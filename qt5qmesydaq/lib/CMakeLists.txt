# CMakeList.txt : CMake project for Input, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(SIMPLE_LOGGER)
find_package(Qt5 COMPONENTS Core Widgets Gui Svg Network PrintSupport CONFIG REQUIRED)

if(MSVC)
     add_compile_definitions(_WIN32_WINNT=0x0601)
     add_compile_definitions(WIN32_PRE10OLDSTYLE)
else()
#message("on linux boost must be installed :  sudo apt-get install libboost-all-dev")
#set(BOOST_ROOT /usr )
#set(Boost_INCLUDE_DIR ${BOOST_ROOT}/include)
endif()

find_package(magic_enum CONFIG REQUIRED )
#set(Boost_USE_STATIC_LIBS ON) 
#set(Boost_USE_STATIC_RUNTIME ON)  
find_package(Boost 1.71 REQUIRED COMPONENTS filesystem chrono thread  system iostreams log log_setup ) # header only libraries must not be added here

include_directories(${Charm_DIR})

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library (libqmesydaq SHARED)

target_sources(libqmesydaq
  PRIVATE
    calibration.cpp  
    counter.cpp
    datarepeater.cpp
    editormemory.cpp
    histogram.cpp
    linearmapcorrect.cpp
    m2d.cpp
    m2dfactory.cpp
    mapcorrect.cpp
    mappeddetector.cpp
    mappedhistogram.cpp
    mcpd.cpp
    mcpd2.cpp
    mcpd8.cpp
    mdll.cpp
    mdllcorrect.cpp 
    measurement.cpp
    mesydaq2.cpp
    mpsd8.cpp
    mpsd8old.cpp
    mpsd8p.cpp
    mpsd8sadc.cpp
    mpsdfactory.cpp
    mstd16.cpp
    mwpchr.cpp
    networkdevice.cpp
    nomodule.cpp
    pulsertest.cpp
    spectrum.cpp
    streamwriter.cpp
    usermapcorrect.cpp
    Zweistein.TraceSteps.cpp
    ${Charm_DIR}/simpleLogger.cpp
   #the following .h will be passed to MOC 
    counter.h
    datarepeater.h
    histogram.h
    mapcorrect.h
    mappedhistogram.h
    mcpd.h
    mcpd2.h
    mcpd8.h
    mdll.h
    measurement.h
    mesydaq2.h
    mpsd8.h
    mstd16.h
    networkdevice.h
    spectrum.h
    streamwriter.h
    usermapcorrect.h
   
)

target_include_directories (libqmesydaq PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
message("we are on Windows")
target_sources(libqmesydaq
  PRIVATE 
  ${Charm_DIR}/coloured_console_sink.cpp
  )
#set_property(TARGET libqmesydaq APPEND_STRING PROPERTY LINK_FLAGS " /FORCE:MULTIPLE")
set_property(TARGET libqmesydaq PROPERTY DEBUG_POSTFIX d)
target_compile_definitions(libqmesydaq PRIVATE EXTERN_FUNCDECLTYPE=DllExport)
 else()
 target_compile_definitions(libqmesydaq PRIVATE EXTERN_FUNCDECLTYPE=)
 endif()
 

target_compile_definitions(libqmesydaq PRIVATE ASIOEXT_USE_BOOST_ASIO)
target_compile_definitions(libqmesydaq PRIVATE QT_GUI_LIB)
target_compile_definitions(libqmesydaq PRIVATE QT_LARGEFILE_SUPPORT=64)
target_compile_definitions(libqmesydaq PRIVATE _ENABLE_EXTENDED_ALIGNED_STORAGE)
target_compile_definitions(libqmesydaq PRIVATE UNICODE)
target_compile_definitions(libqmesydaq PRIVATE LIBQMESYDAQ_LIB)


target_link_libraries(libqmesydaq PRIVATE  Qt5::Widgets Qt5::Core Qt5::Svg Qt5::Network Qt5::PrintSupport magic_enum::magic_enum ${Boost_LIBRARIES} ${Boost_LOG_LIBRARIES})
set_target_properties(libqmesydaq PROPERTIES PREFIX "")
#target_link_options(libqmesydaq PRIVATE $<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:RELEASE>:-static-libstdc++> $<$<CONFIG:DEBUG>:-static-libstdc++> > PRIVATE $<$<CXX_COMPILER_ID:GNU>:-static-libgcc>  )

target_compile_options(libqmesydaq PRIVATE
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/W3>>
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd26812>>
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4577>>
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4467>>
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4309>>
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4305>>
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4996>>
$<$<CXX_COMPILER_ID:MSVC>:/Zc:wchar_t>
$<$<CXX_COMPILER_ID:MSVC>:/Gd>
 $<$<CXX_COMPILER_ID:GNU>:-fPIC>
)


