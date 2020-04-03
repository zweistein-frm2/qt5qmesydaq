/***************************************************************************
 *   Copyright (C) 2002 by Gregor Montermann <g.montermann@mesytec.com>    *
 *   Copyright (C) 2008 by Lutz Rossa <rossa@hmi.de>                       *
 *   Copyright (C) 2009-2020 by Jens Krüger <jens.krueger@frm2.tum.de>     *
 *   Copyright (C) 2010 by Alexander Lenz <alexander.lenz@frm2.tum.de>     *
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

#include <QDateTime>
#include <QSettings>
#include <QEventLoop>
#include <QThread>
#include <QFileInfo>

#include "TCPLoop.h"
#include "MultipleLoopApplication.h"
#include "QMesydaqDetectorInterface.h"

#include "remoteserver.h"
#include "mdefines.h"

#include "Zweistein.Logger.hpp"
#include "qt_glue_std.hpp"
TCPLoop::TCPLoop(QtInterface * /* interface */)
	: m_server(NULL)
	, m_tcpport(14716)
	, m_interface(NULL)
	, m_runid(0)
	, m_histo(0)
	, m_thread(NULL)
	, m_settings(NULL)
{
	setObjectName("TCPLoop");
	m_thread = new QThread;
	moveToThread(m_thread);
	m_thread->start(/* QThread::HighestPriority */);
}

TCPLoop::~TCPLoop()
{
	if (m_thread)
	{
		m_thread->quit();
		m_thread->wait();
		delete m_thread;
		m_thread = NULL;
	}
	if (m_settings)
	{
		m_settings->endGroup();
		delete m_settings;
		m_settings = NULL;
	}
}

QString TCPLoop::version(void)
{
	return "TCP  VERSION";
}

void TCPLoop::runLoop()
{
	MultipleLoopApplication *app = dynamic_cast<MultipleLoopApplication*>(QApplication::instance());
	if (!app)
	{
		LOG_ERROR << "not a MultipleLoopApplication";
		return;
	}

	m_settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, qApp->organizationName(), qApp->applicationName());
	m_settings->beginGroup("TCP");
	m_tcpport = m_settings->value("port", "14716").toUInt();
	m_runid = m_settings->value("runid", "0").toUInt();
	m_histo = m_settings->value("histogramtype", "0").toUInt();

	m_server = new RemoteServer(/* this */);
	if (!m_server->listen(QHostAddress::Any, m_tcpport))
		LOG_ERROR << tr("Unable to start the communication service: %1").arg(m_server->errorString());
	else
	{
		m_interface = dynamic_cast<QMesyDAQDetectorInterface*>(app->getQtInterface());
		connect(m_server, SIGNAL(help()), this, SLOT(help()), Qt::DirectConnection);
		connect(m_server, SIGNAL(start()), this, SLOT(start()), Qt::DirectConnection);
		connect(m_server, SIGNAL(stop()), this, SLOT(stop()), Qt::DirectConnection);
		connect(m_server, SIGNAL(clear()), this, SLOT(clear()), Qt::DirectConnection);
		connect(m_server, SIGNAL(reset()), this, SLOT(reset()), Qt::DirectConnection);
		connect(m_server, SIGNAL(timer(const quint32)), this, SLOT(presetTimer(const quint32)), Qt::DirectConnection);
		connect(m_server, SIGNAL(monitor(const quint8, const quint32)), this, SLOT(presetMonitor(const quint8, const quint32)), Qt::DirectConnection);
		connect(m_server, SIGNAL(event(const quint32)), this, SLOT(presetEvent(const quint32)), Qt::DirectConnection);
		connect(m_server, SIGNAL(status()), this, SLOT(status()), Qt::DirectConnection);
		connect(m_server, SIGNAL(histogram()), this, SLOT(histogram()), Qt::DirectConnection);
		connect(m_server, SIGNAL(timer()), this, SLOT(timer()), Qt::DirectConnection);
		connect(m_server, SIGNAL(event()), this, SLOT(event()), Qt::DirectConnection);
		connect(m_server, SIGNAL(monitor(const quint8)), this, SLOT(monitor(const quint8)), Qt::DirectConnection);
		connect(m_server, SIGNAL(histogram(bool)), this, SLOT(histogram(bool)), Qt::DirectConnection);
		connect(m_server, SIGNAL(histogram(const QString &)), this, SLOT(histogram(const QString &)), Qt::DirectConnection);
		connect(m_server, SIGNAL(listmode(void)), this, SLOT(listmode(void)),  Qt::DirectConnection);
		connect(m_server, SIGNAL(listmode(bool)), this, SLOT(listmode(bool)), Qt::DirectConnection);
		connect(m_server, SIGNAL(listmode(const QString &)), this, SLOT(listmode(const QString &)), Qt::DirectConnection);
		connect(m_server, SIGNAL(histogramFile(void)), this, SLOT(histogramFile(void)), Qt::DirectConnection);
		connect(m_server, SIGNAL(histogramType(void)), this, SLOT(histogramType(void)), Qt::DirectConnection);
		connect(m_server, SIGNAL(histogramType(const QString &)), this, SLOT(histogramType(const QString &)), Qt::DirectConnection);
		connect(m_server, SIGNAL(histogramSave(void)), this, SLOT(histogramSave(void)), Qt::DirectConnection);
		connect(m_server, SIGNAL(listmodeFile(void)), this, SLOT(listmodeFile(void)), Qt::DirectConnection);
		if (m_interface)
		{
			m_interface->setHistogramFileName(m_settings->value("lasthistofile", "tcphistfile00000.mtxt").toString());
			m_interface->setListFileName(m_settings->value("lastlistfile", "tcplistfile00000.mdat").toString());
		}

		LOG_ERROR << "TCPLoop: start event loop";
		do
		{
			app->processEvents(QEventLoop::AllEvents, 10);
		} while (true);
	}
}

