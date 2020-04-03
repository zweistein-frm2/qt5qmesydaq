/***************************************************************************
 *   Copyright (C) 2008 by Gregor Montermann <g.montermann@mesytec.com>    *
 *   Copyright (C) 2009-2020 by Jens Krüger <jens.krueger@frm2.tum.de>     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "stdafx.h"

#define EVENTRATE_MONITORING

#ifdef EVENTRATE_MONITORING
#include "Zweistein.TraceSteps.h"
#endif

#include "Zweistein.HomePath.hpp"
#include <boost/exception/all.hpp>
#include <iostream>
#include <filesystem>
#include <QtCore/QDateTime>
#include <QtCore/QTimerEvent>
#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtNetwork/QUdpSocket>
#include <QtCore/QDir>
#include <QtCore/QDataStream>

#include "measurement.h"
#include "mdefines.h"
#include "histogram.h"
#include "spectrum.h"
#include "usermapcorrect.h"
#include "mdllcorrect.h"
#include "mappedhistogram.h"
#include "mesydaq2.h"
#include "editormemory.h"


#include <cmath>
#include <algorithm>
#include "Mesytec.hpp"
#include "Mcpd8.enums.hpp"

#include "Zweistein.Logger.hpp"
#include "qt_glue_std.hpp"

boost::chrono::system_clock::time_point lastmissed_time;


const char* MESYTEC = "MesyTec";

/*!
    \fn Measurement::Measurement(Mesydaq2 *mesy, QObject *parent)

    constructor

    \param mesy Mesydaq2 object to control the hardware
    \param parent Qt parent object
*/
Measurement::Measurement(Mesydaq2 *mesy, QObject *parent)
	: QObject(parent)
	, m_mesydaq(mesy)
	, m_posHistMapCorrection(NULL)
	, m_starttime_msec(0)
	, m_meastime_msec(0)
	, m_status(Idle)
	, m_online(false)
	, m_working(true)
	, m_remote(false)
	, m_headertime(0)
	, m_rateTimer(0)
	, m_onlineTimer(0)
	, m_packages(0)
	, m_triggers(0)
	, m_mode(DataAcquisition)
	, m_histfilename("")
	, m_calibrationfilename("")
	, m_neutrons(0)
	, m_setup(Mpsd)
	, m_histogramFileFormat(StandardFormat)
	, m_psdArrangement(Square)
	, m_lastTriggerTime(0)
{

	std::wstring ws = Zweistein::GetHomePath().wstring();
	QString homepath = QString((const QChar*)ws.c_str(), ws.length());
	
	setHistfilepath(homepath);
	setListfilepath(homepath);
	
	for (int i = 0; i < int(sizeof(m_Hist) / sizeof(Histogram *)); ++i)
		m_Hist[i] = NULL;
	for (int i = 0; i < int(sizeof(m_Spectrum) / sizeof(Spectrum *)); ++i)
		m_Spectrum[i] = NULL;


	QSettings settings = QSettings(QSettings::IniFormat, QSettings::UserScope, qApp->organizationName(), qApp->applicationName());

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;

	auto b = conv.to_bytes(boost::filesystem::path::preferred_separator);
	std::string subdir = "." + std::string(MESYTEC) + b;


	std::filesystem::path inipath = ws + conv.from_bytes(subdir);


	if (!std::filesystem::exists(inipath)) {
		try {
			std::filesystem::create_directory(inipath);
		}
		catch (std::exception& e) {
			std::cout << e.what();
		}
	}
	std::wstring ini = inipath.wstring();
	QString qinipath = QString((const QChar*)ini.c_str(), ini.length());
	settings.value("config/configfilepath", qinipath);
	setConfigfilepath(qinipath);

	setRunId(settings.value("config/lastrunid", "0").toUInt());
	setAutoIncRunId(settings.value("config/autoincrunid", "true").toBool());
	setWriteProtection(settings.value("config/writeprotect", "false").toBool());
	setHistogramFileFormat(HistogramFileFormat(settings.value("config/histogramfileformat", "0").toInt()));

	connect(m_mesydaq, SIGNAL(analyzeDataBuffer(QSharedDataPointer<SD_PACKET>)), this, SLOT(analyzeBuffer(QSharedDataPointer<SD_PACKET>)));
	connect(m_mesydaq, SIGNAL(headerTimeChanged(quint64)), this, SLOT(setHeadertime(quint64)));
	connect(this, SIGNAL(stopSignal()), m_mesydaq, SLOT(stop()));
	m_events = new MesydaqCounter();
	connect(m_events, SIGNAL(stop()), this, SLOT(requestStop()));
	m_timer = new MesydaqTimer();
	connect(m_timer, SIGNAL(stop()), this, SLOT(requestStop()));
	for (quint8 i = MON1ID; i < ADC1ID; ++i)
	{
		m_counter[i] = new MesydaqCounter();
		connect(m_counter[i], SIGNAL(stop()), this, SLOT(requestStop()));
	}

	resizeHistogram(m_mesydaq->width(), m_mesydaq->height());

	connect(this, SIGNAL(acqListfile(bool)), m_mesydaq, SLOT(acqListfile(bool)));
	connect(this, SIGNAL(autoSaveHistogram(bool)), m_mesydaq, SLOT(autoSaveHistogram(bool)));

	for (int j = MON1ID; j <= TTL2ID; ++j)
	{
		QPoint p = settings.value(QString("monitor%1").arg(j), QPoint(0, j)).toPoint();
		setMonitorMapping(p.x(), p.y(), j);
	}

	m_rateTimer = startTimer(100);	// every 100 ms calculate the rates, was 8 before
	m_onlineTimer = startTimer(60);	// every 60 ms check measurement
}

void Measurement::setHistogramFileFormat(HistogramFileFormat f)
{
	m_histogramFileFormat = f;
        QSettings settings(QSettings::IniFormat, QSettings::UserScope, "MesyTec", "QMesyDAQ");
	settings.setValue("config/histogramfileformat", m_histogramFileFormat);
	settings.sync();
}

void Measurement::setPsdArrangement(Arrangement a)
{
	m_psdArrangement = a;
}

quint16 Measurement::height(void) const
{
	if (mode() == ReplayListFile)
		return qMax(m_Hist[AmplitudeHistogram]->height(), m_Hist[PositionHistogram]->height());
	return m_height;
}

quint16 Measurement::width(void) const
{
	if (mode() == ReplayListFile)
		return qMax(m_Hist[AmplitudeHistogram]->width(), m_Hist[PositionHistogram]->width());
	return m_width;
}

/*!
    \fn void Measurement::resizeHistogram(quint16 w, quint16 h, bool clr, bool resize)


    \param w - new width of the histogram
    \param h - new height of the histogram
    \param clr - clear existing histogram data
    \param resize - automatic resize definition
 */
void Measurement::resizeHistogram(quint16 w, quint16 h, bool clr, bool resize)
{
//	LOG_INFO << tr(__PRETTY_FUNCTION__ "(%1, %2, %3, %4)").arg(w).arg(h).arg(clr).arg(resize);
	m_height = h;
	m_width = w;

	m_tubeMapping = m_mesydaq->getTubeMapping();

	for (int i = PositionHistogram; i < CorrectedPositionHistogram; ++i)
	{
		if (!m_Hist[i])
			m_Hist[i] = new Histogram(w, h);
		else
		{
			if (clr)
				m_Hist[i]->clear();
			m_Hist[i]->setAutoResize(resize);
			m_Hist[i]->resize(w, h);
		}
	}

	readCalibration(m_calibrationfilename, false);

	if (m_Hist[CorrectedPositionHistogram])
		delete m_Hist[CorrectedPositionHistogram];
	m_Hist[CorrectedPositionHistogram] = new MappedHistogram(m_posHistMapCorrection, m_Hist[PositionHistogram]);

	if (m_Spectrum[TimeSpectrum])
		delete m_Spectrum[TimeSpectrum];
	m_Spectrum[TimeSpectrum] = NULL;
	m_Spectrum[Diffractogram] = m_Hist[PositionHistogram]->xSumSpectrum();
	m_Spectrum[TubeSpectrum] = m_Hist[PositionHistogram]->ySumSpectrum();
	if (m_Spectrum[SingleTubeSpectrum])
		m_Spectrum[SingleTubeSpectrum]->resize(w);
	else
		m_Spectrum[SingleTubeSpectrum] = new Spectrum(w);
	if (m_Spectrum[SingleLineSpectrum])
		m_Spectrum[SingleLineSpectrum]->resize(w * h);
	else
		m_Spectrum[SingleLineSpectrum] = new Spectrum(w * h);
}

