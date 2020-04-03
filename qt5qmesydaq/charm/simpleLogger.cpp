#include "simpleLogger.h"



void coloring_formatter(
    logging::record_view const& rec, logging::formatting_ostream& strm)
{

    auto severity = rec[logging::BOOST_LOG_VERSION_NAMESPACE::trivial::severity];
    if (severity)
    {
        // Set the color
        switch (severity.get())
        {
        case logging::BOOST_LOG_VERSION_NAMESPACE::trivial::info:
            strm << "\033[32m";
            break;
        case logging::BOOST_LOG_VERSION_NAMESPACE::trivial::warning:
            strm << "\033[33m";
            break;
        case logging::BOOST_LOG_VERSION_NAMESPACE::trivial::error:
        case logging::BOOST_LOG_VERSION_NAMESPACE::trivial::fatal:
            strm << "\033[31m";
            break;
        default:
            break;
        }
    }

    // auto a = expr::stream << logging::BOOST_LOG_VERSION_NAMESPACE::expressions::format_date_time(timestamp, "%Y-%m-%d, %H:%M:%S.%f");

    strm << rec[timestamp] << " "
        << "[" << severity << "]"
        << " - " << rec[expr::smessage];

    if (severity)
    {
        // Restore the default color
        strm << "\033[0m";
    }
}

namespace Zweistein {
    namespace Logger {
        void Add_File_Sink(std::string logfile) {
            typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;
            boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

            // add a logfile stream to our sink
            sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>(logfile));


            // specify the format of the log message
            logging::formatter formatter = expr::stream
                //     << std::setw(7) << std::setfill('0') << line_id << std::setfill(' ') << " | "
                << expr::format_date_time(timestamp, "%Y-%m-%d, %H:%M:%S.%f") << " "
                << "[" << logging::trivial::severity << "]"
                << " - " << expr::smessage;
            sink->set_formatter(formatter);

            // only messages with severity >= SEVERITY_THRESHOLD are written
            sink->set_filter(severity >= SEVERITY_THRESHOLD);

            // "register" our sink
            logging::core::get()->add_sink(sink);

        }
    }
}




BOOST_LOG_GLOBAL_LOGGER_INIT(logger, src::severity_logger_mt) {
    src::severity_logger_mt<boost::log::trivial::severity_level> logger;

    // add attributes
 //   logger.add_attribute("LineID", attrs::counter<unsigned int>(1));     // lines are sequentially numbered
    logger.add_attribute("TimeStamp", attrs::local_clock());             // each log line gets a timestamp
#ifdef WIN32_PRE10OLDSTYLE
    // add a text sink
    typedef sinks::synchronous_sink<class coloured_console_sink> coloured_console_sink_t;
    auto sink = boost::make_shared<coloured_console_sink_t>();
    logging::formatter formatter = expr::stream
        //  << std::setw(7) << std::setfill('0') << line_id << std::setfill(' ') << " | "
        << expr::format_date_time(timestamp, "%Y-%m-%d, %H:%M:%S.%f") << " "
        << "[" << logging::trivial::severity << "]"
        << " - " << expr::smessage;
    sink->set_formatter(formatter);

#else
    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();
    // add "console" output stream to our sink
#pragma message("HERE NEEDS BOOST >=1.71")
    sink->locked_backend().get()->set_auto_newline_mode(boost::log::BOOST_LOG_VERSION_NAMESPACE::sinks::auto_newline_mode::disabled_auto_newline);
    sink->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
    sink->set_formatter(&coloring_formatter);

#endif
    // only messages with severity >= SEVERITY_THRESHOLD are written
    sink->set_filter(severity >= SEVERITY_THRESHOLD);
    // "register" our sink
    logging::core::get()->add_sink(sink);


    return logger;
}