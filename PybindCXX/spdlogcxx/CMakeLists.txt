set(spdlog_directory ${CMAKE_CURRENT_SOURCE_DIR}/spdlog)
set(fmt_directory ${CMAKE_CURRENT_SOURCE_DIR}/fmt)
set(fmt_sources ${fmt_directory}/src/format.cc)

pybind11_add_module(spdlogcxx 
	Pyspdlog.cpp
	PyspdlogFunctions.h
	PyspdlogTypes.h
)
target_compile_options(spdlogcxx PRIVATE /utf-8)
set(spdlog_sources
    ${spdlog_directory}/src/common.cpp
    ${spdlog_directory}/src/logger.cpp
    ${spdlog_directory}/src/pattern_formatter.cpp
    ${spdlog_directory}/src/spdlog.cpp
    ${spdlog_directory}/src/details/file_helper.cpp
    ${spdlog_directory}/src/details/os_filesystem.cpp
    ${spdlog_directory}/src/details/log_msg.cpp
    ${spdlog_directory}/src/details/async_log_msg.cpp
    ${spdlog_directory}/src/details/err_helper.cpp
    ${spdlog_directory}/src/sinks/base_sink.cpp
    ${spdlog_directory}/src/sinks/basic_file_sink.cpp
    ${spdlog_directory}/src/sinks/rotating_file_sink.cpp
    ${spdlog_directory}/src/sinks/stdout_sinks.cpp
    ${spdlog_directory}/src/sinks/async_sink.cpp
)
if (WIN32)
    list(APPEND spdlog_sources
    	${spdlog_directory}/src/details/os_windows.cpp
    	${spdlog_directory}/src/sinks/wincolor_sink.cpp
	)
else ()
    list(APPEND spdlog_sources
        ${spdlog_directory}/src/details/os_unix.cpp
        ${spdlog_directory}/src/sinks/ansicolor_sink.cpp
	)
endif ()
target_include_directories(spdlogcxx PRIVATE
	${spdlog_directory}/include
	${spdlog_directory}/src
	${fmt_directory}/include
)
target_sources(spdlogcxx PRIVATE
	${spdlog_sources}
	${fmt_sources}
)

source_group("" FILES
	Pyspdlog.cpp
	PyspdlogFunctions.h
	PyspdlogTypes.h
)

source_group("source" FILES 
	${spdlog_sources}
	${fmt_sources}
)