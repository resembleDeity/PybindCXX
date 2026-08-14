cmake_minimum_required(VERSION 3.10.0)

project(PybindCXX VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)



find_package(Python3 3.9 REQUIRED COMPONENTS Interpreter Development)
add_subdirectory(${CMAKE_PROJECT_NAME}/pybind11)

add_subdirectory(${CMAKE_PROJECT_NAME}/spdlogcxx)
add_subdirectory(${CMAKE_PROJECT_NAME}/yamlcxx)