void TCPLoop::help(void)
{
	m_server->sendAnswer("MESYDAQ HELP\n"
	"at the moment are the following commands implemented:\n"
	"actions:\n"
	"\tMESYDAQ [START|STOP|CLEAR|RESET]\n"
	"sets:\n"
	"\tMESYDAQ [TIMER|EVENT|MONITOR1|MONITOR2] PRESETVAL\n"
	"queries:\n"
	"\tMESYDAQ STATUS -> MESYDAQ [STARTED|STOPPED]\n"
	"\n"
	"\tMESYDAQ GET HISTOGRAM -> Histogram in Mesytec histogram format\n"
	"\tMESYDAQ GET TIMER -> timer\n"
	"\tMESYDAQ GET EVENT -> events over all\n"
	"\tMESYDAQ GET MONITOR[1|2] -> monitors\n"
	"configs set:\n"
	"\tMESYDAQ CONFIG LISTMODE [ON|OFF] -> switches save listmode data on|off\n"
	"\tMESYDAQ CONFIG LISTMODE FILE file -> sets the listmode file name to file\n"
	"\n"
	"\tMESYDAQ CONFIG HISTOGRAM [ON|OFF] -> switches save histogram data on|off\n"
	"\tMESYDAQ CONFIG HISTOGRAM FILE file -> sets the histogram file name to file\n"
	"\tMESYDAQ CONFIG HISTOGRAM TYPE [RAW|MAPPED|AMPLITUDE] -> sets the type for histogram reading\n"
	"configs read:\n"
	"\tMESYDAQ CONFIG LISTMODE -> [ON|OFF]\n"
	"\tMESYDAQ CONFIG LISTMODE FILE -> filename\n"
	"\n"
	"\tMESYDAQ CONFIG HISTOGRAM -> [ON|OFF]\n"
	"\tMESYDAQ CONFIG HISTOGRAM TYPE -> [RAW|MAPPED|AMPLITUDE]\n"
	"\tMESYDAQ CONFIG HISTOGRAM FILE -> filename\n"
	"help:\n"
	"\tMESYDAQ HELP\n"
	);
}

void TCPLoop::start(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");

	if (m_interface->getListMode())
	{
		QString listFile = m_interface->getListFileName();
		listFile = incNumber(listFile);
		m_interface->setListFileName(listFile);
		m_settings->setValue("lastlistfile", listFile);
	}

	if (m_interface->getHistogramMode())
	{
		QString histFile = m_interface->getHistogramFileName();
		histFile = incNumber(histFile);
		m_interface->setHistogramFileName(histFile);
		m_settings->setValue("lasthistofile", histFile);
	}
	LOG_ERROR << "MESYDAQ START";
	m_interface->start();
}

void TCPLoop::stop(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	m_interface->stop();
}

