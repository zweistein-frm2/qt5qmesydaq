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

#ifndef PULSER_TEST_H
#define PULSER_TEST_H

#include <QtCore/QList>

class Mesydaq2;

#include "libqmesydaq_global.h"


struct puls
{
	quint16	mod;
	quint8	addr;
	quint8	channel;
	quint8	position;
	quint8	amp;
	int	onTime;
};


class LIBQMESYDAQ_EXPORT PulserTest
{
	PulserTest();
public:
	static QList<puls> sequence(Mesydaq2 *, quint8 amp1 = 30, quint8 amp2 = 60);
};

#endif

