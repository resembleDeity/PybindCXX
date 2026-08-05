cmake_minimum_required(VERSION 3.10.0)

project(PybindCXX VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
find_package(Python3 3.9 REQUIRED COMPONENTS Interpreter Development)


add_subdirectory(${CMAKE_PROJECT_NAME}/vendor/pybind11)



pybind11_add_module(spdlogcxx ${CMAKE_PROJECT_NAME}/src/Pyspdlog.cpp)
set(spdlog-directory ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/vendor/spdlog)
set(SPDLOG_SRCS
    ${spdlog-directory}/src/common.cpp
    ${spdlog-directory}/src/logger.cpp
    ${spdlog-directory}/src/pattern_formatter.cpp
    ${spdlog-directory}/src/spdlog.cpp
    ${spdlog-directory}/src/details/file_helper.cpp
    ${spdlog-directory}/src/details/os_filesystem.cpp
    ${spdlog-directory}/src/details/log_msg.cpp
    ${spdlog-directory}/src/details/async_log_msg.cpp
    ${spdlog-directory}/src/details/err_helper.cpp
    ${spdlog-directory}/src/sinks/base_sink.cpp
    ${spdlog-directory}/src/sinks/basic_file_sink.cpp
    ${spdlog-directory}/src/sinks/rotating_file_sink.cpp
    ${spdlog-directory}/src/sinks/stdout_sinks.cpp
    ${spdlog-directory}/src/sinks/async_sink.cpp
)
if (WIN32)
    list(APPEND SPDLOG_SRCS
    	${spdlog-directory}/src/details/os_windows.cpp
    	${spdlog-directory}/src/sinks/wincolor_sink.cpp
	)
else ()
    list(APPEND SPDLOG_SRCS
        ${spdlog-directory}/src/details/os_unix.cpp
        ${spdlog-directory}/src/sinks/ansicolor_sink.cpp
	)
endif ()
target_include_directories(spdlogcxx PRIVATE
	${spdlog-directory}/include
	${spdlog-directory}/src
	${CMAKE_CURRENT_SOURCE_DIR}/Build/_deps/fmt-src/include
)
target_sources(spdlogcxx PRIVATE
	${SPDLOG_SRCS}
	${CMAKE_CURRENT_SOURCE_DIR}/Build/_deps/fmt-src/src/format.cc
)


pybind11_add_module(yamlcxx ${CMAKE_PROJECT_NAME}/src/Pyyaml.cpp)
target_compile_definitions(yamlcxx PRIVATE YAML_CPP_STATIC_DEFINE)
set(yaml-directory ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/vendor/yaml-cpp)
set(yaml-cpp-contrib-sources
	${yaml-directory}/src/contrib/graphbuilder.cpp
	${yaml-directory}/src/contrib/graphbuilderadapter.cpp
)
set(yaml-cpp-sources
	${yaml-directory}/src/binary.cpp
	${yaml-directory}/src/convert.cpp
	${yaml-directory}/src/depthguard.cpp
	${yaml-directory}/src/directives.cpp
	${yaml-directory}/src/emit.cpp
	${yaml-directory}/src/emitfromevents.cpp
	${yaml-directory}/src/emitter.cpp
	${yaml-directory}/src/emitterstate.cpp
	${yaml-directory}/src/emitterutils.cpp
	${yaml-directory}/src/exceptions.cpp
	${yaml-directory}/src/exp.cpp
	${yaml-directory}/src/fptostring.cpp
	${yaml-directory}/src/memory.cpp
	${yaml-directory}/src/node.cpp
	${yaml-directory}/src/node_data.cpp
	${yaml-directory}/src/nodebuilder.cpp
	${yaml-directory}/src/nodeevents.cpp
	${yaml-directory}/src/null.cpp
	${yaml-directory}/src/ostream_wrapper.cpp
	${yaml-directory}/src/parse.cpp
	${yaml-directory}/src/parser.cpp
	${yaml-directory}/src/regex_yaml.cpp
	${yaml-directory}/src/scanner.cpp
	${yaml-directory}/src/scanscalar.cpp
	${yaml-directory}/src/scantag.cpp
	${yaml-directory}/src/scantoken.cpp
	${yaml-directory}/src/simplekey.cpp
	${yaml-directory}/src/singledocparser.cpp
	${yaml-directory}/src/stream.cpp
	${yaml-directory}/src/tag.cpp
)
target_include_directories(yamlcxx PRIVATE
	${yaml-directory}/include
)
target_sources(yamlcxx PRIVATE
	${yaml-cpp-contrib-sources}
	${yaml-cpp-sources}
)