void TCPLoop::clear(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	LOG_ERROR << "MESYDAQ STOP";
	m_interface->clear();
}

void TCPLoop::reset(void)
{
	LOG_ERROR << "MESYDAQ RESET";
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
}

void TCPLoop::presetTimer(const quint32 input)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	LOG_ERROR << "MESYDAQ TIMER " << input;
	m_interface->selectCounter(TCT, true, input);
}

void TCPLoop::presetMonitor(const quint8 mon, const quint32 input)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	LOG_ERROR << "MESYDAQ MONITOR " << mon << " " << input;
	m_interface->selectCounter(mon - 1, true, input);
}

void TCPLoop::presetEvent(const quint32 input)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	LOG_ERROR << "MESYDAQ EVENT " << input;
	m_interface->selectCounter(EVCT, true, input);
}

void TCPLoop::status(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	switch (m_interface->status())
	{
		case 1:
			LOG_ERROR << "MESYDAQ RUNNING";
			m_server->sendAnswer("MESYDAQ RUNNING\n");
			break;
		case 0:
		default:
			LOG_ERROR << "MESYDAQ STOPPED";
			m_server->sendAnswer("MESYDAQ STOPPED\n");
			break;
	}
}

void TCPLoop::histogram(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");

	QList<quint64> tmpList;
	quint16 width(1),
		height(1);
// complete histogram
	if (1)
	{
		LOG_ERROR << "MESYDAQ GET HISTOGRAM " << m_histo;
		QSize s = m_interface->readHistogramSize(m_histo);
		width = s.width();
		height = s.height();
		tmpList = m_interface->readHistogram(m_histo);
	}
// spectrogram
	else
	{
// 1 1 1 value
		LOG_ERROR << "MESYDAQ GET SPECTROGRAM";
		tmpList = m_interface->readDiffractogram();
//		tmp.push_back(tmpList.count());
//		tmp.push_back(1);
//		tmp.push_back(1);
	}
	LOG_ERROR << "Histogram size: " << width << "x" << height;
	QString tmp = formatHistogram(width, height, tmpList);
	m_server->sendAnswer(tmp);
}

QString TCPLoop::formatHistogram(quint32 width, quint32 height, const QList<quint64> histo)
{
	quint64 totalCounts(0);
	for (qint32 i = 0; i < histo.size(); ++i)
		totalCounts += histo[i];
	QString s;
	QString t;
	// Title
	t =	"mesydaq3 Histogram File    " + QDateTime::currentDateTime().toString ("dd.MM.yy  hh:mm:ss") + "\r\n"
		"\r\n"
		"Comment:\r\n"
//      t += view->comment->text ();
		"\r\n"
		"Acquisition Time\r\n"
//      t += doc->cpu1->elapsedTime;
		"\r\n"
		"Total Counts\r\n";
//      t += doc->hist->totalCounts;
		t += s.setNum(totalCounts) + "\r\n"
		"\r\n"
		+ QString("XY data: 1 row title (%1 channels), position data in columns").arg(width) + "\r\n"
		"\t";
	for (quint32 i = 0; i < width; i++)
		t += s.setNum(i) + "\t";
	t += "\r\n";
	for (quint32 i = 0; i < height; i++)
	{
		t += s.setNum(i) + "\t";
		quint32 row = i * width;
		for (quint32 j = 0; j < width; j++)
			t += s.setNum(histo[row + j]) + "\t";
		t += "\r\n";
	}
	t += "\r\n";
	return t;
}

void TCPLoop::timer(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	QString s;
	double tmp = m_interface->readCounter(TCT);
	s.setNum(tmp);
	LOG_ERROR << "MESYDAQ GET TIMER " << s;
	m_server->sendAnswer(s + "\n");
}

void TCPLoop::event(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	QString s;
	quint64 tmp = m_interface->readCounter(EVCT);
	s.setNum(tmp);
	LOG_ERROR << "MESYDAQ GET EVENTS " << s;
	m_server->sendAnswer(s + "\n");
}

void TCPLoop::monitor(const quint8 mon)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	QString s;
	quint64 tmp = m_interface->readCounter(mon - 1);
	s.setNum(tmp);
	LOG_ERROR << "MESYDAQ GET MONITOR" << mon << " " << s;
	m_server->sendAnswer(s + "\n");
}

