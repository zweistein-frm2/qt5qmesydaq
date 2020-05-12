
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



if(MSVC)
    add_compile_definitions(_WIN32_WINNT=0x0601)
    add_compile_definitions(WIN32_PRE10OLDSTYLE)
else()
#set(BOOST_ROOT /usr )
#set(Boost_INCLUDE_DIR ${BOOST_ROOT}/include)
find_package(Threads)
endif()

add_compile_definitions(SIMPLE_LOGGER)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt5 COMPONENTS Core Widgets Gui Svg Network PrintSupport WebEngineWidgets CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED )

find_package(Boost 1.71 REQUIRED COMPONENTS  filesystem chrono thread  iostreams log log_setup) # header only libraries must not be added here


add_library(LoopObject STATIC Zweistein.LoopObject.cpp Zweistein.LoopObject.h LoopObject.cpp LoopObject.h )

set_property(TARGET LoopObject PROPERTY CXX_STANDARD 14)
 target_include_directories( LoopObject PUBLIC ${Qt5Core_INCLUDE_DIRS}../ ${Qt5Core_INCLUDE_DIRS} ) # sort o a hack to have QtCore/Qwhatever like include
 target_include_directories(LoopObject PUBLIC ${Tango_Controls_INLCUDE_DIR} )
target_compile_definitions(LoopObject PRIVATE QT_GUI_LIB)
target_compile_definitions(LoopObject PRIVATE QT_LARGEFILE_SUPPORT=64)
target_compile_definitions(LoopObject PRIVATE _ENABLE_EXTENDED_ALIGNED_STORAGE)
target_compile_definitions(LoopObject PRIVATE UNICODE)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

target_compile_options(LoopObject PRIVATE
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/W3>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd26812>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4577>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4467>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4309>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4305>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4996>>
  $<$<CXX_COMPILER_ID:MSVC>:/Zc:wchar_t>
  $<$<CXX_COMPILER_ID:MSVC>:/Gd>
 )
 else()
 target_compile_options(LoopObject PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-fPIC>
 )

 endif()



add_executable(qmesydaq )

target_sources(qmesydaq 
  PRIVATE
    caresssetup.cpp
    ChannelSpinBox.cpp
    colormaps.cpp
    colorwidget.cpp
    CommandEvent.cpp
    ConfigFileDialog.cpp
    data.cpp
    datetimelabel.cpp
    doublepresetwidget.cpp
    generalsetup.cpp
    histogramedittablewidget.cpp
    histogrammappingeditor.cpp
    ipaddresswidget.cpp
    main.cpp
    mainwidget.cpp
    mainwindow.cpp
    mcpdsetup.cpp
    MCPDSpinBox.cpp
    mdllpulser.cpp
    mdllsetup.cpp
    mesydaqdata.cpp
    moduleidentificationpage.cpp
    modulemasterpage.cpp
    modulesetup.cpp
    ModuleSpinBox.cpp
    modulestatus.cpp
    modulewizard.cpp
    monitorpresetwidget.cpp
    mpsdpulser.cpp
    MultipleLoopApplication.cpp
    passworddialog.cpp
    plot.cpp
    presetwidget.cpp
    QMesydaqDetectorInterface.cpp
    QtInterface.cpp
    StatusBarEntry.cpp
    #${Charm_DIR}/simpleLogger.cpp
    tcpsetup.cpp
    website.cpp
    zoomer.cpp
    Zweistein.Console.cpp
    caresssetup.h
    ChannelSpinBox.h
    colorwidget.h
    ConfigFileDialog.h
    datetimelabel.h
    doublepresetwidget.h
    generalsetup.h
    histogramedittablewidget.h
    histogrammappingeditor.h
    ipaddresswidget.h
    mainwidget.h
    mainwindow.h
    mcpdsetup.h
    MCPDSpinBox.h
    mdllpulser.h
    mdllsetup.h
    moduleidentificationpage.h
    modulemasterpage.h
    modulesetup.h
    ModuleSpinBox.h
    modulestatus.h
    modulewizard.h
    monitorpresetwidget.h
    mpsdpulser.h
    MultipleLoopApplication.h
    passworddialog.h
    plot.h
    presetwidget.h
    QMesydaqDetectorInterface.h
    QtInterface.h
    StatusBarEntry.h
    tcpsetup.h
    website.h
    qmesydaq.qrc
    additionaleventconfig.ui
    caresssetup.ui
    channelhistogramsetup.ui
    doublepresetwidget.ui
    generalsetup.ui
    histogrammappingeditor.ui
    ipaddresswidget.ui
    mainwidget.ui
    mainwindow.ui
    mcpdsetup.ui
    mdllpulser.ui
    mdllsetup.ui
    moduleidentificationpage.ui
    modulemasterpage.ui
    modulesetup.ui
    modulestatus.ui
    modulewizard.ui
    monitorpresetwidget.ui
    mpsdpulser.ui
    passworddialog.ui
    presetwidget.ui
    StatusBarEntry.ui
    tcpsetup.ui
    website.ui
)


