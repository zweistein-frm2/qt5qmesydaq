/***************************************************************************
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

#ifndef __CHANNEL_SPIN_BOX_H
#define __CHANNEL_SPIN_BOX_H

#include <QtWidgets/QSpinBox>

/**
 * \short Spinbox to select one of the channels over all modules 
 * \author Jens Kr&uuml;ger <jens.krueger@frm2.tum.de>
 * \version 0.1
 */
class ChannelSpinBox : public QSpinBox
{
Q_OBJECT
public:
	ChannelSpinBox(QWidget *parent = 0);

	virtual void stepBy(int steps);

signals:
	//! this signal will be emitted if the module number over/underruns
	void changeModule(int);
};

#endif
