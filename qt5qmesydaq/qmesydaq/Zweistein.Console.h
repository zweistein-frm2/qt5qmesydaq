/***************************************************************************
 *   Copyright (C) 2019 by Andreas Langhoff <andreas.langhoff@frm2.tum.de> *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation;                                         *
 ***************************************************************************/

#ifndef ZWEISTEIN_CONSOLE_H
#define ZWEISTEIN_CONSOLE_H
#pragma once
#ifdef WIN32
#include <windows.h>
#include <io.h>
#else
#include <stdio.h>
#endif
#include <fcntl.h>
#include <iostream>
namespace Zweistein {
	void startMonitoring();
	void endMonitoring();
#ifdef WIN32
	 void BindCrtHandlesToStdHandles(bool bindStdIn, bool bindStdOut, bool bindStdErr);
#endif	 
	 void SetNucleo0Rate(long rate);
	
}
#endif
