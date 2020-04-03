#include "coloured_console_sink.h"

void coloured_console_sink::consume(boost::log::record_view const& rec, string_type const& formatted_string)
{
    auto level = rec.attribute_values()["Severity"].extract<boost::log::trivial::severity_level>();
    auto hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hstdout, &csbi);

    SetConsoleTextAttribute(hstdout, get_colour(level.get()));
    std::cout << formatted_string << std::endl;
    SetConsoleTextAttribute(hstdout, csbi.wAttributes);
}

WORD get_colour(boost::log::trivial::severity_level level)
{
    switch (level)
    {
    case boost::log::trivial::trace: return 0x08;
    case boost::log::trivial::debug: return 0x07;
    case boost::log::trivial::info: return 0x0F;
    case boost::log::trivial::warning: return 0x0D;
    case boost::log::trivial::error: return 0x0E;
    case boost::log::trivial::fatal: return 0x0C;
    default: return 0x0F;
    }
}