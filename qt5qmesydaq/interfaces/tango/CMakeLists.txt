# CMakeList.txt : CMake project for Input, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
find_package(Qt5 COMPONENTS Core Widgets Gui Svg Network PrintSupport CONFIG REQUIRED)
find_package(Boost 1.71 REQUIRED COMPONENTS log log_setup ) # header only libraries must not be added here

add_compile_definitions(SIMPLE_LOGGER)

if(MSVC)
    add_compile_definitions(_WIN32_WINNT=0x0601)
else()

endif()

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library (TANGOLoop STATIC TANGOLoop.cpp TANGOLoop.h ClassFactory.cpp )
 
 target_include_directories( TANGOLoop PUBLIC ${Qt5Core_INCLUDE_DIRS}../ ${Qt5Core_INCLUDE_DIRS} ) # sort o a hack to have QtCore/Qwhatever like include
 target_include_directories(TANGOLoop PUBLIC ${Charm_DIR} ${qmesydaq_SOURCE_DIR}/qmesydaq ${CMAKE_SOURCE_DIR}/lib)
 target_include_directories (TANGOLoop PUBLIC ${Boost_INCLUDE_DIR})
message(******************${Tango_Controls_INLCUDE_DIR}*******************)
target_include_directories(TANGOLoop PUBLIC ${Tango_Controls_INLCUDE_DIR} )
target_compile_definitions(TANGOLoop PRIVATE QT_GUI_LIB)
target_compile_definitions(TANGOLoop PRIVATE QT_LARGEFILE_SUPPORT=64)
target_compile_definitions(TANGOLoop PRIVATE _ENABLE_EXTENDED_ALIGNED_STORAGE)
target_compile_definitions(TANGOLoop PRIVATE UNICODE)


#target_link_libraries(TANGOLoop PRIVATE  Qt5::Widgets Qt5::Core Qt5::Svg Qt5::Network Qt5::PrintSupport)

#target_link_options(TANGOLoop PRIVATE $<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:RELEASE>:-static-libstdc++> $<$<CONFIG:DEBUG>:-static-libstdc++> > PRIVATE $<$<CXX_COMPILER_ID:GNU>:-static-libgcc>  )

target_compile_options(TANGOLoop PRIVATE
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


