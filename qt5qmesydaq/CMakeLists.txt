cmake_minimum_required (VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_definitions(NUCLEO_RATE_TESTING) # Zweistein.TraceSteps.cpp Zweistein.TraceApp.cpp

set(QMESYDAQ_TCP OFF)

set(QMESYDAQ_TANGO OFF)


if(${QMESYDAQ_TCP} STREQUAL ON)
add_compile_definitions(USE_TCP)
message(*****************USE_TCP*****************)
endif()

if(${QMESYDAQ_TANGO} STREQUAL ON)
message(********USE_TANGO*************)
add_compile_definitions(USE_TANGO)
if(UNIX)
set(Tango_Controls_INLCUDE_DIR /usr/include/tango CACHE STRING "Tango_include")
set(Tango_Controls_LIB /usr/lib/x86_64-linux-gnu/libtango.so CACHE STRING "Tango_lib")
endif()
if(MSVC)
set(Tango_Controls_SHARED_LIB_DIR $ENV{TANGO_ROOT}\\win64\\lib\\vc12_dll CACHE STRING "Tango_SHARED_LIB_DIR")
set(Tango_Controls_INLCUDE_DIR "$ENV{TANGO_ROOT}\\win64\\include\\vc12" CACHE STRING "Tango_include")
set(Tango_Controls_LIB "$ENV{TANGO_ROOT}\\win64\\lib\\vc12_dll\\tango.lib" CACHE STRING "Tango_lib")
endif()
endif()


if(UNIX)
message("on linux boost >= 1.71 must be installed, usually by :  sudo apt-get install libboost-all-dev")
message ("BUT:  on Ubuntu 18 or lower boost must be installed from sources:")
message("https://www.boost.org/doc/libs/1_72_0/more/getting_started/unix-variants.html")
message("tar --bzip2 -xf /path/to/boost_1_72_0.tar.bz2")
message("cd boost_1_72_0")
message("./bootstrap.sh --prefix=/usr/")
message("./b2")
message("sudo ./b2 install")
#set(BOOST_ROOT /usr )
#set(Boost_INCLUDE_DIR ${BOOST_ROOT}/include)
endif()
project(qmesydaq)

add_compile_definitions(BOOST_LOG_DYN_LINK)


add_subdirectory (interfaces)
add_subdirectory (qwt5-qt5)
add_subdirectory(lib)
add_subdirectory(qled)
add_subdirectory(qmesydaq)

add_custom_target(copylibs
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:libqmesydaq>
         ${qmesydaq_BINARY_DIR}/qmesydaq

  COMMAND ${CMAKE_COMMAND} -E copy  $<TARGET_FILE:qwt5-qt5>
         ${qmesydaq_BINARY_DIR}/qmesydaq
  
  )


  add_custom_target(copylibsWin

  message(************MSVC copy************************************** )
  COMMAND ${CMAKE_COMMAND} -E  copy ${Tango_Controls_SHARED_LIB_DIR}/zmq.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

  COMMAND ${CMAKE_COMMAND} -E copy  ${Tango_Controls_SHARED_LIB_DIR}/zmqd.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/tango922.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/tango922d.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/omnithread40_vc13_rtd.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/omnithread40_vc13_rt.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/omniORB421_vc13_rtd.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/omniORB421_vc13_rt.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/omniDynamic421_vc13_rtd.dll  ${qmesydaq_BINARY_DIR}/qmesydaq
  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/omniDynamic421_vc13_rt.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

   COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/log4tangod.dll  ${qmesydaq_BINARY_DIR}/qmesydaq
  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/log4tango.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/COS421_vc13_rt.dll  ${qmesydaq_BINARY_DIR}/qmesydaq
  COMMAND ${CMAKE_COMMAND} -E copy ${Tango_Controls_SHARED_LIB_DIR}/COS421_vc13_rtd.dll  ${qmesydaq_BINARY_DIR}/qmesydaq

)

if(${QMESYDAQ_TANGO} STREQUAL ON)
if(MSVC)
add_dependencies(qmesydaq qwt5-qt5 libqmesydaq qled LoopObject TANGOLoop tcploop copylibs copylibsWin)
else()
add_dependencies(qmesydaq qwt5-qt5 libqmesydaq qled LoopObject TANGOLoop tcploop copylibs)
endif()
else()
add_dependencies(qmesydaq qwt5-qt5 libqmesydaq qled LoopObject tcploop copylibs)
endif()




