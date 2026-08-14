set(yaml_directory ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp)

pybind11_add_module(yamlcxx 
	Pyyaml.cpp
	PyyamlFunctions.h
	PyyamlTypes.h
)
target_compile_definitions(yamlcxx PRIVATE YAML_CPP_STATIC_DEFINE)
set(yaml_contrib_sources
	${yaml_directory}/src/contrib/graphbuilder.cpp
	${yaml_directory}/src/contrib/graphbuilderadapter.cpp
)
set(yaml_sources
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
	${yaml_contrib_sources}
	${yaml_sources}
)

source_group("" FILES
	Pyyaml.cpp
	PyyamlFunctions.h
	PyyamlTypes.h
)

source_group("source" FILES 
	${yaml_contrib_sources}
	${yaml_sources}
)