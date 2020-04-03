/***************************************************************************
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

#ifndef __STATUS_BAR_ENTRY_H
#define __STATUS_BAR_ENTRY_H

#include <QtWidgets/QFrame>
#include "ui_StatusBarEntry.h"

/**
 * \short Box to display a text in the status bar
 * \author Jens Kr&uuml;ger <jens.krueger@frm2.tum.de>
 * \version 0.1
 */
class StatusBarEntry : public QFrame, public Ui_StatusBarEntry
{
	Q_OBJECT
public:
	StatusBarEntry(const QString &text, QWidget *parent = 0)
		: QFrame(parent)
//		, Ui_StatusBarEntry()
	{
		setupUi(this);
		setText(text);
	}

	virtual void setText(const QString &text)
	{
		label->setText(text);
	}
};

#endif
