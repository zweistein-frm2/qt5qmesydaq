/***************************************************************************
 *   Copyright (C) 2019 by Andreas Langhoff <andreas.langhoff@frm2.tum.de> *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation;                                         *
 ***************************************************************************/
#ifndef ZWEISTEIN_TRACESTEPS_H
#define ZWEISTEIN_TRACESTEPS_H
#pragma once

#define DllExport   __declspec( dllexport )
#define DllImport  __declspec( dllimport )

#ifndef Q_MOC_RUN

//#include <boost/filesystem.hpp>
#define BOOST_CHRONO_VERSION 2
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
//#include <boost/locale.hpp>

namespace Zweistein {
	
	void TraceStep0(void* p);
	void TraceStep1(int queueseize);
	
}
extern EXTERN_FUNCDECLTYPE boost::mutex coutGuard;
extern EXTERN_FUNCDECLTYPE boost::thread_group worker_threads;

#endif

#endif
