/********************************************************************************
 *   Copyright (C) 2019-2020 by Andreas Langhoff <andreas.langhoff@frm2.tum.de> *
 *   This program is free software; you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation;                                              *
 ********************************************************************************/
#
#include "Zweistein.TraceSteps.h"
#include "Mesytec.hpp"
#include "Mcpd8.DataPacket.hpp"
#include "Zweistein.PrettyBytes.hpp"
#include "Zweistein.Logger.hpp"
#include <boost/atomic.hpp>


EXTERN_FUNCDECLTYPE boost::log::trivial::severity_level SEVERITY_THRESHOLD = boost::log::trivial::info;

EXTERN_FUNCDECLTYPE boost::mutex coutGuard;
EXTERN_FUNCDECLTYPE boost::thread_group worker_threads;

namespace Zweistein {

	
	static boost::chrono::system_clock::time_point start= boost::chrono::system_clock::now();
	boost::atomic<long long> count = 0;
	long long lastcount = 0;
	long maxsizeque = 0;
	void TraceStep0(void* p) {
		Mcpd8::DataPacket* dp = reinterpret_cast<Mcpd8::DataPacket*>(p);
		count+=dp->numEvents();
		boost::chrono::milliseconds elapsed = boost::chrono::duration_cast<boost::chrono::milliseconds> (boost::chrono::system_clock::now() - start);
		if (elapsed.count() > 1000) {
			double evtspersecond = elapsed.count() != 0 ? (double)(count - lastcount) / ((double)elapsed.count() / 1000) : 0;
			lastcount = count;
			{
				boost::mutex::scoped_lock lock(coutGuard);
				std::cout << "\r" << "max queuesize=" << maxsizeque << " ";
				maxsizeque = 0;
				std::cout <<std::setprecision(0) << std::fixed << evtspersecond << " Events/s, (" << Zweistein::PrettyBytes((size_t)(evtspersecond * sizeof(Mesy::Mpsd8Event))) << "/s)\t\t";// << std::endl;
				//std::cout << *dp;
			}
			start = boost::chrono::system_clock::now();
		}
	}
	void TraceStep1(int queusize) {
		if (queusize > maxsizeque) maxsizeque= queusize;

	}

}