/*!
    \fn Measurement::destroyHistogram(void)

    This method deletes all existing histograms, spectra, ... .
    It also initializes all pointer to NULL.
 */
void Measurement::destroyHistogram(void)
{
	if (m_Hist[AmplitudeHistogram])
		delete m_Hist[AmplitudeHistogram];
	m_Hist[AmplitudeHistogram] = NULL;

	if (m_Hist[PositionHistogram])
		delete m_Hist[PositionHistogram];
	m_Hist[PositionHistogram] = NULL;

	if (m_Hist[CorrectedPositionHistogram])
		delete m_Hist[CorrectedPositionHistogram];
	m_Hist[CorrectedPositionHistogram] = NULL;

	if (m_Spectrum[TimeSpectrum])
		delete m_Spectrum[TimeSpectrum];
	m_Spectrum[TimeSpectrum] = NULL;

	if (m_Spectrum[SingleTubeSpectrum])
		delete m_Spectrum[SingleTubeSpectrum];
	m_Spectrum[SingleTubeSpectrum] = NULL;

	if (m_Spectrum[AmplitudeSpectrum])
		delete m_Spectrum[AmplitudeSpectrum];
	m_Spectrum[AmplitudeSpectrum] = NULL;
	if (m_Spectrum[SingleLineSpectrum])
		delete m_Spectrum[SingleLineSpectrum];
	m_Spectrum[SingleLineSpectrum] = NULL;

}

//! destructor
Measurement::~Measurement()
{
        if (m_rateTimer)
		killTimer(m_rateTimer);
	m_rateTimer = 0;

	if (m_onlineTimer)
		killTimer(m_onlineTimer);
	m_onlineTimer = 0;

	if (m_posHistMapCorrection)
		delete m_posHistMapCorrection;
	m_posHistMapCorrection = NULL;

	destroyHistogram();
}

QString Measurement::version() const
{
    return QString(VERSION);
}

/*!
    \fn Measurement::timerEvent(QTimerEvent *event)

    callback for the timer events

    \param event event structure
*/
void Measurement::timerEvent(QTimerEvent *event)
{
	int id = event->timerId();
	if (id == m_rateTimer)
		calcRates();
	else if (id == m_onlineTimer)
	{
		if(!isOk())
			setOnline(false);
	}
}
/*!
    \fn Measurement::setCurrentTime(quint64 msecs)

    sets the current time for the measurement
    the timer will be updated during the events

    \param msecs current time in ms
 */
void Measurement::setCurrentTime(quint64 msecs)
{
	if(status() == Started)
	{
		m_meastime_msec = msecs - m_starttime_msec;
		m_events->setTime(m_meastime_msec);
		for (quint8 i = MON1ID; i < ADC1ID; ++i)
			m_counter[i]->setTime(m_meastime_msec);
		m_timer->setTime(msecs);
	}
}

/*!
    \fn Measurement::getMeastime(void) const

    \return measurement time
 */
quint64 Measurement::getMeastime(void) const
{
	return m_meastime_msec;
}

/*!
    \fn Measurement::start()

    starts the measurement and initialize all counters and timers
 */
void Measurement::start()
{
	m_mode = DataAcquisition;
	resizeHistogram(m_mesydaq->width(), m_mesydaq->height());
	if (m_Spectrum[AmplitudeSpectrum])
		m_Spectrum[AmplitudeSpectrum]->clear();
	foreach (MesydaqCounter *c, m_counter)
		c->reset();
	m_packages = 0;
	m_triggers = 0;
	m_neutrons = 0;
	if (m_mesydaq->getAutoIncRunId())
		m_mesydaq->setRunId(m_mesydaq->runId() + 1);
	m_mesydaq->start();
	m_status = Started;
	m_starttime_msec = m_mesydaq->time();
	LOG_INFO << tr("event counter limit : %1").arg(m_events->limit()) << std::endl;
	LOG_INFO << tr("timer limit : %1").arg(m_timer->limit() / 1000) << std::endl;
	foreach (MesydaqCounter *c, m_counter)
	{
		c->start(m_starttime_msec);
		LOG_INFO<< tr("counter %1 value : %2 limit : %3").arg(*c).arg(c->value()).arg(c->limit()) << std::endl;
	}
	m_lastTriggerTime = 0;
	m_events->start(m_starttime_msec);
	m_timer->start(m_starttime_msec);
}

/*!
    \fn Measurement::requestStop()

    callback for the request to stop the measurement
 */
void Measurement::requestStop()
{
	if (status() == Started)
	{
		m_status = Stopped;
		emit stopSignal(false);
#ifdef max
#undef max
#endif
		LOG_INFO << tr("Max %1 was at pos %2").arg(m_Hist[PositionHistogram]->max(0)).arg(m_Hist[PositionHistogram]->maxpos(0)) << std::endl;
	}
}

/*!
    \fn Measurement::stop()

    really stop the measurement
 */
void Measurement::stop()
{
	if (status() != Idle)
	{
		if (status() == Started)
			m_mesydaq->stop();
		quint64 time = m_mesydaq->time();
		foreach (MesydaqCounter *c, m_counter)
			c->stop(time);
		LOG_WARNING << tr("packages : %1 triggers : %2 neutrons : %3").arg(m_packages).arg(m_triggers).arg(m_neutrons) << std::endl;
		if (m_triggers)
		{
			for(int i = 0; i < m_counter.size(); ++i)
				LOG_WARNING << tr("Counter %1 got %2 events").arg(i).arg(m_counter[i]->value()) << std::endl;
		}
		for (int i = 0; i < NoHistogram; ++i)
			LOG_WARNING << tr("Histogram[%1]: %2").arg(i).arg(m_Hist[i]->getTotalCounts()) << std::endl;
	}
	m_status = Idle;
}

/*!
    \fn Measurement::cont()
    \todo implement me
*/
void Measurement::cont()
{
}

/*!
    \fn Measurement::setCounter(quint32 cNum, quint64 val)

    fill a counter with a value

    \param cNum number of the counter
    \param val value of the counter
 */
void Measurement::setCounter(quint32 cNum, quint64 val)
{
// set counter
	LOG_INFO << tr("Measurement::setCounter(cNum = %1, val = %2)").arg(cNum).arg(val) << std::endl;
	if(m_counter.contains(cNum))
	{
		if (val == 0)
			m_counter[cNum]->reset();
		else
			m_counter[cNum]->set(val);
// is counter master and is limit reached?
		if(m_counter[cNum]->isStopped() && status() != Stopped)
		{
			LOG_INFO << tr("stop on counter %1, value: %2, preset: %3").arg(cNum).arg(m_counter[cNum]->value()).arg(m_counter[cNum]->limit()) << std::endl;
			m_status = Stopped;
			emit stopSignal();
		}
	}
}

/*!
    \fn Measurement::calcRates()

    calculates the rates for all counters
 */
void Measurement::calcRates()
{
	foreach(MesydaqCounter *c, m_counter)
		c->calcRate();
}

/*!
    \fn Measurement::calcMeanRates()

    calculates the mean rates for all counters
 */
void Measurement::calcMeanRates()
{
	foreach(MesydaqCounter *c, m_counter)
		c->calcMeanRate();
}

/*!
    \fn Measurement::getCounter(const quint8 cNum) const

    get the current value of the counter

    \param cNum number of the counter
    \return counter value
 */
quint64 Measurement::getCounter(const quint8 cNum) const
{
	if(m_counter.contains(cNum))
		return m_counter[cNum]->value();
	return 0;
}

/*!
    \fn Measurement::getRate(const quint8 cNum) const

    get the rate of a counter

    \param cNum number of the counter
    \return counter rate
 */
