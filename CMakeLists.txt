cmake_minimum_required(VERSION 3.12.0)
project(WalletCpp)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION_APPENDIX "-dev.1")
set(PROJECT_COPYRIGHT "Copyright (C) 2018 Christian Mayer <https://fox21.at>")

set(CMAKE_CXX_FLAGS "-Wall -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -Wno-unused-variable -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -Wunused-variable")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

configure_file("${PROJECT_SOURCE_DIR}/src/config.hpp.in" "${PROJECT_SOURCE_DIR}/src/config.hpp" NEWLINE_STYLE LF)

add_executable(wallet
    src/app/wallet.cpp
    src/class/mutable_wallet.cpp src/class/mutable_wallet.hpp
    src/class/immutable_wallet.cpp src/class/immutable_wallet.cpp
    src/class/command_factory.cpp src/class/command_factory.hpp
    src/class/command.cpp src/class/command.hpp
    src/class/help_command.cpp src/class/help_command.hpp
    src/class/add_command.cpp src/class/add_command.hpp
    src/class/entry.cpp src/class/entry.hpp)
target_include_directories(wallet PRIVATE ${PROJECT_SOURCE_DIR}/src)
set_property(TARGET wallet PROPERTY CXX_STANDARD 17)
target_compile_features(wallet PRIVATE cxx_noexcept)
get_target_property(wallet_std wallet CXX_STANDARD)

# Install
install(TARGETS wallet RUNTIME DESTINATION /usr/local/bin)

include(ExternalProject)

# Term Color
ExternalProject_Add(termcolor_project
    GIT_REPOSITORY https://github.com/ikalnytskyi/termcolor.git
    GIT_TAG origin/master
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "")
ExternalProject_Get_Property(termcolor_project SOURCE_DIR)
target_include_directories(wallet PRIVATE ${SOURCE_DIR}/include)
add_library(termcolor INTERFACE IMPORTED)
add_dependencies(termcolor termcolor_project)

# fmt
#ExternalProject_Add(fmt_project
#    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#    GIT_TAG origin/master
#    CONFIGURE_COMMAND ""
#    BUILD_COMMAND ""
#    INSTALL_COMMAND "")
#ExternalProject_Get_Property(fmt_project SOURCE_DIR)
#target_include_directories(wallet PRIVATE ${SOURCE_DIR}/include)
#add_library(fmt INTERFACE IMPORTED)
#add_dependencies(fmt fmt_project)

# yaml-cpp
ExternalProject_Add(yamlcpp_project
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG origin/master
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "")
ExternalProject_Get_Property(yamlcpp_project SOURCE_DIR)
target_include_directories(wallet PRIVATE ${SOURCE_DIR}/include)
add_library(yamlcpp INTERFACE IMPORTED)
add_dependencies(yamlcpp yamlcpp_project)

set(LIBS)

# Boost
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_STATIC_RUNTIME     ON)
set(Boost_USE_MULTITHREADED     OFF)
find_package(Boost 1.67.0 COMPONENTS filesystem program_options)
if(Boost_FOUND)
    message(STATUS "Found Boost")
    message(STATUS "Boost INCL ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost LIBS ${Boost_LIBRARIES}")
    target_include_directories(wallet PRIVATE ${Boost_INCLUDE_DIRS})
    list(APPEND LIBS ${Boost_LIBRARIES})
endif()

# yaml-cpp
# TODO

target_link_libraries(wallet ${LIBS})

message(STATUS "CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER}")
message(STATUS "CXX_STANDARD ${wallet_std}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
