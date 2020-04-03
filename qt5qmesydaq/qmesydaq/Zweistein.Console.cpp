/***************************************************************************
 *   Copyright (C) 2019 by Andreas Langhoff <andreas.langhoff@frm2.tum.de> *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation;                                         *
 ***************************************************************************/

#include <boost/process.hpp>
#include <boost/atomic.hpp>
#include "Zweistein.Console.h"
#include "Zweistein.TraceApp.h"
#include "Zweistein.TraceSteps.h"
#include "Mesytec.hpp"
#include "Mcpd8.DataPacket.hpp"
#include "Zweistein.PrettyBytes.hpp"
#include <boost/dll/runtime_symbol_info.hpp>

boost::atomic<bool> stopall(false);
boost::atomic<bool> daqrunning(false);
boost::atomic<long> nucleorate(0);
boost::mutex updateDisplayVariablesGuard;

namespace Zweistein {

	void DaqStarted(bool b) {
		if (daqrunning != b) {
			if (b == false) SetNucleo0Rate(0);
			if (b == true) SetNucleo0Rate(165000);
			
		}
		daqrunning = b;
		

	}
	boost::chrono::system_clock::time_point  _lastupdate;
	
	unsigned long long _misseddata = 0;
	void TraceUpdateDisplay(boost::chrono::system_clock::time_point  tp, unsigned long long misseddata) {
		boost::mutex::scoped_lock lock(updateDisplayVariablesGuard);
		_lastupdate=tp;
		_misseddata = misseddata;
	}

	void SetNucleo0Rate(long rate) {
#ifdef NUCLEO_RATE_TESTING
		if (rate > 1850000) {
			boost::mutex::scoped_lock lock(coutGuard);
			std::cout << "ERROR: SetNucleo0Rate(" << rate << ") : > MAXRATE" << std::endl;
			return;
		}
		namespace bp = boost::process;
		boost::filesystem::path p = bp::search_path("python");
		boost::system::error_code ec0;
		boost::filesystem::path py_script = boost::dll::program_location(ec0);
		py_script = py_script.remove_filename();
		py_script /= "nucleo_rate_testing";
		py_script.append("Ncleo0SetRate.py");
		
		std::string cmdline = p.string() + " "+py_script.string() + " " + std::to_string(rate);
		std::error_code ec;
		bp::child c(cmdline);
		c.wait_for(std::chrono::seconds(3), ec);
		if (c.running()) {
			c.terminate(ec);
			{
				boost::mutex::scoped_lock lock(coutGuard);
				std::cout << "ERROR: SetNucleo0Rate("<<rate<<") " << cmdline << std::endl;
			}
		}
		else {
			if (!ec && c.exit_code()==0) nucleorate = rate;
			{
				boost::mutex::scoped_lock lock(coutGuard);
				std::cout << "NUCLEO NEW RATE:" << nucleorate << " Events/second" << std::endl;
			}
		}
#endif

	}
#ifdef WIN32
	void BindCrtHandlesToStdHandles(bool bindStdIn, bool bindStdOut, bool bindStdErr)
	{
		// Re-initialize the C runtime "FILE" handles with clean handles bound to "nul". We do this because it has been
		// observed that the file number of our standard handle file objects can be assigned internally to a value of -2
		// when not bound to a valid target, which represents some kind of unknown internal invalid state. In this state our
		// call to "_dup2" fails, as it specifically tests to ensure that the target file number isn't equal to this value
		// before allowing the operation to continue. We can resolve this issue by first "re-opening" the target files to
		// use the "nul" device, which will place them into a valid state, after which we can redirect them to our target
		// using the "_dup2" function.
		if (bindStdIn)
		{
			FILE* dummyFile;
			freopen_s(&dummyFile, "nul", "r", stdin);
		}
		if (bindStdOut)
		{
			FILE* dummyFile;
			freopen_s(&dummyFile, "nul", "w", stdout);
		}
		if (bindStdErr)
		{
			FILE* dummyFile;
			freopen_s(&dummyFile, "nul", "w", stderr);
		}

		// Redirect unbuffered stdin from the current standard input handle
		if (bindStdIn)
		{
			HANDLE stdHandle = GetStdHandle(STD_INPUT_HANDLE);

			if (stdHandle != INVALID_HANDLE_VALUE)
			{
				int fileDescriptor = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
				if (fileDescriptor != -1)
				{
					FILE* file = _fdopen(fileDescriptor, "r");
					if (file != NULL)
					{
						int dup2Result = _dup2(_fileno(file), _fileno(stdin));
						if (dup2Result == 0)
						{
							setvbuf(stdin, NULL, _IONBF, 0);
						}
					}
				}
			}
		}

		// Redirect unbuffered stdout to the current standard output handle
		if (bindStdOut)
		{
			HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			if (stdHandle != INVALID_HANDLE_VALUE)
			{
				int fileDescriptor = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
				if (fileDescriptor != -1)
				{
					FILE* file = _fdopen(fileDescriptor, "w");
					if (file != NULL)
					{
						int dup2Result = _dup2(_fileno(file), _fileno(stdout));
						if (dup2Result == 0)
						{
							setvbuf(stdout, NULL, _IONBF, 0);
						}
					}
				}
			}
		}

		// Redirect unbuffered stderr to the current standard error handle
		if (bindStdErr)
		{
			HANDLE stdHandle = GetStdHandle(STD_ERROR_HANDLE);
			if (stdHandle != INVALID_HANDLE_VALUE)
			{
				int fileDescriptor = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
				if (fileDescriptor != -1)
				{
					FILE* file = _fdopen(fileDescriptor, "w");
					if (file != NULL)
					{
						int dup2Result = _dup2(_fileno(file), _fileno(stderr));
						if (dup2Result == 0)
						{
							setvbuf(stderr, NULL, _IONBF, 0);
						}
					}
				}
			}
		}

		// Clear the error state for each of the C++ standard stream objects. We need to do this, as attempts to access the
		// standard streams before they refer to a valid target will cause the iostream objects to enter an error state. In
		// versions of Visual Studio after 2005, this seems to always occur during startup regardless of whether anything
		// has been read from or written to the targets or not.
		if (bindStdIn)
		{
			std::wcin.clear();
			std::cin.clear();
		}
		if (bindStdOut)
		{
			std::wcout.clear();
			std::cout.clear();
		}
		if (bindStdErr)
		{
			std::wcerr.clear();
			std::cerr.clear();
		}
	}
#endif

