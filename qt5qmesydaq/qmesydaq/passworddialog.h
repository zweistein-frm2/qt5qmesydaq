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
#ifndef PASSWORD_DIALOG_H
#define PASSWORD_DIALOG_H

#include <QtWidgets/QDialog>
#include <QCryptographicHash>
#include "ui_passworddialog.h"

class QMouseEvent;

/*!
    \class PasswordDialog

    \short This class handles the password input

    \author Jens Kr&uuml;ger <jens.krueger@frm2.tum.de>
 */
class PasswordDialog : public QDialog, protected Ui_PasswordDialog
{
	Q_OBJECT
public:
	//! Constructor
	PasswordDialog(QWidget *parent = 0)
		: QDialog(parent)
	{
    		setupUi(this);
		passwordInput->setText("");
	}

	//! returns the encrypted hash for the user typed input
	QString password(void)
	{
		return QCryptographicHash::hash(passwordInput->text().toLatin1().data(), QCryptographicHash::Md5).toHex();
	}
};
#endif
