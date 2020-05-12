/***************************************************************************
 *   Copyright (C) 2013-2015 by Stefan Rainow <stefan.rainow@frm2.tum.de>  *
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

#ifndef MCPD_8INPUTDIALOG_H
#define MCPD_8INPUTDIALOG_H

#include <inputdialog.h>

class QLineEdit;


class MCPD_8InputDialog : public InputDialog
{
    Q_OBJECT

public:
    MCPD_8InputDialog(QString name, QString toolTip, QString ip,
                      int port, int id, QWidget *parent=NULL);
    QString getNewIP()
        {return newIP;}
    int getNewID()
        {return newID;}
    int getNewPort()
        {return newPort;}

public slots:
    void changeNewIP(QString ip);
    void changeNewPort(QString port);
    void changeNewID(QString id);

private:
    QString newIP;
    QLineEdit *ipEdit;
    int newPort;
    QLineEdit *portEdit;
    QLineEdit *idEdit;
    int newID;



};

#endif // MCPD_8INPUTDIALOG_H