quint64 Measurement::getRate(const quint8 cNum) const
{
	if(m_counter.contains(cNum))
		return m_counter[cNum]->rate();
	return 0;
}

/*!
    \fn Measurement::isOk(void) const

    return the status of the measurement
	- 0 - online and working
	- 1 - online and not working
	- 2 - not oline
 */
quint8 Measurement::isOk(void) const
{
	quint8 ret(2);
	if (m_online)
	{
		if (m_working)
			ret = 0;
		else
			ret = 1;
	}
	return ret;
}

/*!
    \fn Measurement::setOnline(bool truth)

    sets the measurement online/offline

    \param truth online = true, offline = false
 */
void Measurement::setOnline(bool truth)
{
	m_online = truth;
	LOG_INFO << tr("MCPD %1").arg(m_online ? "online" : "offline") << std::endl;
}

/*!
    \fn quint64 Measurement::getTimerPreset(void) const

    get the preset value of the timer
    \return preset value
 */
quint64 Measurement::getTimerPreset(void) const
{
	return m_timer->limit();
}

/*!
    \fn void Measurement::setTimerPreset(const quint64 prval, const bool mast)

    sets the timer preset and master counter, all other counters will be set to slave
    if the timer is set to master

    \param prval preset value
    \param mast should the counter be master or not
 */
void Measurement::setTimerPreset(const quint64 prval, const bool mast)
{
	m_timer->setMaster(mast);
	m_timer->setLimit(prval);
}

/*!
    \fn Measurement::isTimerMaster(void) const

    is timer master or not

    \return master state
 */
bool Measurement::isTimerMaster(void) const
{
	return m_timer->isMaster();
}

/*!
    \fn Measurement::clearTimer(void)

    resets the timer, clear preset and set value to 0
 */
void Measurement::clearTimer(void)
{
	m_timer->reset();
}

/*!
    \fn quint64 Measurement::getEventCounterPreset(void) const

    get the preset value of the event counter
    \return preset value
 */
quint64 Measurement::getEventCounterPreset(void) const
{
	return m_events->limit();
}

/*!
    \fn void Measurement::setEventCounterPreset(const quint64 prval, const bool mast)

    sets the event counter preset and master counter, all other counters will be set
    to slave if the event counter is set to master

    \param prval preset value
    \param mast should the counter be master or not
 */
void Measurement::setEventCounterPreset(const quint64 prval, const bool mast)
{
	m_events->setMaster(mast);
	m_events->setLimit(prval);
}

/*!
    \fn Measurement::isEventCounterMaster(void) const

    is event counter master or not

    \return master state
 */
bool Measurement::isEventCounterMaster(void) const
{
	return m_events->isMaster();
}

/*!
    \fn Measurement::clearEventCounter(void)

    resets the event counter, clear preset and set value to 0
 */
void Measurement::clearEventCounter(void)
{
	m_events->reset();
}

/*!
    \fn Measurement::getEventCounterRate(void) const

    get the rate of the event counter

    \return counter rate
 */
quint64 Measurement::getEventCounterRate(void) const
{
	return m_events->rate();
}

/*!
    \fn Measurement::setPreset(quint8 cNum, quint64 prval, bool mast)

    sets the counter preset and master counter, all other counters will be set to slave
    if the counter is set to master

    \param cNum number of the counter
    \param prval preset value
    \param mast should the counter be master or not
 */
void Measurement::setPreset(quint8 cNum, quint64 prval, bool mast)
{
	if(m_counter.contains(cNum))
	{
		LOG_INFO << tr("setPreset counter: %1 to %2 %3").arg(cNum).arg(prval).arg(mast ? "master" : "slave") << std::endl;
		m_counter[cNum]->setMaster(mast);
		m_counter[cNum]->setLimit(prval);
	}
}


/*!
    \fn Measurement::getPreset(quint8 cNum)

    get the preset value of the counter

    \param cNum number of the counter
    \return preset value
 */
quint64 Measurement::getPreset(quint8 cNum) const
{
	if(m_counter.contains(cNum))
		return m_counter[cNum]->limit();
	return 0;
}

/*!
    \fn Measurement::setListmode(bool truth)

    sets the list mode

    \param truth list mode
 */
void Measurement::setListmode(bool truth)
{
	emit acqListfile(truth);
}

/*!
    \fn Measurement::setAutoSaveHistogram(bool truth)

    sets the auto save histogram mode

    \param truth auto save histogram mode
 */
void Measurement::setAutoSaveHistogram(bool truth)
{
	emit autoSaveHistogram(truth);
}

/*!
    \fn Measurement::setRemote(bool truth)

    sets the flag for remote control

    \param truth remote on/off
 */
void Measurement::setRemote(bool truth)
{
	m_remote = truth;
}

/*!
    \fn Measurement::remoteStart(void) const

     gets information whether the remote control is switched on or not

     \return status of remote control
 */
bool Measurement::remoteStart(void) const
{
	return m_remote;
}

/*!
    \fn Measurement::isMaster(const quint8 cNum) const

    is counter master or not

    \param cNum number of the counter
    \return master state
 */
bool Measurement::isMaster(const quint8 cNum) const
{
	if (m_counter.contains(cNum))
		return m_counter[cNum]->isMaster();
	return false;
}

/*!
    \fn Measurement::clearCounter(quint8 cNum)

    resets the counter, clear preset and set value to 0

    \param cNum number of the counter
 */
void Measurement::clearCounter(quint8 cNum)
{
	if(m_counter.contains(cNum))
		m_counter[cNum]->reset();
}

/*!
    \fn Measurement::clearAllHist(void)

    clears all histograms
 */
void Measurement::clearAllHist(void)
{
	if (m_Hist[PositionHistogram])
		m_Hist[PositionHistogram]->clear();
	if (m_Hist[AmplitudeHistogram])
		m_Hist[AmplitudeHistogram]->clear();
	if (m_Hist[CorrectedPositionHistogram])
		m_Hist[CorrectedPositionHistogram]->clear();
	if (m_Spectrum[TimeSpectrum])
		m_Spectrum[TimeSpectrum]->clear();
	if (m_Spectrum[SingleTubeSpectrum])
		m_Spectrum[SingleTubeSpectrum]->clear();
	if (m_Spectrum[AmplitudeSpectrum])
		m_Spectrum[AmplitudeSpectrum]->clear();

}

/*!
    \fn Measurement::clearChanHist(quint16 chan)

    clears the spectra of a tube

    \param chan tube number
 */
void Measurement::clearChanHist(quint16 chan)
{
	quint16 line = mapTube(chan);
	if (line == 0xFFFF)
		return;
	if (m_Hist[PositionHistogram])
		m_Hist[PositionHistogram]->clear(line);
	if (m_Hist[AmplitudeHistogram])
		m_Hist[AmplitudeHistogram]->clear(line);
	if (m_Hist[CorrectedPositionHistogram])
		m_Hist[CorrectedPositionHistogram]->clear(line);
}

/*!
    \fn void Measurement::clearChanHist(const quint16 mcpd, const quint8 mpsd, const quint8 chan)

    clears the spectra of a tube

    \param mcpd number of the MCPD
    \param mpsd number of the MPSD on the MCPD
    \param chan number of the channel at the MPSD
 */
void Measurement::clearChanHist(const quint16 mcpd, const quint8 mpsd, const quint8 chan)
{
	quint16 line = chan + m_mesydaq->startChannel(mcpd) + m_mesydaq->width(mcpd, mpsd);
	clearChanHist(line);
}
/*!
    \fn Spectrum *Measurement::data(const HistogramType t, const quint16 line)

    gets a position spectrum of a tube

    \param t type of the requested histogram
    \param line tube number
    \return spectrum if line exist otherwise NULL pointer
 */
Spectrum *Measurement::data(const HistogramType t, const quint16 line)
{
	quint16 tmpLine = mapTube(line);
	if (m_Hist[t] && tmpLine != 0xFFFF)
		return m_Hist[t]->spectrum(tmpLine);
	else
		return NULL;
}

/*!
    \fn Spectrum *Measurement::data(const HistogramType t, const quint16 mcpd, const quint16 mpsd, const quint8 chan)

    gets a position spectrum of a tube

    \param t type of the requested histogram
    \param mcpd number of the MCPD
    \param mpsd number of the MPSD on the MCPD
    \param chan number of the channel at the MPSD
    \return spectrum if line exist otherwise NULL pointer
 */
