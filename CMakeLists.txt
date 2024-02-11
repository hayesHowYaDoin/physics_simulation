include(cmake/app.cmake)

cmake_minimum_required(VERSION 3.5)

project(physics_simulation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

build_physics_simulation()

target_sources(physics_simulation
  PRIVATE
    src/particle.h
)
