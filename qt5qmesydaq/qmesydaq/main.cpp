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
#include "Zweistein.ThreadPriority.hpp"
#include <QtWidgets/QSplashScreen>
#include <QtCore/QSettings>
#include <QtGui/QIcon>

#include "LoopObject.h"
#include "QMesydaqDetectorInterface.h"
#include "MultipleLoopApplication.h"
#include "mainwindow.h"

#include "Zweistein.Logger.hpp"
#include "qt_glue_std.hpp"
#include "Zweistein.Console.h"
#include "../lib/Zweistein.TraceSteps.h"
#include <boost/dll/runtime_symbol_info.hpp>
#include "Zweistein.LoopObject.h"

#if defined(_MSC_VER)
#include <io.h>
#include <FCNTL.H>
#endif



const char* g_szShortUsage =
#ifdef USE_TANGO
	"[-n=<tango_host>] "
#endif
	"[-f|--file|--config|-nf|--nofile|--noconfig]";
const char* g_szLongUsage =
#ifdef USE_TANGO
	"  -n=<tango_host> set environment variable TANGO_HOST\n"
#endif
	"  -f=<file>\n  --file=<file>\n  --config=<file>\n" \
	"               load configuration from file\n" \
	"  -nf\n  --nofile\r\n  --noconfig   do not load last configuration automatically";

//EXTERN_FUNCDECLTYPE SEVERITY_THRESHOLD = boost::log::trivial::info;

int main(int argc, char **argv)
{
#if defined(_MSC_VER)
	//Open the Console
	int hCrt;
	FILE *hf;

	AllocConsole();

	hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	hf = _fdopen( hCrt, "w" );
	*stdout = *hf;
	setvbuf(stdout, NULL, _IONBF, 0);

	Zweistein::BindCrtHandlesToStdHandles(true, true, true);

	std::locale l = std::locale("DE");
	std::cout << "User-preferred locale setting is " << l.name().c_str() << std::endl;
	std::cout.imbue(l);

#endif

	
	LOG_WARNING << " Hello now!" << std::endl;

	boost::system::error_code ec;
	boost::filesystem::path p = boost::dll::program_location(ec);
	Zweistein::Logger::Add_File_Sink(p.string() + ".log");

	Zweistein::Thread::CheckSetUdpKernelBufferSize();


	MultipleLoopApplication app(argc, argv);
	QStringList 		argList = app.arguments();
	LoopObject 		*loop(NULL);
	QString 		szLoadConfiguration(QString::null);
	Q_INIT_RESOURCE(qled);
	Zweistein::startMonitoring();
	
	for (int i = 1; i < argList.size(); ++i)
	{
		QString szArgument = argList[i], szParameter;
		bool bSeparatedParameter(false);
		if (szArgument.indexOf('=') >= 0)
		{
			int iPos = szArgument.indexOf('=');
			szParameter = szArgument.mid(iPos + 1);
			szArgument.remove(iPos, szArgument.size() - iPos);
		}
		else
		{
			szParameter = argList[i];
			bSeparatedParameter = true;
		}
		if (szArgument == "-f" || szArgument == "--file" || szArgument == "--config")
		{
			// load this configuration file
			if (szLoadConfiguration.isEmpty())
				szLoadConfiguration = szParameter;
			if (bSeparatedParameter)
				++i;
		}
		else if (szArgument == "-nf" || szArgument == "--nofile" || szArgument == "--noconfig")
		{
			// load no configuration
			szLoadConfiguration = "";
		}

		loop = Zweistein::get(szArgument.toStdString(), szParameter.toStdString());
	}
#ifdef USE_TANGO
	if (!getenv("TANGO_HOST"))
	{
		LOG_ERROR << QObject::tr("Environment variable \"TANGO_HOST\" is not set")<<std::endl;
		LOG_ERROR << QObject::tr("You may set it explicitly in the command shell") << std::endl;
		LOG_ERROR << QObject::tr("or by using command line option -n='tango_host:port'") << std::endl;
	}
#endif

	if (loop)
		app.setLoopObject(loop);
#if QT_VERSION < 0x050000
	app.setStyle(new QPlastiqueStyle());
#endif

	QPixmap pixmap(":/images/mesytec.png");

	QSplashScreen splash(pixmap);
	splash.show();
	app.processEvents();

	app.setOrganizationName("MesyTec");
	app.setOrganizationDomain("mesytec.com");
	app.setApplicationName("QMesyDAQ");
	app.setWindowIcon(QIcon(":/images/logo32.png"));

	MainWindow mainWin;

	if (loop)
	{
		app.setQtInterface(new QMesyDAQDetectorInterface);
		app.setLoopEventReceiver(mainWin.centralWidget());
		QObject::connect(loop, SIGNAL(terminated()), mainWin.centralWidget(), SLOT(quitContinue()));
		QObject::connect(loop, SIGNAL(finished()), mainWin.centralWidget(), SLOT(quitContinue()));
	}
	app.processEvents();

	if (szLoadConfiguration.isNull())
	{
		// get last configuration file name
		
		QSettings settings(QSettings::IniFormat, QSettings::UserScope, app.organizationName(), app.applicationName());
		szLoadConfiguration = settings.value("lastconfigfile", "mesycfg.mcfg").toString();
	}
	app.processEvents();

	// load configuration
	mainWin.doLoadConfiguration(szLoadConfiguration);

	mainWin.updateStatusBar();

	app.processEvents();
	splash.finish(&mainWin);

	mainWin.show();

	return app.exec();
}
