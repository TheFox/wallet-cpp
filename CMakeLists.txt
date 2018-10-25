cmake_minimum_required(VERSION 3.12.0)
project(Wallet)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_APPENDIX "-dev.1")
set(PROJECT_COPYRIGHT "Copyright (C) 2018 Christian Mayer <https://fox21.at>")

set(CMAKE_CXX_FLAGS "-Wall -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -Wno-unused-variable -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wunused-variable")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

configure_file("${PROJECT_SOURCE_DIR}/src/config.hpp.in" "${PROJECT_SOURCE_DIR}/src/config.hpp" NEWLINE_STYLE LF)

add_executable(wallet
    src/app/wallet.cpp
    src/class/wallet.cpp src/class/wallet.hpp
    src/class/command_factory.cpp src/class/command_factory.hpp
    src/class/command.cpp src/class/command.hpp
    src/class/help_command.cpp src/class/help_command.hpp
    src/class/add_command.cpp src/class/add_command.hpp
    )
target_include_directories(wallet PRIVATE ${PROJECT_SOURCE_DIR}/src)
set_property(TARGET wallet PROPERTY CXX_STANDARD 17)
#target_compile_features(wallet PRIVATE cxx_filesystem)

# Install
# TODO
#install(TARGETS wallet)

set(LIBS)

# fmt
list(APPEND LIBS fmt)
#list(APPEND LIBS fmt-header-only)
#add_definitions(-DFMT_HEADER_ONLY)

# Boost
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_STATIC_RUNTIME     ON)
set(Boost_USE_MULTITHREADED     OFF)
find_package(Boost 1.67.0 COMPONENTS filesystem program_options)
if(Boost_FOUND)
    message(STATUS "Found Boost")
    message(STATUS "Boost INCL ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost LIBS ${Boost_LIBRARIES}")
    include_directories(${Boost_INCLUDE_DIRS})
    list(APPEND LIBS ${Boost_LIBRARIES})
endif()

# yaml-cpp
# TODO

target_link_libraries(wallet ${LIBS})
