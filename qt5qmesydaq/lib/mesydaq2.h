/***************************************************************************
 *   Copyright (C) 2008 by Gregor Montermann <g.montermann@mesytec.com>    *
 *   Copyright (C) 2009-2020 by Jens Krüger <jens.krueger@frm2.tum.de>     *
 *   Copyright (C) 2011-2020 by Lutz Rossa <rossa@helmholtz-berlin.de>     *
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


#ifndef _MESYDAQ2_H_
#define _MESYDAQ2_H_

#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QtCore/QSize>
#include <QtCore/QMap>

#include "libqmesydaq_global.h"
#include "structures.h"
#include "mdefines.h"
#include "datarepeater.h"
#include "streamwriter.h"
#include "mcpd8.h"


/**
 * \short Mesydaq DAQ object (without any graphical frontend)
 * \author Gregor Montermann <g.montermann@mesytec.com>
 * \author Jens Kr&uuml;ger <jens.krueger@frm2.tum.de>
 * \version 0.9
 */
class LIBQMESYDAQ_EXPORT Mesydaq2 : public QObject
{
	Q_OBJECT

public:
	/**
	 * Default Constructor
	 */
	Mesydaq2();

	/**
	 * Default Destructor
	 */
	virtual ~Mesydaq2();

	void setActive(quint16, quint16, bool);

	void setActive(quint16, quint16, quint8, bool);

	bool active(quint16, quint16, quint16);

	bool active(quint16, quint16);

	void setHistogram(quint16, quint16, bool);

	void setHistogram(quint16, quint16, quint8, bool);

	bool histogram(quint16, quint16, quint16);

	bool histogram(quint16, quint16);

	void scanPeriph(quint16 id);

	void initMcpd(quint8 id);

	void setTimingwidth(quint8 width);

	void writePeriReg(quint16 id, quint16 mod, quint16 reg, quint16 val);

	quint16 readPeriReg(quint16 id, quint16 mod, quint16 reg);

	quint16 capabilities(quint16 id, const bool);

	quint16 getTxMode(quint16 id, const bool = false);

	quint16 getTxMode(quint16 id, quint8 mod);

// list mode oriented methods
	void setStreamWriter(StreamWriter* pStreamWriter);

	/**
	 * sets the file name of a list mode data file
	 *
	 * \param name name of the next list mode data file
	 */
	void setListfilename(const QString &name);

	//! \return name of the current list mode data file
	QString getListfilename() const;

	void setListFileHeader(const QByteArray& header, bool bInsertHeaderLength);

	//! \return header for list mode file
	const QByteArray& getListFileHeader() const;

// configuration file oriented methods
	bool loadSetup(QSettings &);

	bool saveSetup(QSettings &);

	bool checkMcpd(quint8 device);

	//! \returns the number of the first MCPD
	qint16 firstMcpd(void);

	bool isPulserOn();

	bool isPulserOn(quint16 mod);

	bool isPulserOn(quint16 mod, quint8 addr);

	bool getMode(const quint16 mod, quint8 addr);

	quint8 getModuleId(quint16 mod, quint8 addr);

	quint8 getChannels(quint16 mod, quint8 addr);

	quint8 getMdllDataset(quint16 id);

	quint16 getMdllTimingWindow(quint16 id, quint8 val);

	quint8 getMdllEnergyWindow(quint16 id, quint8 val);

	quint8 getMdllSpectrum(quint16 id, quint8 val);

	quint8 getMdllThresholds(quint16 id, quint8 val);

	quint8 getMdllPulser(quint16 id, quint8 val);

	QString getModuleType(quint16 mod, quint8 addr);

	float getModuleVersion(quint16 mod, quint8 addr);

	bool online(quint16 mod, quint8 addr);

	float getGain(quint16 mod, quint8 addr, quint8 chan);

	quint8 getThreshold(quint16 mod, quint8 addr);

	quint8 getPulsChan(quint16 mod, quint8 addr);

	quint8 getPulsAmp(quint16 mod, quint8 addr);