Spectrum *Measurement::data(const HistogramType t, const quint16 mcpd, const quint8 mpsd, const quint8 chan)
{
	quint16 line = calculateChannel(mcpd, mpsd, chan); // chan + m_mesydaq->startChannel(mcpd) + m_mesydaq->width(mcpd, mpsd);
	return data(t, line);
}


/*!
    \fn Spectrum *Measurement::data(const HistogramType t)

    gets the position histogram

    \return position histogram if exist otherwise NULL pointer
*/
Spectrum *Measurement::data(const HistogramType t)
{
	if (t == CorrectedPositionHistogram)
		return m_Spectrum[TubeSpectrum];
	if (m_Hist[t])
		return m_Hist[t]->ySumSpectrum();
	return NULL;
}

/*!
    \fn Spectrum *Measurement::spectrum(const SpectrumType t)

    gets a spectrum of all events

    \return spectrum if line exist otherwise NULL pointer
*/
Spectrum *Measurement::spectrum(const SpectrumType t)
{
	switch(t)
	{
		case TubeSpectrum :
			if (m_Spectrum[TubeSpectrum]->width() > 0)
				return m_Spectrum[TubeSpectrum];
			break;
		case SingleLineSpectrum :
			{
				int pos = 0;
				for (int i = 0; i < m_Hist[PositionHistogram]->width(); ++i)
				{
					Spectrum *spec = m_Hist[PositionHistogram]->spectrum(i);
					for (int j = 0; j < spec->width(); ++j, ++pos)
						m_Spectrum[SingleLineSpectrum]->setValue(pos, spec->value(j));
				}
			}
			return m_Spectrum[SingleLineSpectrum];
			break;
		case SingleTubeSpectrum :
			if (m_Spectrum[SingleTubeSpectrum] && m_Spectrum[SingleTubeSpectrum]->width() > 0)
				return m_Spectrum[SingleTubeSpectrum];
			break;
		case Diffractogram :

			return m_Spectrum[Diffractogram];
			break;
		default :
			return m_Spectrum[t];
	}
	return NULL;
}

/*!
    \fn Measurement::writeHistograms(const QString &name)

    writes the position and amplitude histogram to a file

    \param name file name
 */
void Measurement::writeHistograms(const QString &name)
{
	if(name.isEmpty())
		return;

	QFile f;
	f.setFileName(name);
	if (f.open(QIODevice::WriteOnly))
	{    // file opened successfully
		QTextStream t(&f);        // use a text stream
		switch(m_histogramFileFormat)
		{
			case SimpleFormat:
				writeSimpleHistogram(t);
				break;
			default:
			case StandardFormat:
				writeStandardHistograms(t);
				break;
		}
		f.close();
		if (getWriteProtection())
			f.setPermissions(f.permissions() & (~(QFile::WriteOwner|QFile::WriteUser|QFile::WriteGroup|QFile::WriteOther)));
	}
}

void Measurement::writeStandardHistograms(QTextStream &t)
{
	QString endLine("\r\n");

	t << "# filename = " << reinterpret_cast<QFile *>(t.device())->fileName() << endLine;
	//
	// write the monitor, events, and timer values after a '#' char
	//
	for (quint8 i = MON1ID; i <= TTL2ID; ++i)
		t << "# monitor " << (i + 1) << " = " << m_counter[i]->value() << endLine;
	t << "# events = " << m_events->value() << endLine;
	t << "# timer = " << m_timer->value() << " ms" << endLine;
	t << "# setup file = " << getConfigfilename() << endLine;
	if (!getCalibrationfilename().isEmpty())
		t << "# calibration file = " << getCalibrationfilename() << endLine;
	if (acqListfile())
		t << "# listmode file = " << getListfilename() << endLine;
	// Title
	t << "mesydaq Histogram File    " << QDateTime::currentDateTime().toString("dd.MM.yy  hh:mm:ss") << endLine;
	t.flush();
	if (m_Hist[PositionHistogram])
		t << m_Hist[PositionHistogram]->format("position data: 1 row title (8 x 8 detectors), position data in columns") << endLine;
	if (m_Hist[AmplitudeHistogram])
		t << m_Hist[AmplitudeHistogram]->format("amplitude/energy data: 1 row title (8 x 8 detectors), amplitude data in columns") << endLine;
	if (m_Hist[CorrectedPositionHistogram])
		t << m_Hist[CorrectedPositionHistogram]->format("corrected position data: 1 row title (8 x 8 detectors), position data in columns") << endLine;
}

void Measurement::writeSimpleHistogram(QTextStream &t)
{
	QString endLine("\r\n");
	if (m_Hist[PositionHistogram])
		t << m_Hist[PositionHistogram]->format(); // << endLine;
}

/*!
    \fn Measurement::readHistograms(const QString &name)

    reads the position and amplitude histogram from a file

    \param name file name
 */
void Measurement::readHistograms(const QString &name)
{
	if(name.isEmpty())
		return;

        setListfilename("");
	QFile f;
	f.setFileName(name);
	if (f.open(QIODevice::ReadOnly))
	{
		m_mode = HistogramLoad;
// use a text stream
		QTextStream t(&f);
		QStringList list = t.readLine().split(QRegExp("\\s+"));
// if there are some comment lines which should contain only the monitor, event, and timer values
// ignore them at the moment
		while (list.size() > 0 && list[0] == "#")
			list = t.readLine().split(QRegExp("\\s+"));
// Title
		if (list.size() >= 3 && list[0] == "mesydaq" && list[1] == "Histogram" && list[2] == "File")
		{
			setHistfilename(name);
			clearAllHist();
			resizeHistogram(0, 0);

			while(!t.atEnd())
			{
				list = t.readLine().split(QRegExp("\\s+"));
				if (list.size() >= 2 && list[1].startsWith("data"))
				{
					if (list[0] == "position")
						fillHistogram(t, m_Hist[PositionHistogram]);
					else if (list[0] == "amplitude/energy")
						fillHistogram(t, m_Hist[AmplitudeHistogram]);
					else if (list[0] == "corrected")
						fillHistogram(t, m_Hist[CorrectedPositionHistogram]);
				}
			}
			resizeHistogram(m_Hist[PositionHistogram]->width() ? m_Hist[PositionHistogram]->width() : m_Hist[AmplitudeHistogram]->width(),
					m_Hist[PositionHistogram]->width() ?  m_Hist[PositionHistogram]->height() : m_Hist[AmplitudeHistogram]->height(), false);
			// create the mapped histogram
			reinterpret_cast<MappedHistogram *>(m_Hist[CorrectedPositionHistogram])->setHistogram(m_Hist[PositionHistogram]);
		}
		f.close();
	}
}

/*!
	\fn void Measurement::readCalibration(const QString &name, bool bForceDefault)

	\param name calibration file name
	\param bForceDefault reset to default with empty calibration file name
 */
void Measurement::readCalibration(const QString &name, bool bForceDefault)
{
	if (m_calibrationfilename.isEmpty() && !bForceDefault)
		return;

	setCalibrationfilename(name);
	if (m_posHistMapCorrection)
		delete m_posHistMapCorrection;
	if (m_calibrationfilename.isEmpty())
	{
		switch (setupType())
		{
			case Mdll:
				LOG_INFO << tr("MDLL Map correction");
				m_posHistMapCorrection = new MdllMapCorrection(QSize(480, 480/* m_width, m_height */));
				break;
			case Mdll2:
				LOG_INFO << tr("MWPCHR Map correction");
				m_posHistMapCorrection = new Mdll2MapCorrection(QSize(256, 256/* m_width, m_height */));
				break;
			default:
				LOG_INFO << tr("Linear Map correction");
#if defined(_MSC_VER)
#	pragma message("TODO the size of the corrected map")
#else
#	warning TODO the size of the corrected map
#endif

				m_posHistMapCorrection = new LinearMapCorrection(QSize(m_width, m_height), QSize(m_width, m_height));

				break;
		}
	}
	else
	{
		LOG_INFO << tr("User map correction from file '%1' -> (%2, %3)").arg(m_calibrationfilename).arg(m_width).arg(m_height);
		m_posHistMapCorrection = new UserMapCorrection(QSize(m_width, m_height), m_calibrationfilename);
	}
	emit mappingChanged();
}

