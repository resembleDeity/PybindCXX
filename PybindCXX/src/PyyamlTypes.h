#pragma once

#include <pybind11/pybind11.h>

#include <yaml-cpp/yaml.h>

// namespaces
namespace py = pybind11;

// yaml names
using EmitterManip = YAML::EMITTER_MANIP;
using Emitter = YAML::Emitter;
using Node = YAML::Node;