void TCPLoop::histogram(bool writeHistogram)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	LOG_ERROR << "MESYDAQ CONFIG HISTOGRAM " << writeHistogram;
	m_interface->setHistogramMode(writeHistogram);
}

void TCPLoop::histogram(const QString &histogramfile)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	m_interface->setHistogramFileName(histogramfile);
	LOG_ERROR << "MESYDAQ CONFIG HISTOGRAM FILE " << histogramfile;
	m_settings->setValue("lasthistofile", histogramfile);
}

void TCPLoop::sendOnOff(bool val)
{
	m_server->sendAnswer(QString(val ? "ON" : "OFF") + '\n');
}

void TCPLoop::listmode(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	bool tmp = m_interface->getListMode();
	LOG_ERROR << "MESYDAQ GET CONFIG LISTMODE " << tmp;
	sendOnOff(tmp);
}

void TCPLoop::listmode(bool writeListmode)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	LOG_ERROR << "MESYDAQ CONFIG LISTMODE " << writeListmode;
	m_interface->setListMode(writeListmode, true);
}

void TCPLoop::listmode(const QString &listmodefile)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	LOG_ERROR << "MESYDAQ GET CONFIG LISTMODE FILE " << listmodefile;
	m_interface->setListFileName(listmodefile);
	m_settings->setValue("lastlistfile", listmodefile);
}

void TCPLoop::histogramFile(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	QString file = m_interface->getHistogramFileName();
	LOG_ERROR << "MESYDAQ GET CONFIG HISTOGRAM FILE " << file;
	m_server->sendAnswer(file + '\n');
}

void TCPLoop::histogramType(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	switch (m_histo)
	{
		case CorrectedPositionHistogram:
			LOG_ERROR << "MESYDAQ GET CONFIG HISTOGRAM TYPE MAPPED";
			m_server->sendAnswer("MAPPED\n");
			break;
		case AmplitudeHistogram:
			LOG_ERROR << "MESYDAQ GET CONFIG HISTOGRAM TYPE AMPLITUDE";
			m_server->sendAnswer("AMPLITUDE\n");
			break;
		case PositionHistogram:
			LOG_ERROR << "MESYDAQ GET CONFIG HISTOGRAM TYPE RAW";
			m_server->sendAnswer("RAW\n");
			break;
		default:
			m_server->sendAnswer("MESYDAQ NOTOK\n");
	}
}

void TCPLoop::histogramType(const QString &type)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	QString tmp = type.toUpper();
	LOG_ERROR << "MESYDAQ CONFIG HISTOGRAM TYPE " << tmp;
	if (tmp == "MAPPED")
		m_histo = CorrectedPositionHistogram;
	else if (tmp == "AMPLITUDE")
		m_histo = AmplitudeHistogram;
	else if (tmp == "RAW")
		m_histo = PositionHistogram;
	else
	{
		m_server->sendAnswer("MESYDAQ NOTOK\n");
		return;
	}
	m_settings->setValue("histogramtype", m_histo);
}

void TCPLoop::histogramSave(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	bool tmp = m_interface->getHistogramMode();
	LOG_ERROR << "MESYDAQ GET CONFIG HISTOGRAM " << tmp;
	sendOnOff(tmp);
}

void TCPLoop::listmodeFile(void)
{
	if (!m_interface)
		m_server->sendAnswer("MESYDAQ NOTOK\n");
	QString listfile = m_interface->getListFileName();
	LOG_ERROR << "MESYDAQ GET CONFIG LISTMODE FILE " << listfile;
	m_server->sendAnswer(listfile + '\n');
}

QString TCPLoop::incNumber(const QString &val)
{
	QString tmpString(val);
	QFileInfo fi(val);
	QString baseName = fi.baseName();
	QString ext(fi.completeSuffix());
	if (fi.completeSuffix().isEmpty())
		ext = "mdat";
	long currIndex(0);
	if (baseName.length() > 5)
	{
		currIndex = baseName.mid(baseName.length() - 5).toLong();
		if (currIndex)
			baseName.truncate(baseName.length() - 5);
	}
	QString tmp = QString::number(++currIndex);
	int pos = tmpString.indexOf(baseName);
	pos += baseName.length();
	tmpString.truncate(pos);
	for (int i = tmp.length(); i < 5; ++i)
		tmpString += '0';
	tmpString += tmp;
	tmpString += '.' + ext;
	return tmpString;
}
