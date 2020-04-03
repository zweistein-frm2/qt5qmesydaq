#include "Zweistein.LoopObject.h"

#ifdef USE_TANGO
#include "../interfaces/tango/TANGOLoop.h"
#else
#ifdef USE_TCP
#include "../interfaces/tcp/TCPLoop.h"
#endif
#endif



namespace Zweistein {
	LoopObject* get(std::string  szArgument, std::string  szParameter) {
		LoopObject* loop(NULL);
#ifdef USE_TANGO
		if (szArgument == "-n")
#ifdef WIN32
		{
			std::string envadd = "TANGO_HOST=" + szParameter;
			putenv(envadd.c_str());
		}
#else
			setenv("TANGO_HOST", szParameter.c_str(), 1);
#endif
		loop = new TANGOLoop;
#endif

#ifdef USE_TCP
		loop = new TCPLoop;
#endif
		return loop;
	}
	
}