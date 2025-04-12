cmake_minimum_required(VERSION 3.10)
project(atm
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_library(atm STATIC)
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
