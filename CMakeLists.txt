cmake_minimum_required(VERSION 3.8.0)

project(WalletCpp VERSION 0.5.0 LANGUAGES CXX)
set(PROJECT_VERSION_APPENDIX "-dev.3")
set(PROJECT_COPYRIGHT "Copyright (C) 2018 Christian Mayer <https://fox21.at>")
set(PROJECT_HOMEPAGE_URL "https://github.com/TheFox/wallet-cpp")
set(PROJECT_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(PROJECT_SHARE_PREFIX "${PROJECT_INSTALL_PREFIX}/share/wallet_cpp")
set(PROJECT_SHARE_RESOURCES_DIR "${PROJECT_SHARE_PREFIX}/resources")

option(WALLETCPP_GNUPLOT_SUPPORT "Turn on/off building with Gnuplot support." OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -Wunused-variable")
set(CMAKE_CXX_FLAGS_TEST "-g -O0 -DDEBUG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Set minimum C++ to 2017 standards.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Config File
configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/src/config.hpp"
    NEWLINE_STYLE LF)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/src")

# yaml-cpp
find_package(yaml-cpp REQUIRED)

# mstch
find_package(mstch REQUIRED)

# Term Color
find_package(termcolor QUIET)

# Catch2
find_package(catch2 QUIET)

# Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_USE_MULTITHREADED OFF)
find_package(Boost 1.62.0 COMPONENTS filesystem program_options date_time)
if (Boost_FOUND)
    message(STATUS "Found Boost")
    message(STATUS "Boost INCL ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost LIBS ${Boost_LIBRARIES}")
endif ()

# Wallet Target
add_executable(wallet
    src/app/wallet.cpp
    src/debug.hpp
    src/fs.hpp
    src/components.cpp src/components.hpp
    src/class/mutable_wallet.cpp src/class/mutable_wallet.hpp
    src/class/immutable_wallet.cpp src/class/immutable_wallet.cpp
    src/class/command/command_options.cpp src/class/command/command_options.hpp
    src/class/command/command_factory.cpp src/class/command/command_factory.hpp
    src/class/command/command.cpp src/class/command/command.hpp
    src/class/command/help_command.cpp src/class/command/help_command.hpp
    src/class/command/add_command.cpp src/class/command/add_command.hpp
    src/class/command/init_command.cpp src/class/command/init_command.hpp
    src/class/command/html_command.cpp src/class/command/html_command.hpp
    src/class/command/list_command.cpp src/class/command/list_command.hpp
    src/class/entry.cpp src/class/entry.hpp
    src/class/container/entry_container.cpp src/class/container/entry_container.hpp
    src/class/accountable.cpp src/class/accountable.hpp
    src/class/html/html_generator.cpp src/class/html/html_generator.hpp
    src/class/html/base_html.cpp src/class/html/base_html.hpp
    src/class/html/index_html.cpp src/class/html/index_html.hpp
    src/class/html/year_html.cpp src/class/html/year_html.hpp
    src/class/html/month_html.cpp src/class/html/month_html.hpp
    src/class/mustache/base_mustache.cpp src/class/mustache/base_mustache.hpp
    src/class/mustache/index_mustache.cpp src/class/mustache/index_mustache.hpp
    src/class/mustache/year_mustache.cpp src/class/mustache/year_mustache.hpp
    src/class/mustache/month_mustache.cpp src/class/mustache/month_mustache.hpp
    src/class/mustache/base_gnuplot.cpp src/class/mustache/base_gnuplot.hpp
    src/class/mustache/total_gnuplot.cpp src/class/mustache/total_gnuplot.hpp
    src/class/mustache/year_gnuplot.cpp src/class/mustache/year_gnuplot.hpp
    resources/css/style.css
    resources/views/index.mustache
    resources/views/year.mustache
    resources/views/month.mustache
    resources/gnuplot/total.mustache
    resources/gnuplot/year.mustache)
target_include_directories(wallet PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_compile_features(wallet PRIVATE
    cxx_noexcept
    cxx_constexpr
    cxx_final
    cxx_deleted_functions
    cxx_override)
get_target_property(wallet_std wallet CXX_STANDARD)
target_include_directories(wallet PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(wallet ${Boost_LIBRARIES} ${YAML_CPP_LIBRARIES})
target_link_libraries(wallet mstch::mstch)

# Test Target
string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
if(CMAKE_BUILD_TYPE_LOWER STREQUAL "test")
    add_executable(test
        src/app/test.cpp
        src/test/entry_test.hpp
        src/components.cpp src/components.hpp
        src/class/entry.cpp src/class/entry.hpp
        src/class/accountable.cpp src/class/accountable.hpp)
    target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(test Catch2::Catch2)
    target_compile_features(test PRIVATE
        cxx_noexcept
        cxx_constexpr
        cxx_final
        cxx_deleted_functions
        cxx_override)
    get_target_property(test_std test CXX_STANDARD)
    target_include_directories(test PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(test ${Boost_LIBRARIES} ${YAML_CPP_LIBRARIES})
endif()

# Install Wallet
install(TARGETS wallet RUNTIME DESTINATION bin)

# Install Resources
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/resources
    DESTINATION ${PROJECT_SHARE_PREFIX})

message(STATUS "CXX_STANDARD wallet ${wallet_std}")
message(STATUS "CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_SYSTEM_PREFIX_PATH ${CMAKE_SYSTEM_PREFIX_PATH}")
message(STATUS "CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH}")
message(STATUS "CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH}")
message(STATUS "CMAKE_INSTALL_LOCALSTATEDIR ${CMAKE_INSTALL_LOCALSTATEDIR}")
message(STATUS "CMAKE_INSTALL_SYSCONFDIR ${CMAKE_INSTALL_SYSCONFDIR}")

message(STATUS "PROJECT_INSTALL_PREFIX ${PROJECT_INSTALL_PREFIX}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_SHARE_PREFIX ${PROJECT_SHARE_PREFIX}")
message(STATUS "PROJECT_SHARE_RESOURCES_DIR ${PROJECT_SHARE_RESOURCES_DIR}")

message(STATUS "YAML_CPP_INCLUDE_DIR ${YAML_CPP_INCLUDE_DIR}")
message(STATUS "YAML_CPP_LIBRARIES ${YAML_CPP_LIBRARIES}")

message(STATUS "Catch2_HEADER_DIR ${Catch2_HEADER_DIR}")

message(STATUS "Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS}")

message(STATUS "WALLETCPP_GNUPLOT_SUPPORT ${WALLETCPP_GNUPLOT_SUPPORT}")