/*!
    \fn Measurement::fillHistogram(QTextStream &t, Histogram *hist)

    analyzes the text stream down to a empty line and put the values
    into a histogram
*/

void Measurement::fillHistogram(QTextStream &t, Histogram *hist)
{
	QString tmp = t.readLine();
	QStringList list = tmp.split(QRegExp("\\s+"), QString::SkipEmptyParts);
	int tubes = list.size();

	QStringList lines;

	while(!(tmp = t.readLine()).isEmpty())
		lines << tmp;

	LOG_INFO << tr("Resize histogram to %1, %2").arg(tubes).arg(lines.size());

	hist->resize(tubes, lines.size());

	for (int j = 0; j < lines.size(); ++j)
	{
		list = lines[j].split(QRegExp("\\s+"), QString::SkipEmptyParts);
		if (list.size() == (tubes + 1))
		{
//			add values to histogram
			quint16 bin = list[0].toUShort();
			for(int i = 1; i < list.size(); ++i)
				hist->addValue((i - 1), bin, list[i].toULongLong());
		}
	}
}

/*!
    \fn Measurement::analyzeBuffer(QSharedDataPointer<SD_PACKET> pPacket)

    analyze the data packet and put all events into the right counters and/or histogram

    \param pPacket data packet
 */
void Measurement::analyzeBuffer(QSharedDataPointer<SD_PACKET> pPacket)
{
	quint16 neutrons = 0;
	quint16 triggers = 0;
	quint16	monitorTriggers = 0;
	quint16	ttlTriggers = 0;
	quint16	adcTriggers = 0;
	quint16 counterTriggers = 0;
	quint64 tim;
	quint16 mod = pPacket->dp.deviceId;
	
	const MDP_PACKET* pMdp = &pPacket.constData()->mdp;
#ifdef EVENTRATE_MONITORING
	Zweistein::TraceStep0((void *)pMdp);
#endif
	
	quint16 txmod = m_mesydaq->getTxMode(mod, true);

	setHeadertime(pPacket->dp.time[0] + (quint64(pPacket->dp.time[1]) << 16) + (quint64(pPacket->dp.time[2]) << 32));
	setCurrentTime(m_headertime / m_timeBase);

#ifdef EVENTRATE_MONITORING
	if (pMdp->bufferNumber != (unsigned short)(lastbufnum + 1)) {
		boost::chrono::duration<double> sec = boost::chrono::system_clock::now() - lastmissed_time;
		unsigned short missed = (unsigned short)(pMdp->bufferNumber - (unsigned short)(lastbufnum + 1));
		lastmissed_count += missed;
		if (sec.count() > 1) {
			boost::mutex::scoped_lock lock(coutGuard);
			LOG_ERROR<<std::endl<<  boost::chrono::time_fmt(boost::chrono::timezone::local) << boost::chrono::system_clock::now() << ": " << "MISSED " << lastmissed_count << " BUFFER(s)" << std::endl;
			lastmissed_time = boost::chrono::system_clock::now();
			lastmissed_count = 0;
		}

	}
#endif

	lastbufnum = pMdp->bufferNumber;
#pragma message("ALANGHOF : 1,6M EVENTS when return here")
	m_packages++;
	Mode mode = this->mode();

	if(pPacket->dp.bufferType < 0x0003)
	{
// extract parameter values:
		QChar c('0');
		quint32 datalen = (pPacket->dp.bufferLength - pPacket->dp.headerLength) / 3;
//
// status Idle is for replaying files
//
		for(quint32 counter = 0, i = 0; i < datalen && (status() == Started || status() == Idle); ++i, counter += 3)
		{
			tim = pPacket->dp.data[counter + 1] & 0x7;
			tim <<= 16;
			tim += pPacket->dp.data[counter];
			tim += m_headertime;
// id stands for the trigId and modId depending on the package type
			quint8 id = (pPacket->dp.data[counter + 2] >> 12) & 0x7;
			m_timer->setTime(tim / m_timeBase);
// not neutron event (counter, chopper, ...)
			if((pPacket->dp.data[counter + 2] & TRIGGEREVENTTYPE))
			{
				triggers++;
				quint8 dataId = (pPacket->dp.data[counter + 2] >> 8) & 0x0F;
				quint8 olddataId = dataId;

				if (dataId > ADC2ID)
				{
					++counterTriggers;
					LOG_INFO << tr("counter %1 : %2").arg(dataId).arg(i);
				}
				else switch (dataId = monitorMapping(mod, dataId))
				{
					case MON1ID :
					case MON2ID :
					case MON3ID :
					case MON4ID :
						++monitorTriggers;
						++(*m_counter[dataId]);
						if (m_counter[dataId]->isTrigger())
							m_lastTriggerTime = tim;

						break;
					case TTL1ID :
					case TTL2ID :
						++ttlTriggers;
						++(*m_counter[dataId]);
						if (m_counter[dataId]->isTrigger())
							m_lastTriggerTime = tim;

						break;
					case ADC1ID :
					case ADC2ID :
						++adcTriggers;
						++(*m_counter[dataId]);

						break;
					default:
						LOG_ERROR << tr("Got unknown trigger on data id(%1) from (%2, %3).").arg(dataId).arg(mod).arg(olddataId);
						break;
				}
			}
// neutron event:
			else
			{
				tim -= m_lastTriggerTime;
				quint8 slotId = (pPacket->dp.data[counter + 2] >> 7) & 0x1F;
				quint8 modChan = (id << 3) + slotId;
				quint16 chan = modChan + (mod << 6);
				quint16 amp = ((pPacket->dp.data[counter+2] & 0x7F) << 3) + ((pPacket->dp.data[counter+1] >> 13) & 0x7),
					pos = (pPacket->dp.data[counter+1] >> 3) & 0x3FF;
				quint16 moduleID = m_mesydaq->getModuleId(mod, id);
//
// old MPSD-8 are running in 8-bit mode and the data are stored left in the ten bits
//
				if (moduleID == Mesy::ModuleId::MPSD8OLD)
				{
					amp >>= 2;
					pos >>= 2;
				}
				if (pPacket->dp.bufferType == 0x0002)
				{
//
// in MDLL, data format is different:
// The position inside the PSD is used as y direction
// Therefore the x position of the MDLL has to be used as channel
// the y position as position and the channel value is the amplitude value
// y position (10 bit) is at MPSD "Amplitude" data
// amplitude (8 bit) is at MPSD "chan" data
//
					chan = (id << 5) + slotId;
					quint16 val = pos;
					pos = amp;
					amp = chan;
					chan = val;
					if (pos >= m_mesydaq->height())
						continue;
				}
				else
				{
#pragma message("ALANGHOF why is Mesy::ModuleId::MPSD8 not ok?")
					if (moduleID!= Mesy::ModuleId::MPSD8 && moduleID != Mesy::ModuleId::MPSTD16 && pos >= 960 )
					{
						LOG_WARNING << tr("POSITION >= 959 : %1 %2.%3.%4").arg(pos).arg(pPacket->dp.data[counter + 2], 4, 16, QChar('0')).
							arg(pPacket->dp.data[counter + 1], 4, 16, QChar('0')).arg(pPacket->dp.data[counter], 4, 16, QChar('0'));
						continue;
					}
				}
				if (mode == ReplayListFile || m_mesydaq->active(mod, id, slotId))
				{
// BUG in firmware, every first neutron event seems to be "buggy" or virtual
// Only on newer modules with a distinct CPLD firmware
// BUG is reported
					if (neutrons == 1 && modChan == 0 && pos == 0 && amp == 0 && (m_mesydaq->capabilities(mod, true) & Mcpd8::TX_CAP::TPA))
					{
						LOG_WARNING << tr("GHOST EVENT: SlotID %1 Mod %2").arg(slotId).arg(id);
						continue;
					}
					if (moduleID != TYPE_MDLL)
					{
						if (!(txmod & Mcpd8::TX_CAP::TPA) && m_mesydaq->getMode(mod, id))
						{
// Amplitude must be different from 0 !!
							if (amp == 0)
							{
// If the modules are not able to transfer the position and amplitude simultaneously
// and the amplitude mode is enabled, the amplitude is in the field for the position
// given !
								quint16 val = pos;
								pos = amp;
								amp = val;
							}
						}
						if (moduleID == Mesy::ModuleId::MPSTD16)
						{

							quint16 lchan = chan << 1;	// each tube has two channels
							if (m_mesydaq->version(mod, id) <= 6.03)
								lchan += (pos >> 9) & 0x1;	// if the MSB bit is set then it comes from the right channel
							else if (m_mesydaq->getMode(mod, id))
							{
								lchan += (amp >> 9) & 0x1;	// if the MSB bit is set then it comes from the right channel
//								LOG_DEBUG << "amp " << amp << "-" << (amp >> 9) << "-" << lchan;
							}
							else
							{
								lchan += (pos >> 9) & 0x1;
//								LOG_DEBUG << "pos " << pos << "-" << (pos >> 9) << "-" << lchan;
							}
							amp &= 0x1FF;		// in MSB of amp is the information left/right
							lchan = mapTube(lchan);

							if (lchan == 0xFFFF)
								continue;
							chan = lchan;
							if (m_Spectrum[SingleTubeSpectrum])
							{
								m_Spectrum[SingleTubeSpectrum]->incVal(chan);

							}
						}
						else
						{
							chan = mapTube(chan);
							if (chan == 0xFFFF)
								continue;
						}
					}
					neutrons++;
					++(*m_events);
					if (m_Hist[PositionHistogram])
						m_Hist[PositionHistogram]->incVal(chan, pos);
					if (m_Hist[AmplitudeHistogram])
					{
						if (pPacket->dp.bufferType == 0x0002)
						{
							m_Hist[AmplitudeHistogram]->addValue(chan, pos, amp);
							m_Spectrum[AmplitudeSpectrum]->incVal(amp);
						}
						else
							m_Hist[AmplitudeHistogram]->incVal(chan, amp);
					}
					if (m_Hist[CorrectedPositionHistogram])
						m_Hist[CorrectedPositionHistogram]->incVal(chan, pos);
				}

			}
		}

		m_triggers += triggers;
		m_neutrons += neutrons;

	}
	else
		LOG_INFO << tr("buffer type : %1").arg(pPacket->dp.bufferType);
}