	quint8 getPulsPos(quint16 mod, quint8 addr);

	void getCounterCell(quint16 mod, quint8 cell, quint16 *celldata);

	quint16 getParamSource(quint16 mod, quint16 param);

	quint16 getAuxTimer(quint16 mod, quint16 timer);

	quint64 getParameter(quint16 mod, quint16 param);

	float version(quint16 mod, quint8 addr);

	void setRunId(quint32 runid);

	//! \return the current run ID number
	quint32 runId();

	//! \return selection, if run id should incremented automatically
	bool getAutoIncRunId() const;
	void setAutoIncRunId(bool b);

	//! \return write protect closed files
	bool getWriteProtection() const;
	/**
	 * sets the write protection of the data files
	 *
	 * \param b true enables the write protection
	 */
	void setWriteProtection(bool b);

	quint64 missedData();

	quint64 receivedData();

	quint64 receivedCmds();

	quint64 sentCmds();

	quint64 time();

	float getFirmware(quint16 mod);

	float getFpga(quint16 mod);

	//! \return number of MCPD's
	quint16 numMCPD(void) const;

	//! \return list containing the found MCPD's
	QList<int> mcpdId(void);

        /**
         * gets the list of available MPSD's connected with the MCPD
         *
         * \param id id of the MCPD
         * \return list of id numbers
         */
	QList<int> mpsdId(const int id);

	//! \return list of histogrammed MPSD's connected with the MCPD
	QList<int> histogrammedId(const int id);

        /**
         * gets the list of available channels of a MPSD
         *
         * \param id id of the MCPD
	 * \param mod id of the MPSD at MCPD
         * \return list of id numbers
	 */
	QList<int> channelId(const int id, const int mod);

	bool isMaster(quint16 mod);

	bool isExtsynced(quint16 mod);

	bool isTerminated(quint16 mod);

	bool isSynced() const;

	quint16 width(void);

	quint16 height(void);

	QSize size(void);

	//! Helper function which returns the version number string
	QString libVersion(void) const;

	/**
	 * Helper function, which returns the start channel of a MCPD
	 * in the histogram for given MCPD id
	 *
	 * \param id id of the MCPD
	 */
	quint16 startChannel(quint16 id);

	/**
	 * Helper function which returns the "width" of a MCPD in the
	 * histogram. The width is the number of channels in the histogram
	 * which are connected withe the MCPD
	 *
	 * \param id id of the MCPD
	 * \param end id of the last used MPSD channel
	 */
	quint16 width(quint16 id, quint16 end = 8);

	//! set setup type
	void setSetupType(const Setup val);

	//! read setup type
	Setup setupType() const;

public slots:
	//! analysis thread end
	void threadExit(void);

	void addMCPD(quint8, QString = "192.168.168.121", quint16 = 54321, QString = QString::null, quint16 = 0, QString = "0.0.0.0");

	void writeRegister(quint16 id, quint16 reg, quint16 val);

	void setProtocol(const quint16 id, const QString &mcpdIP, const QString &dataIP = QString("0.0.0.0"), quint16 dataPort = 0, const QString &cmdIP = QString("0.0.0.0"), quint16 cmdPort = 0);

	void getProtocol(const quint16 id, QString &mcpdIP, QString &dataIP, quint16 &dataPort, QString &cmdIP, quint16 &cmdPort) const;

	void setMode(const quint16 id, quint8 addr, bool mode);

	void setPulser(const quint16 mod, quint8 addr, quint8 channel, quint8 position, quint8 amp, bool onoff);

	void setCounterCell(quint16 mod, quint16 source, quint16 trigger, quint16 compare);

	void setParamSource(quint16 mod, quint16 param, quint16 source);

	void setAuxTimer(quint16 mod, quint16 tim, quint16 val);

	void setMasterClock(quint16 mod, quint64);

	void setTimingSetup(quint16 mod, bool master, bool term, bool extsync);

	void setId(quint16 mod, quint8 mcpdid);

	void setGain(quint16 mod, quint8 addr, quint8 channel, quint8 gain);

