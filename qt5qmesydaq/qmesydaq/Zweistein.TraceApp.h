#ifndef ZWEISTEIN_TRACEAPPS_H
#define ZWEISTEIN_TRACEAPPS_H
#pragma once
#include <QtCore/QtCore>


#define BOOST_CHRONO_VERSION 2
#include <boost/chrono.hpp>
namespace Zweistein {
	void TraceUpdateDisplay(boost::chrono::system_clock::time_point tp, unsigned long long misseddata);
	void DaqStarted(bool b);
}

#endif