quint16 Measurement::mapTube(const quint16 tube)
{
	quint16 tmpTube = m_tubeMapping.value(tube, 0xFFFF);

	return tmpTube;
}

bool Measurement::acqListfile() const
{
	return m_mesydaq ? m_mesydaq->acqListfile() : true;
}

/**
    \fn bool Measurement::getNextBlock(QDataStream &datStream, DATA_PACKET &dataBuf)

    Read the next data buffer block from file

    block starts with:
	- buffer length
	- buffer type
	- header length
	- buffer number

    If this words contain 0xFFFF 0xAAAA 0x5555 0x0000 the EOF is reached

    If after the block do not follow 0x0000 0xFFFF 0x5555 0xAAAA (block separator)
    the data file is corrupted

    \param datStream data stream
    \param dataBuf data buffer, will be filled

    \return true if block complete otherwise false
 */
bool Measurement::getNextBlock(QDataStream &datStream, DATA_PACKET &dataBuf)
{
	const QChar c('0');
	quint16 sep1, sep2, sep3, sep4;

	quint64	sep;
	datStream >> sep;
	sep4 = sep & 0xFFFF;
	sep3 = (sep >>= 16) & 0xFFFF;
	sep2 = (sep >>= 16) & 0xFFFF;
	sep1 = (sep >>= 16) & 0xFFFF;
// check for closing signature:
// closing separator: sepF sepA sep5 sep0
	bool ok = !((sep1 == sepF) && (sep2 == sepA) && (sep3 == sep5) && (sep4 == sep0));
	if (ok)
	{
		dataBuf.bufferLength = sep1;
		dataBuf.bufferType = sep2;
		dataBuf.headerLength = sep3;
		dataBuf.bufferNumber = sep4;
		ok = (dataBuf.bufferLength <= 750);
		if (ok)
		{
			int buflen = (dataBuf.bufferLength - 4) * sizeof(quint16);
			char *pD = (char *)&dataBuf.runID;
			ok = datStream.readRawData(pD, buflen) == buflen;
			if (ok)
				for (int i = 0; i < buflen; i += 2)
				{
					char tmp = pD[i];
					pD[i] = pD[i + 1];
					pD[i + 1] = tmp;
				}
			else
				LOG_ERROR << "corrupted file";
			datStream >> sep;
			sep4 = sep & 0xFFFF;
			sep3 = (sep >>= 16) & 0xFFFF;
			sep2 = (sep >>= 16) & 0xFFFF;
			sep1 = (sep >>= 16) & 0xFFFF;
			// block separator : sep0 sepF sep5 sepA
			ok = ((sep1 == sep0) && (sep2 == sepF) && (sep3 == sep5) && (sep4 == sepA));
		}
		else
		{
			LOG_DEBUG << tr("erroneous length: %1 - aborting").arg(dataBuf.bufferLength);
			datStream >> sep1 >> sep2 >> sep3 >> sep4;
			LOG_DEBUG << tr("Separator: %1 %2 %3 %4").arg(sep1, 2, 16, c).arg(sep2, 2, 16, c).arg(sep3, 2, 16, c).arg(sep4, 2, 16, c);
		}
	}
	else
	{
			LOG_DEBUG << tr("EOF reached");
	}
	return ok;
}

/*!
    \fn Measurement::readListfile(QString readfilename)

    reads a list mode data file and handles the read events as same as events coming
    over the network interfaces

    \param readfilename file name for the list mode data
*/
void Measurement::readListfile(const QString &readfilename)
{
	QFile datfile;
	datfile.setFileName(readfilename);
	if (!datfile.open(QIODevice::ReadOnly))
		return;

	m_mode = ReplayListFile;
	m_status = Started;

	LOG_INFO << tr("Start replay");
	QDataStream datStream;
	quint16 sep1, sep2, sep3, sep4;

	setListfilename(readfilename);
	setHistfilename("");
	datStream.setDevice(&datfile);

	m_packages = 0;
	m_triggers = 0;
	m_neutrons = 0;

	quint32 blocks(0),
		bcount(0);
	qint64  seekPos(-1);

	const int blocksize(64 * 1024); // 64KB
	bool bFound(false);
	QByteArray header;
	for (;;) // search for start of sequence magic
	{
		QByteArray d;
		d.resize(blocksize);
		int i = datStream.readRawData(d.data(), blocksize);
		if (i > 0)
		{
			d.resize(i);
			header += d;
		}
		if (header.size() < int(4 * sizeof(sep0)))
		{
			if (i < blocksize)
				break;
			continue;
		}
		for (i = 0; i < header.size(); ++i)
		{
			const quint16* p = reinterpret_cast<const quint16 *>(header.constData() + i);
			if (p[0] == sep0 && p[1] == sep5 && p[2] == sepA && p[3] == sepF)
			{
				bFound=true;
				break;
			}
		}
		if (i >= header.size())
		{
			i = header.size() - (4 * sizeof(sep0) - 1);
			if (i <= 0)
				break;
			header.remove(0, i);
			seekPos += i;
			if (seekPos >= 1048576) // stop at 1MB searching for header
				break;
		}
		else
		{
			seekPos += i;
			break;
		}
	}
	header.clear();

	if (!bFound && seekPos < 0)
	{
		// header magic failed, use the old way
		QTextStream textStream;
		QString str;
		seekPos = 0;
		textStream.setDevice(&datfile);
		textStream.seek(seekPos);
		while (!textStream.atEnd())
		{
			str = textStream.readLine();
			seekPos += str.size()+1;
			LOG_DEBUG << str;
			if (str.startsWith("header length: "))
				break;
		}
		textStream.seek(seekPos);
	}
	else
	{
		seekPos++;
		datfile.seek(seekPos);
		datStream.setDevice(&datfile);
	}
#if defined(_MSC_VER)
#	pragma message("TODO dynamic resizing of the mapped histogram")
#else
#	warning TODO dynamic resizing of the mapped histogram
#endif
#if 0
	resizeHistogram(0, 0, true, true);
#else
	resizeHistogram(128, 960, true, true);
#endif
	foreach(MesydaqCounter *c, m_counter)
		c->reset();

	QChar		c('0');
	QSharedDataPointer<SD_PACKET> dataBuf(new SD_PACKET);

// header separator : sep0 sep5 sepA sepF
	datStream >> sep1 >> sep2 >> sep3 >> sep4;
	if ((sep1 == sep0) && (sep2 == sep5) && (sep3 == sepA) && (sep4 == sepF))
	{
		LOG_INFO << tr("%1").arg(m_Hist[PositionHistogram]->width());
#if 0
		m_starttime_msec = m_mesydaq->time();
		foreach (MesydaqCounter *c, m_counter)
			c->start(m_starttime_msec);
		setROI(QRectF(0, 0, m_mesydaq->width(), m_mesydaq->height()));
#endif
		if (getNextBlock(datStream, dataBuf->dp))
		{
			quint64 tmp = dataBuf->dp.time[0] + (quint64(dataBuf->dp.time[1]) << 16) + (quint64(dataBuf->dp.time[2]) << 32);
			m_timer->start(tmp / m_timeBase);
			analyzeBuffer(dataBuf);
			++blocks;
			++bcount;
			LOG_INFO << tr("Run ID %1").arg(dataBuf->dp.runID);
		}
		for(; getNextBlock(datStream, dataBuf->dp); ++blocks, ++bcount)
		{
// hand over data buffer for processing
			analyzeBuffer(dataBuf);
			if(!(bcount % 5000))
				QCoreApplication::processEvents();
		}
		LOG_INFO << tr("%1").arg(m_Hist[PositionHistogram]->width());
	}
	datfile.close();
	LOG_INFO << tr("End replay");
	LOG_WARNING << tr("Found %1 data packages").arg(blocks);
	LOG_WARNING << tr("%2 trigger events and %3 neutrons").arg(m_triggers).arg(m_neutrons);
	resizeHistogram(m_Hist[PositionHistogram]->width() ? m_Hist[PositionHistogram]->width() : m_Hist[AmplitudeHistogram]->width(),
			m_Hist[PositionHistogram]->width() ?  m_Hist[PositionHistogram]->height() : m_Hist[AmplitudeHistogram]->height(), false);
	QCoreApplication::processEvents();
	m_status = Idle;
}

