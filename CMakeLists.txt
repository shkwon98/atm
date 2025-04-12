cmake_minimum_required(VERSION 3.10)
project(atm
    LANGUAGES CXX
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

option(BUILD_SHARED_LIBS "Build shared libraries instead of static" OFF)

add_library(atm)
target_sources(atm
    PRIVATE src/atm.cpp
)
target_include_directories(atm
    PUBLIC include
)
target_compile_features(atm
    PUBLIC cxx_std_17
)
add_library(atm::atm ALIAS atm)

enable_testing()
add_subdirectory(tests)
