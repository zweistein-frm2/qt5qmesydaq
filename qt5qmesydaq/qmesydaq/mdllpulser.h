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
#ifndef MDLL_PULSER_H
#define MDLL_PULSER_H

#include <QtWidgets/QDialog>
#include "ui_mdllpulser.h"

class Mesydaq2;

/*!
    \class MdllSetup

    \short This class handles the setup dialog for setting up the MPSD modules

    \author Gregor Montermann <g.montermann@mesytec.com>
 */
class MdllPulser : public QDialog, public Ui_MdllPulser
{
	Q_OBJECT
public:
	MdllPulser(Mesydaq2 *, QWidget * = 0);

public slots:
	void setMCPD(int = -1);

protected:
	void closeEvent(QCloseEvent *);

private slots:
	void setPulserAmplitude(int);

	void setPulserPosition(int);

	void setPulser(bool);

private:
	void display(int = -1);

	void updatePulser();

private:
	//! The Mesydaq object
	Mesydaq2	*m_theApp;

};
#endif