target_include_directories (qmesydaq PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories (qmesydaq PUBLIC ${CMAKE_SOURCE_DIR}/lib)

target_include_directories (qmesydaq PUBLIC ${CMAKE_SOURCE_DIR}/qwt5-qt5/src)
target_include_directories( qmesydaq PUBLIC ${Qt5Core_INCLUDE_DIRS}../ ${Qt5Core_INCLUDE_DIRS} ) # sort o a hack to have QtCore/Qwhatever like include
target_include_directories (qmesydaq PUBLIC ${CMAKE_SOURCE_DIR}/qled/src)
target_include_directories (qmesydaq PUBLIC ${Charm_DIR})


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
message("we are on Windows")
set_target_properties( qmesydaq PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS
)
target_compile_definitions(qmesydaq PRIVATE EXTERN_FUNCDECLTYPE=DllImport)
target_compile_definitions(qmesydaq PRIVATE _WIN32_WINNT=0x0601)
target_compile_definitions(qmesydaq PRIVATE QWT_DLL)
 else()
 message("we are on Linux")
 target_compile_definitions(qmesydaq PRIVATE EXTERN_FUNCDECLTYPE=)
 endif()
 
target_compile_definitions(qmesydaq PRIVATE ASIOEXT_USE_BOOST_ASIO)
target_compile_definitions(qmesydaq PRIVATE QT_GUI_LIB)
target_compile_definitions(qmesydaq PRIVATE QT_LARGEFILE_SUPPORT=64)
target_compile_definitions(qmesydaq PRIVATE _ENABLE_EXTENDED_ALIGNED_STORAGE)
target_compile_definitions(qmesydaq PRIVATE UNICODE)


target_link_libraries(qmesydaq PRIVATE magic_enum::magic_enum ${Boost_LIBRARIES}  Qt5::Widgets Qt5::Core Qt5::Svg Qt5::Network  Qt5::PrintSupport Qt5::WebEngineWidgets)
target_link_libraries (qmesydaq LINK_PUBLIC  qwt5-qt5 libqmesydaq qled LoopObject)

target_link_options(qmesydaq PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wl,-rpath,.>  )

get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
foreach( d ${DirDefs} )
    message( STATUS "Found Define: " ${d} )
    if(${d} STREQUAL USE_TCP)
    #message("USE_TCP Endlich gefunden")
    target_link_libraries (qmesydaq LINK_PUBLIC  tcploop)
    endif()
    if(${d} STREQUAL USE_TANGO)
    #message("USE_TANGO Endlich gefunden")
    target_link_libraries (qmesydaq LINK_PUBLIC  TANGOLoop  ${Tango_Controls_LIB} )
    if(UNIX)
     target_link_libraries (qmesydaq LINK_PUBLIC /usr/lib/x86_64-linux-gnu/libomniORB4.so /usr/lib/x86_64-linux-gnu/libomniZIOP4.so /usr/lib/x86_64-linux-gnu/libomnithread.so  )
    endif()
    endif()
endforeach()

#target_link_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:GNU>:$<$<CONFIG:RELEASE>:-static-libstdc++> $<$<CONFIG:DEBUG>:-static-libstdc++> > PRIVATE $<$<CXX_COMPILER_ID:GNU>:-static-libgcc>  )

message(****************${Boost_LIBRARIES}*********************)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
message("we are on Windows")

target_link_libraries(qmesydaq PRIVATE Qt5::WinMain)
target_compile_options(qmesydaq PRIVATE
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/W3>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd26812>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4577>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4467>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4309>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4305>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4996>>
  $<$<CXX_COMPILER_ID:MSVC>:/Zc:wchar_t>
  $<$<CXX_COMPILER_ID:MSVC>:/Gd>
 )
 else()
 target_compile_options(qmesydaq PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-fPIC>
 )
 #set_property(TARGET qmesydaq APPEND_STRING PROPERTY LINK_FLAGS "-lrt")
  
 endif()



 if(MSVC)
add_custom_command(
        TARGET qmesydaq POST_BUILD
        COMMAND ${Qt5Core_DIR}\\..\\..\\..\\bin\\windeployqt.exe
                ${RUNTIME_OUTPUT_DIRECTORY}qmesydaq.exe
        )
endif()

add_custom_command(
    TARGET qmesydaq POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
         ${CMAKE_CURRENT_SOURCE_DIR}/nucleo_rate_testing/Nucleo0SetRate.py
         ${RUNTIME_OUTPUT_DIRECTORY}nucleo_rate_testing/Nucleo0SetRate.py
    COMMAND ${CMAKE_COMMAND} -E copy
         ${CMAKE_CURRENT_SOURCE_DIR}/nucleo_rate_testing/mesylib.py
         ${RUNTIME_OUTPUT_DIRECTORY}nucleo_rate_testing/mesylib.py

)
 
 
 

