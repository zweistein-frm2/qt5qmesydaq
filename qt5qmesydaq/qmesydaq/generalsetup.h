/***************************************************************************
 *   Copyright (C) 2008 by Gregor Montermann <g.montermann@mesytec.com>    *
 *   Copyright (C) 2009-2014 by Jens Kr�ger <jens.krueger@frm2.tum.de>     *
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
#ifndef GENERAL_SETUP_H
#define GENERAL_SETUP_H

#include <QtWidgets/QDialog>
#include "ui_generalsetup.h"

class Measurement;

/*!
    \class GeneralSetup

    \short This class handles the general settings dialog

    \author Jens Kr&uuml;ger <jens.krueger@frm2.tum.de>
 */
class GeneralSetup : public QDialog, public Ui_GeneralSetup
{
	Q_OBJECT
public:
	GeneralSetup(Measurement *, QWidget * = 0);

	//! \return the path for the configuration files
	QString configFilePath(void);

	//! \return the path for the listmode data files
	QString listFilePath(void);

	//! \return the path for the histogram data file
	QString histFilePath(void);

	//! \return the last run ID
	quint32 lastRunId(void);

	//! \return auto increment run id selection
	bool getAutoIncRunId(void);

	//! \return write protect closed files
	bool getWriteProtection(void);

	//! \return MPSD detector arrangement
	int getArrangement(void) const;

	//! \return histogram file format
	int getHistogramFileFormat(void) const;

	/*!
	    set the last run id
            \param val
         */
	void setLastRunId(const quint32 val);

	//! \return the selected trigger id
	int getTriggerId(void);

private slots:
	void selectConfigpathSlot();

	void selectHistpathSlot();

	void selectListpathSlot();

	void setRunIdSlot();

	void selectAutoIncRunIdSlot();

	void selectWriteProtectSlot();

	void setTriggerId(const int);

private:
	//! store the measurement object
	Measurement 	*m_meas;
};
#endif
