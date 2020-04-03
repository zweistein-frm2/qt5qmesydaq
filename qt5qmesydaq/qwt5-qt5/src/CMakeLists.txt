# CMakeList.txt : CMake project for Input, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

if(${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC")
    add_compile_definitions(_WIN32_WINNT=0x0601)
endif()
add_compile_definitions(QWT_DLL) 
add_compile_definitions(QWT_MAKEDLL)
add_compile_definitions(_ENABLE_EXTENDED_ALIGNED_STORAGE)
add_compile_definitions(UNICODE)

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt5 COMPONENTS Core Widgets Gui Svg PrintSupport CONFIG REQUIRED)

# Add source to this project's executable.
add_library (qwt5-qt5 SHARED)

target_include_directories (qwt5-qt5 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(qwt5-qt5
  PRIVATE
	 qwt_abstract_scale.cpp
	 qwt_abstract_scale_draw.cpp
	 qwt_abstract_slider.cpp
	 qwt_analog_clock.cpp
	 qwt_arrow_button.cpp
	 qwt_clipper.cpp
	 qwt_color_map.cpp
	 qwt_compass.cpp
	 qwt_compass_rose.cpp
	 qwt_counter.cpp
	 qwt_curve_fitter.cpp
	 qwt_data.cpp
	 qwt_dial.cpp
	 qwt_dial_needle.cpp
	 qwt_double_interval.cpp
	 qwt_double_range.cpp
	 qwt_double_rect.cpp
	 qwt_dyngrid_layout.cpp
	 qwt_event_pattern.cpp
	 qwt_interval_data.cpp
	 qwt_knob.cpp
	 qwt_layout_metrics.cpp
	 qwt_legend.cpp
	 qwt_legend_item.cpp
	 qwt_magnifier.cpp
	 qwt_math.cpp
	 qwt_paint_buffer.cpp
	 qwt_painter.cpp
	 qwt_panner.cpp
	 qwt_picker.cpp
	 qwt_picker_machine.cpp
	 qwt_plot.cpp
	 qwt_plot_axis.cpp
	 qwt_plot_canvas.cpp
	 qwt_plot_curve.cpp
	 qwt_plot_dict.cpp
	 qwt_plot_grid.cpp
	 qwt_plot_item.cpp
	 qwt_plot_layout.cpp
	 qwt_plot_magnifier.cpp
	 qwt_plot_marker.cpp
	 qwt_plot_panner.cpp
	 qwt_plot_picker.cpp
	 qwt_plot_print.cpp
	 qwt_plot_printfilter.cpp
	 qwt_plot_rasteritem.cpp
	 qwt_plot_rescaler.cpp
	 qwt_plot_scaleitem.cpp
	 qwt_plot_spectrogram.cpp
	 qwt_plot_svgitem.cpp
	 qwt_plot_xml.cpp
	 qwt_plot_zoomer.cpp
	 qwt_raster_data.cpp
	 qwt_round_scale_draw.cpp
	 qwt_scale_div.cpp
	 qwt_scale_draw.cpp
	 qwt_scale_engine.cpp
	 qwt_scale_map.cpp
	 qwt_scale_widget.cpp
	 qwt_slider.cpp
	 qwt_spline.cpp
	 qwt_symbol.cpp
	 qwt_text.cpp
	 qwt_text_engine.cpp
	 qwt_text_label.cpp
	 qwt_thermo.cpp
	 qwt_wheel.cpp

	  qwt_abstract_scale.h
	 qwt_abstract_scale_draw.h
	 qwt_abstract_slider.h
	 qwt_analog_clock.h
	 qwt_arrow_button.h
	 qwt_clipper.h
	 qwt_color_map.h
	 qwt_compass.h
	 qwt_compass_rose.h
	 qwt_counter.h
	 qwt_curve_fitter.h
	 qwt_data.h
	 qwt_dial.h
	 qwt_dial_needle.h
	 qwt_double_interval.h
	 qwt_double_range.h
	 qwt_double_rect.h
	 qwt_dyngrid_layout.h
	 qwt_event_pattern.h
	 qwt_interval_data.h
	 qwt_knob.h
	 qwt_layout_metrics.h
	 qwt_legend.h
	 qwt_legend_item.h
	 qwt_magnifier.h
	 qwt_math.h
	 qwt_paint_buffer.h
	 qwt_painter.h
	 qwt_panner.h
	 qwt_picker.h
	 qwt_picker_machine.h
	 qwt_plot.h
	 qwt_plot_canvas.h
	 qwt_plot_curve.h
	 qwt_plot_dict.h
	 qwt_plot_grid.h
	 qwt_plot_item.h
	 qwt_plot_layout.h
	 qwt_plot_magnifier.h
	 qwt_plot_marker.h
	 qwt_plot_panner.h
	 qwt_plot_picker.h
	 qwt_plot_printfilter.h
	 qwt_plot_rasteritem.h
	 qwt_plot_rescaler.h
	 qwt_plot_scaleitem.h
	 qwt_plot_spectrogram.h
	 qwt_plot_svgitem.h
	 qwt_plot_zoomer.h
	 qwt_raster_data.h
	 qwt_round_scale_draw.h
	 qwt_scale_div.h
	 qwt_scale_draw.h
	 qwt_scale_engine.h
	 qwt_scale_map.h
	 qwt_scale_widget.h
	 qwt_slider.h
	 qwt_spline.h
	 qwt_symbol.h
	 qwt_text.h
	 qwt_text_engine.h
	 qwt_text_label.h
	 qwt_thermo.h
	 qwt_wheel.h

	 qwt5-qt5_resource.rc
 )

set_property(TARGET qwt5-qt5 PROPERTY DEBUG_POSTFIX d)
target_link_libraries(qwt5-qt5 PRIVATE Qt5::Widgets Qt5::Core Qt5::Svg )
target_compile_options(qwt5-qt5 PRIVATE
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/W3>>
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd26812>>
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4577>>
$<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:MSVC>:/wd4467>>
$<$<CXX_COMPILER_ID:MSVC>:/Zc:wchar_t>
$<$<CXX_COMPILER_ID:MSVC>:/Gd>
$<$<CXX_COMPILER_ID:GNU>:-fPIC>
)