/*!
    \fn Measurement::getMean(const HistogramType t, float &mean, float &sigma)

    gives the mean value and the standard deviation of the last position events

    \param t type of the requested histogram
    \param mean mean value
    \param sigma standard deviation
 */
void Measurement::getMean(const HistogramType t, float &mean, float &sigma)
{
	m_Hist[t]->getMean(mean, sigma);
}

/*!
    \fn Measurement::getMean(const HistogramType t, quint16 chan, float &mean, float &sigma)

    gives the mean value and the standard deviation of the last events in the tube chan of the position histogram

    \param t type of the requested histogram
    \param chan the number of the tube
    \param mean mean value
    \param sigma standard deviation
 */
void Measurement::getMean(const HistogramType t, quint16 chan, float &mean, float &sigma)
{
	quint16 tmpChan = mapTube(chan);
	if (tmpChan != 0xFFFF)
		m_Hist[t]->getMean(tmpChan, mean, sigma);
	else
		mean = sigma = 0.0;
}

/**
    \fn Measurement::getMean(const SpectrumType t, float &mean, float &sigma)

    gives the mean value and the standard deviation of the last events in the time spectrum

    \param t type of the requested spectrum
    \param mean mean value
    \param sigma standard deviation of the mean value
    \return mean value
 */
void Measurement::getMean(const SpectrumType t, float &mean, float &sigma)
{
	mean = m_Spectrum[t]->mean(sigma);
}

quint64 Measurement::eventsInROI(const HistogramType t, const QRect &roi)
{
	quint64 tmp = m_Hist[t]->getCounts(roi);
	return tmp;
}

void Measurement::setListFileHeader(const QByteArray& header, bool bInsertHeaderLength)
{
	if (m_mesydaq)
		m_mesydaq->setListFileHeader(header, bInsertHeaderLength);
}

void Measurement::setConfigfilepath(const QString &path)
{
	QFileInfo fi(path);
	if (fi.exists() && fi.isDir())
		m_configPath = path;
	else
		m_configPath = QDir::currentPath();
}

void Measurement::setListfilepath(const QString &path)
{
	LOG_INFO << "1measurement.setListfilepath:" << path << std::endl;
	QFileInfo fi(path);
	if (fi.exists() && fi.isDir())
		m_listPath = QString(path);
	else
		m_listPath = QDir::currentPath();
	
}

void Measurement::setHistfilepath(const QString &path)
{
	QFileInfo fi(path);
	if (fi.exists() && fi.isDir())
		m_histPath = path;
	else
		m_histPath = QDir::currentPath();
}

void Measurement::setListfilename(const QString &name)
{
	if (m_mesydaq)
	{
		QString tmp = name;
		if(!tmp.isEmpty() && tmp.indexOf(".mdat") == -1)
			tmp.append(".mdat");
		m_mesydaq->setListfilename(tmp);
	}
}

void Measurement::setHistfilename(const QString &name)
{
	m_histfilename = name;
	if(!m_histfilename.isEmpty() && m_histfilename.indexOf(".mtxt") == -1)
		m_histfilename.append(".mtxt");
}

void Measurement::setCalibrationfilename(const QString &name)
{
	m_calibrationfilename = name;
	if (!m_calibrationfilename.isEmpty() && m_calibrationfilename.indexOf(".mcal") == -1 &&
		m_calibrationfilename.indexOf(".txt") == -1 && m_calibrationfilename.indexOf(".mesf") == -1)
		m_calibrationfilename.append(".mcal");
}

void Measurement::setConfigfilename(const QString &name)
{
	if (name.isEmpty())
		m_configfile.setFile("mesycfg.mcfg");
	else
		m_configfile.setFile(name);
}

QString Measurement::getConfigfilename(void) const
{
	if (m_configfile.exists())
		return m_configfile.absoluteFilePath();
	else
		return QString("");
}

void Measurement::setSetupType(const Setup val)
{
	m_setup = val;
	m_mesydaq->setSetupType(val);
}

/*!
    \fn bool Measurement::loadSetup(const QString &name)

    Loads the setup from a file. This function should be able to load
    "MesyDAQ" files and also "QMesyDAQ" files (using QSettings class which is
    not easy human readable).

    \note MesyDAQ INI file format is not used correctly, because the section
	  names are not unique: imagine you don't have a single MCPD-8 + MPSD-8 ...

    \param name file name
    \return true if successfully loaded otherwise false
 */
bool Measurement::loadSetup(const QString &name)
{
	setConfigfilename(name);
	if (getConfigfilename().isEmpty())
		return false;

	LOG_INFO <<"Reading configfile "<<getConfigfilename();
	QSettings settings(getConfigfilename(), QSettings::IniFormat);

	settings.beginGroup("MESYDAQ");
	QString	home(getenv("HOME"));
	m_histPath = settings.value("histogramPath", home).toString();
	m_listPath = settings.value("listfilePath", home).toString();
	m_timeBase = settings.value("timebase", 10000).toUInt(); // headertime is in 100ns steps
	QString qzlevel = boost::log::trivial::to_string(SEVERITY_THRESHOLD);
	QString sz = settings.value("debugLevel",qzlevel ).toString();
	m_psdArrangement = Arrangement(settings.value("psdarrangement", "0").toInt());
	
	//SEVERITY_THRESHOLD

	if (sz.toStdString() == boost::log::trivial::to_string(boost::log::trivial::severity_level::debug)) SEVERITY_THRESHOLD = boost::log::trivial::severity_level::debug;
	if (sz.toStdString() == boost::log::trivial::to_string(boost::log::trivial::severity_level::info)) SEVERITY_THRESHOLD = boost::log::trivial::severity_level::info;
	if (sz.toStdString() == boost::log::trivial::to_string(boost::log::trivial::severity_level::warning)) SEVERITY_THRESHOLD = boost::log::trivial::severity_level::warning;
	if (sz.toStdString() == boost::log::trivial::to_string(boost::log::trivial::severity_level::error)) SEVERITY_THRESHOLD = boost::log::trivial::severity_level::error;

	

//	m_acquireListfile = settings.value("listmode", "true").toBool();
	sz = settings.value("calibrationfile", "").toString();
	settings.endGroup();

	m_mesydaq->loadSetup(settings);

	storeLastFile();

	updateSetupType();

	settings.beginGroup("MESYDAQ");
	for (int j = MON1ID; j <= TTL2ID; ++j)
	{
		QPoint p = settings.value(QString("monitor%1").arg(j), QPoint(0, j)).toPoint();
		setMonitorMapping(p.x(), p.y(), j);
	}
	settings.endGroup();

// Calibration file must be read after hardware configuration
	readCalibration(sz, true);

	resizeHistogram(m_mesydaq->width(), m_mesydaq->height());
	return true;
}