	void setGain(quint16 mod, quint8 addr, quint8 channel, float gain);

	void setThreshold(quint16 mod, quint8 addr, quint8 thresh);

	void setThreshold(quint16 mod, quint8 addr, quint16 thresh);

	void setMdllThresholds(quint16 mod, quint8 threshX, quint8 threshY, quint8 threshA);

	void setMdllSpectrum(quint16 mod, quint8 shiftX, quint8 shiftY, quint8 scaleX, quint8 scaleY);

	void setMdllDataset(quint16 mod, quint8 set);

	void setMdllTimingWindow(quint16 mod, quint16 xlo, quint16 xhi, quint16 ylo, quint16 yhi);

	void setMdllEnergyWindow(quint16 mod, quint8 elo, quint8 ehi);

	void acqListfile(bool yesno);

	//! \return stream the data into a separate file too
	bool acqListfile() const;

	void autoSaveHistogram(bool yesno);

	//! \return save the histogram data automatically
	bool autoSaveHistogram() const;

	void start(void);

	void startedDaq(void);

	void stop(void);

	void stoppedDaq(void);

	void reset(void);

	void cont(void);

	void allPulserOff();

	void writeListfileHeader(void);

	void writeClosingSignature(void);

	void writeProtectFile(QIODevice* pIODevice);

	void writeBlockSeparator(void);

	void writeHeaderSeparator(void);

	virtual void analyzeBuffer(QSharedDataPointer<SD_PACKET> pPacket);

	/**
	 * will be emitted if the MCPD's has lost his sync (lost = true)
	 * or if it was resynchronized (lost = false)
	 *
	 * \param id id of the MCPD the connection
	 * \param bLost true=lost  false=resynced
	 */
	void lostSync(quint16 id, bool bLost);

public:
	bool status(bool *pbAck = NULL) const;

	QMap<quint16, quint16>& getTubeMapping(void);

signals:
	/**
	 * will be emitted if the status has changed
	 *
	 * \param str the status as string
	 */
	void statusChanged(const QString &str);

	/**
	 * will be emitted if new data packet reached from one of the MCPD's
	 *
	 * \param pPacket data packet
	 */
	void analyzeDataBuffer(QSharedDataPointer<SD_PACKET> pPacket);

	//! a new data package from one of the MCPD's received
	void newCmdPackageReceived();

	//! a new header time received
	void headerTimeChanged(quint64);

	/**
	 * will be emitted if one of the MCPD's has lost his sync (bLost = true)
         * or was resynchronized (bLost = false)
	 *
	 * \param id id of the MCPD lost the connection
	 * \param bLost true=lost  false=resynced
	 */
	void syncLost(quint16 id, bool bLost);

protected:
	void timerEvent(QTimerEvent *event);

private slots:
	void setHeadertime(quint64 ht);

private:
	void clear();

	QHash<int, MCPD8 *>	m_mcpd;

private:
	static const quint16	sep0 = 0x0000;
	static const quint16	sep5 = 0x5555;
	static const quint16	sepA = 0xAAAA;
	static const quint16	sepF = 0xFFFF;

private:
	QThread*	m_pThread;

	//! acquisition is active
	bool            m_bRunning;

	//! hardware acknowledge of acquisition status
	bool            m_bRunAck;

	bool		m_acquireListfile;

	bool		m_autoSaveHistogram;

	//! currently used list mode file
	QString		m_listfilename;

	StreamWriter*	m_pDatStream;
	DataRepeater*	m_pDatSender;

	quint8		m_timingwidth;

	QByteArray	m_datHeader;
	bool		m_bInsertHeaderLength;

	//! time stamp for the start of measurement
	quint64		m_starttime_msec;

	//! current run ID
	quint32		m_runId;

	bool		m_bAutoIncRunId;

	//! write protect closed files
	bool		m_bWriteProtect;

	//! mapping vector for the histogrammed tubes
	QMap<quint16, quint16>	m_tubeMapping;

	//! setup type
	Setup		m_setup;
};



#endif // _MESYDAQ2_H_
