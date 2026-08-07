cmake_minimum_required(VERSION 3.10.0)

project(PybindCXX VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
find_package(Python3 3.9 REQUIRED COMPONENTS Interpreter Development)


add_subdirectory(${CMAKE_PROJECT_NAME}/vendor/pybind11)

set(project_directory ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME})
set(vendor_directory ${project_directory}/vendor)

set(fmt_directory ${vendor_directory}/fmt)

pybind11_add_module(spdlogcxx 
	${CMAKE_PROJECT_NAME}/src/PyspdlogTypes.h
	${CMAKE_PROJECT_NAME}/src/Pyspdlog.cpp
)
set(spdlog_directory ${vendor_directory}/spdlog)
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
	${fmt_directory}/src/format.cc
)



pybind11_add_module(yamlcxx 
	${CMAKE_PROJECT_NAME}/src/PyyamlTypes.h
	${CMAKE_PROJECT_NAME}/src/PyyamlFunctions.h
	${CMAKE_PROJECT_NAME}/src/Pyyaml.cpp
)
target_compile_definitions(yamlcxx PRIVATE YAML_CPP_STATIC_DEFINE)
set(yaml_directory ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/vendor/yaml-cpp)
set(yaml-cpp-contrib-sources
	${yaml_directory}/src/contrib/graphbuilder.cpp
	${yaml_directory}/src/contrib/graphbuilderadapter.cpp
)
set(yaml-cpp-sources
	${yaml_directory}/src/binary.cpp
	${yaml_directory}/src/convert.cpp
	${yaml_directory}/src/depthguard.cpp
	${yaml_directory}/src/directives.cpp
	${yaml_directory}/src/emit.cpp
	${yaml_directory}/src/emitfromevents.cpp
	${yaml_directory}/src/emitter.cpp
	${yaml_directory}/src/emitterstate.cpp
	${yaml_directory}/src/emitterutils.cpp
	${yaml_directory}/src/exceptions.cpp
	${yaml_directory}/src/exp.cpp
	${yaml_directory}/src/fptostring.cpp
	${yaml_directory}/src/memory.cpp
	${yaml_directory}/src/node.cpp
	${yaml_directory}/src/node_data.cpp
	${yaml_directory}/src/nodebuilder.cpp
	${yaml_directory}/src/nodeevents.cpp
	${yaml_directory}/src/null.cpp
	${yaml_directory}/src/ostream_wrapper.cpp
	${yaml_directory}/src/parse.cpp
	${yaml_directory}/src/parser.cpp
	${yaml_directory}/src/regex_yaml.cpp
	${yaml_directory}/src/scanner.cpp
	${yaml_directory}/src/scanscalar.cpp
	${yaml_directory}/src/scantag.cpp
	${yaml_directory}/src/scantoken.cpp
	${yaml_directory}/src/simplekey.cpp
	${yaml_directory}/src/singledocparser.cpp
	${yaml_directory}/src/stream.cpp
	${yaml_directory}/src/tag.cpp
)
target_include_directories(yamlcxx PRIVATE
	${yaml_directory}/include
)
target_sources(yamlcxx PRIVATE
	${yaml-cpp-contrib-sources}
	${yaml-cpp-sources}
)

source_group("" FILES
	${CMAKE_PROJECT_NAME}/src/PyspdlogTypes.h
	${CMAKE_PROJECT_NAME}/src/Pyspdlog.cpp
	${CMAKE_PROJECT_NAME}/src/PyyamlTypes.h
	${CMAKE_PROJECT_NAME}/src/PyyamlFunctions.h
	${CMAKE_PROJECT_NAME}/src/Pyyaml.cpp
)

source_group("source" FILES 
	${spdlog_sources}
	${fmt_directory}/src/format.cc
	${yaml-cpp-sources}
	${yaml-cpp-contrib-sources}
)