void Measurement::updateSetupType(void)
{
	setSetupType(Mpsd);

	QList<int> mcpdList = m_mesydaq->mcpdId();
	for (int i = 0; i < mcpdList.size(); ++i)
	{
		int mod = mcpdList.at(i);
		for (int j = 0; j < 8; ++j)
			switch (m_mesydaq->getModuleId(mod, j))
			{
				case Mesy::ModuleId::MPSTD16 :
					if (m_mesydaq->active(mod, j))
						setSetupType(Mstd);
					break;
				case TYPE_MWPCHR :
					if (m_mesydaq->active(mod, j))
						setSetupType(Mdll2);
					break;
				case TYPE_MDLL :
					if (m_mesydaq->active(mod, j))
						setSetupType(Mdll);
					break;
				default:
					break;
			}
	}
	if (m_setup == Mstd)
	{
		if (m_Spectrum[SingleTubeSpectrum])
			m_Spectrum[SingleTubeSpectrum]->resize(16);
		else
			m_Spectrum[SingleTubeSpectrum] = new Spectrum(16);
	}
	else if (m_setup == Mdll || m_setup == Mdll2)
	{
		if (!m_Spectrum[AmplitudeSpectrum])
			m_Spectrum[AmplitudeSpectrum] = new Spectrum();
	}
	m_width = m_mesydaq->width();
	m_height = m_mesydaq->height();
}

/*!
    \fn bool Measurement::saveSetup(const QString &name)

    Stores the setup in a file. This function stores INI files in format of
    "MesyDAQ" instead of "QMesyDAQ" using QSettings class (which is not easy
    human readable).

    Note: MesyDAQ INI file format is not used correctly, because the section
	  names are not unique: imagine you don't have a single MCPD-8 + MPSD-8 ...

    \param name file name
    \return true if successfully saved otherwise false
 */
bool Measurement::saveSetup(const QString &name, const QString &comment)
{
		
	if(name.isEmpty())
		m_configfile.setFile("mesycfg.mcfg");
	m_configfile.setFile(name);

	if(m_configfile.fileName().indexOf(".mcfg") == -1)
		m_configfile.setFile(m_configfile.absoluteFilePath().append(".mcfg"));

	QSettings settings(m_configfile.absoluteFilePath(), QSettings::IniFormat);

	settings.beginGroup("MESYDAQ");
	settings.setValue("comment", comment);
	settings.setValue("date", QDateTime::currentDateTime().toString(Qt::ISODate));
	settings.setValue("histogramPath", m_histPath);
	settings.setValue("listfilePath", m_listPath);
	settings.setValue("debugLevel", boost::log::trivial::to_string(SEVERITY_THRESHOLD));
	settings.setValue("calibrationfile", m_calibrationfilename);
	settings.setValue("psdarrangement", m_psdArrangement);
	for (int j = MON1ID; j <= TTL2ID; ++j)
	{
		QPair<int, int> p = monitorMapping(j);
		settings.setValue(QString("monitor%1").arg(j), QPoint(p.first, p.second));
	}
	settings.endGroup();

	UserMapCorrection* pUserMapCorrection(dynamic_cast<UserMapCorrection*>(m_posHistMapCorrection));
	if (pUserMapCorrection != NULL)
		pUserMapCorrection->saveCorrectionFile(m_calibrationfilename);

	m_mesydaq->saveSetup(settings);
	settings.sync();
	storeLastFile();
	return true;
}

/*!
    \fn void Measurement::storeLastFile(void)

    stores the last used configuration file name in the global user settings.
 */
void Measurement::storeLastFile(void)
{
        QSettings settings(QSettings::IniFormat, QSettings::UserScope, "MesyTec", "QMesyDAQ");
	settings.setValue("lastconfigfile", getConfigfilename());
	settings.sync();
}

Histogram *Measurement::hist(const HistogramType t) const
{
	return m_Hist[t];
}

quint64	Measurement::mon(const int id) const
{
	return m_counter[id]->value();
}

quint64 Measurement::events() const
{
	return m_events->value();
}

quint64	Measurement::timer() const
{
	return m_timer->value();
}

quint64 Measurement::getHeadertime(void) const
{
	return m_headertime;
}

void Measurement::setHeadertime(quint64 ht)
{
	m_headertime = ht;
}

MapCorrection *&Measurement::posHistMapCorrection()
{
	return m_posHistMapCorrection;
}

Mesydaq2 *Measurement::getMesydaq() const
{
	return m_mesydaq;
}

Setup Measurement::setupType(void) const
{
	return m_setup;
}

QString Measurement::getConfigfilepath(void) const
{
	return m_configPath;
}

QString Measurement::getListfilename(void) const
{
	return m_mesydaq ? m_mesydaq->getListfilename() : "";
}

QString Measurement::getListfilepath(void) const
{
	return m_listPath;
}

QString Measurement::getHistfilename(void) const
{
	return m_histfilename;
}

QString Measurement::getHistfilepath(void) const
{
	return m_histPath;
}

QString Measurement::getCalibrationfilename(void) const
{
	return m_calibrationfilename;
}

bool Measurement::hwstatus(bool *pbAck) const
{
	return m_mesydaq->status(pbAck);
}

Measurement::Mode Measurement::mode(void) const
{
	return m_mode;
}

Measurement::Status Measurement::status(void) const
{
	return m_status;
}

bool Measurement::getWriteProtection() const
{
	return m_mesydaq->getWriteProtection();
}

void Measurement::setWriteProtection(bool b)
{
	m_mesydaq->setWriteProtection(b);
}

Measurement::HistogramFileFormat Measurement::getHistogramFileFormat() const
{
	return m_histogramFileFormat;
}

void Measurement::setRunId(const quint32 runid)
{
	m_mesydaq->setRunId(runid);
}

bool Measurement::getAutoIncRunId() const
{
	return m_mesydaq->getAutoIncRunId();
}

void Measurement::setAutoIncRunId(bool b)
{
	m_mesydaq->setAutoIncRunId(b);
}

quint32 Measurement::runId(void) const
{
	return m_mesydaq->runId();
}

quint16 Measurement::calculateChannel(const quint16 mcpd, const quint8 mpsd, const quint8 channel)
{
	if (m_setup == Mpsd)
		return mcpd * 64 + mpsd * 8 + channel;
	else
		return mcpd * 128 + mpsd * 16 + channel;
}

Measurement::Arrangement Measurement::getPsdArrangement(void) const
{
	return m_psdArrangement;
}

void Measurement::setMonitorMapping(quint16 id, qint8 input, qint8 channel)
{
	QList<int> mcpd = m_mesydaq->mcpdId();
	if (mcpd.contains(id))
	{
		if (input < 0)
			m_monitorMap.remove(channel);
		else
			m_monitorMap[channel] = QPair<int, int>(id, input);
	}
}

qint8 Measurement::monitorMapping(quint16 id, qint8 input) const
{
	return m_monitorMap.key(QPair<int, int>(id, input), -1);
}

QPair<int, int> Measurement::monitorMapping(quint8 channel) const
{
	return m_monitorMap.value(channel, QPair<int, int>(-1, -1));
}