	void endMonitoring() {

		stopall = true;
		DaqStarted(false);
		worker_threads.join_all();
		{
			boost::mutex::scoped_lock lock(coutGuard);
			std::cout << "endMonitoring() exiting..." << std::endl;
		}
	}
	
	unsigned long long missed_reported = 0;
	
	static void monitoring() {
		int secondscounter = 0;
		int maxdelay = 8;
		do {
			boost::this_thread::sleep_for(boost::chrono::seconds(1));
			unsigned long long newmissed;
			boost::chrono::system_clock::time_point tmp ;
			{
				boost::mutex::scoped_lock lock(updateDisplayVariablesGuard);
				tmp = _lastupdate;
				newmissed = _misseddata - missed_reported;
				if (newmissed > 0) {
					missed_reported = _misseddata;
					boost::mutex::scoped_lock lock(coutGuard);
					std::cout << std::endl << boost::chrono::time_fmt(boost::chrono::timezone::local) << boost::chrono::system_clock::now() << ": " << "MISSED " << newmissed << " BUFFER(s)" << std::endl;

				}
			
			}
			boost::chrono::duration<double> sec = boost::chrono::system_clock::now() - tmp;
			double delay = sec.count();
			if (!daqrunning) continue;
			if(delay>maxdelay){
					boost::mutex::scoped_lock lock(coutGuard);
					std::cout << "display lagging " <<std::setprecision(2)<<delay<< " seconds"<< std::endl;
				
			}
			if (secondscounter > 60) {
					secondscounter = 0;
					long newrate =  (delay<maxdelay?105L:90L)*nucleorate/100L;
					SetNucleo0Rate(newrate);
					
				}
			secondscounter++;
			

		} while (!stopall);

		{
			boost::mutex::scoped_lock lock(coutGuard);
			std::cout << "exiting monitoring()" << std::endl;
		}
	}

	void startMonitoring() {

		worker_threads.create_thread([] {Zweistein::monitoring(); });


	}
}