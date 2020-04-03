
#pragma once
#include <boost/log/sinks/basic_sink_backend.hpp>

class coloured_console_sink : public boost::log::sinks::basic_formatted_sink_backend<char, boost::log::sinks::synchronized_feeding>
{
public:
    static void consume(boost::log::record_view const& rec, string_type const& formatted_string);
};

#include <iostream>
#define NOMINMAX
#include <windows.h>
#ifdef ERROR 
#undef ERROR
#endif

#include <boost/log/trivial.hpp>
#include <boost/log/attributes/value_extraction.hpp>
#include <boost/log/attributes/attribute_value.hpp>

WORD get_colour(boost::log::trivial::severity_level level);





