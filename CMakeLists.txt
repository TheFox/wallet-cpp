cmake_minimum_required(VERSION 3.8.0)

project(WalletCpp LANGUAGES CXX)
set(PROJECT_VERSION_APPENDIX "-dev.8f")
set(PROJECT_COPYRIGHT "Copyright (C) 2018 Christian Mayer <https://fox21.at>")
set(PROJECT_HOMEPAGE_URL "https://github.com/TheFox/wallet-cpp")
set(PROJECT_SHARE_PATH "share/wallet_cpp")

# Options
message(STATUS "Set options")
set(PROJECT_VERSION_FULL "N/A" CACHE STRING "Version Full")
set(PROJECT_VERSION_HASH "N/A" CACHE STRING "Version Hash")
set(PROJECT_SHARE_PREFIX "${CMAKE_INSTALL_PREFIX}/${PROJECT_SHARE_PATH}" CACHE STRING "Share prefix path.")
set(PROJECT_RESOURCES_PREFIX "${PROJECT_SHARE_PREFIX}/resources" CACHE STRING "Resources prefix path.")
option(WALLETCPP_GNUPLOT_SUPPORT "Turn on/off building with Gnuplot support." OFF)
message(STATUS "Gnuplot support - ${WALLETCPP_GNUPLOT_SUPPORT}")

# Flags
message(STATUS "Set flags")
set(CMAKE_CXX_FLAGS "-Wall -Wshadow -Wfatal-errors")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wunused-variable -DNDEBUG")
set(CMAKE_CXX_FLAGS_TEST "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBIAN "-O3 -Wunused-variable")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Set minimum C++ to 2017 standards.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "release")
endif ()

# Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
message(STATUS "CMake Module path: ${CMAKE_MODULE_PATH}")

# Mustache
message(STATUS "Include FindMustache")
include(FindMustache)
#include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/FindMustache.cmake")

# yaml-cpp
message(STATUS "Check yaml-cpp")
find_package(yaml-cpp REQUIRED)
if (yaml-cpp_FOUND)
    message(STATUS "yaml-cpp config: '${yaml-cpp_CONFIG}'")
    message(STATUS "yaml-cpp INCL: '${YAML_CPP_INCLUDE_DIR}'")
    message(STATUS "yaml-cpp LIBS: '${YAML_CPP_LIBRARIES}'")

    if ("${yaml-cpp_CONFIG}" STREQUAL "")
        message(FATAL_ERROR "yaml-cpp CONFIG not found")
    endif()
    if ("${YAML_CPP_INCLUDE_DIR}" STREQUAL "")
        message(FATAL_ERROR "yaml-cpp INCL not found")
    endif()
    if ("${YAML_CPP_LIBRARIES}" STREQUAL "")
        message(FATAL_ERROR "yaml-cpp LIBS not found")
    endif()
else ()
    message(FATAL_ERROR "yaml-cpp not found")
endif ()

# Term Color
message(STATUS "Check termcolor")
find_package(termcolor QUIET)
if (termcolor_FOUND)
    message(STATUS "termcolor config: '${termcolor_CONFIG}'")
else ()
    message(FATAL_ERROR "termcolor not found")
endif ()

# Catch2
message(STATUS "Check catch2")
find_package(catch2 QUIET)
if (catch2_FOUND)
    message(STATUS "catch2 config: '${catch2_CONFIG}'")
else ()
    message(FATAL_ERROR "catch2 not found")
endif ()

# Boost
message(STATUS "Check Boost")
# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_STATIC_RUNTIME ON)
# set(Boost_USE_MULTITHREADED OFF)
find_package(Boost 1.75.0 REQUIRED COMPONENTS filesystem program_options date_time)
if (Boost_FOUND)
    message(STATUS "Found Boost")
    message(STATUS "Boost INCL '${Boost_INCLUDE_DIRS}'")
    message(STATUS "Boost LIBS '${Boost_LIBRARIES}'")

    if ("${Boost_INCLUDE_DIRS}" STREQUAL "")
        message(FATAL_ERROR "Boost INCL not found")
    endif()
    if ("${Boost_LIBRARIES}" STREQUAL "")
        message(FATAL_ERROR "Boost LIBS not found")
    endif()
else ()
    message(FATAL_ERROR "Boost not found")
endif ()

# Git/Version
include(GetGitVersion)
get_git_version(GIT_VERSION)
get_git_hash(GIT_HASH)
if (${PROJECT_VERSION_FULL} STREQUAL "N/A" AND GIT_VERSION)
    set(PROJECT_VERSION_FULL "${GIT_VERSION}")
endif ()
string(CONCAT PROJECT_VERSION_FULL ${PROJECT_VERSION_FULL} ${PROJECT_VERSION_APPENDIX})
if (${PROJECT_VERSION_HASH} STREQUAL "N/A" AND GIT_HASH)
    set(PROJECT_VERSION_HASH "${GIT_HASH}")
endif ()

message(STATUS "Project Version Full: ${PROJECT_VERSION_FULL}")
message(STATUS "Project Version Hash: ${PROJECT_VERSION_HASH}")

# C++ Includes
include(CheckIncludeFileCXX)
check_include_file_cxx("algorithm" HAVE_ALGORITHM_FILE)
check_include_file_cxx("cmath" HAVE_CMATH_FILE)
check_include_file_cxx("cstddef" HAVE_CSTDDEF_FILE)
check_include_file_cxx("cstdint" HAVE_CSTDINT_FILE)
check_include_file_cxx("cstdio" HAVE_CSTDIO_FILE)
check_include_file_cxx("cstdlib" HAVE_CSTDLIB_FILE)
check_include_file_cxx("fstream" HAVE_FSTREAM_FILE)
check_include_file_cxx("functional" HAVE_FUNCTIONAL_FILE)
check_include_file_cxx("iomanip" HAVE_IOMANIP_FILE)
check_include_file_cxx("ios" HAVE_IOS_FILE)
check_include_file_cxx("iostream" HAVE_IOSTREAM_FILE)
check_include_file_cxx("istream" HAVE_ISTREAM_FILE)
check_include_file_cxx("iterator" HAVE_ITERATOR_FILE)
check_include_file_cxx("locale" HAVE_LOCALE_FILE)
check_include_file_cxx("map" HAVE_MAP_FILE)
check_include_file_cxx("sstream" HAVE_SSTREAM_FILE)
check_include_file_cxx("string" HAVE_STRING_FILE)
check_include_file_cxx("unistd.h" HAVE_unistd.H_FILE)
check_include_file_cxx("unordered_map" HAVE_UNORDERED_MAP_FILE)
check_include_file_cxx("utility" HAVE_UTILITY_FILE)
check_include_file_cxx("vector" HAVE_VECTOR_FILE)

# Other Includes
include(CheckIncludeFiles)
check_include_files("boost/date_time/gregorian/gregorian.hpp" HAVE_BOOST_DATETIME_GREGORIAN_FILE)
check_include_files("boost/date_time/local_time/local_time.hpp" HAVE_BOOST_DATETIME_LOCALTIME_FILE)
check_include_files("boost/date_time/time_facet.hpp" HAVE_BOOST_DATETIME_TIMEFACET_FILE)
check_include_files("boost/date_time/year_month_day.hpp" HAVE_BOOST_DATETIME_YMD_FILE)
check_include_files("boost/filesystem.hpp" HAVE_BOOST_FILESYSTEM_FILE)
check_include_files("boost/program_options.hpp" HAVE_BOOST_PROGRAM_OPTIONS_FILE)
check_include_files("boost/uuid/random_generator.hpp" HAVE_BOOST_UUID_RND_FILE)
check_include_files("boost/uuid/uuid.hpp" HAVE_BOOST_UUID_FILE)
check_include_files("boost/uuid/uuid_io.hpp" HAVE_BOOST_UUID_IO_FILE)
check_include_files("yaml-cpp/yaml.h" HAVE_YAML_FILE)

# Check Functions
include(CheckFunctionExists)
check_function_exists("getline" HAVE_GETLINE_FUNCTION)
check_function_exists("system" HAVE_SYSTEM_FUNCTION)

# Config File
message(STATUS "Make config file")
configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/src/config.hpp"
    NEWLINE_STYLE LF)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/src")

set(TARGET_WALLET_FILES
    src/app/wallet.cpp
    src/debug.hpp
    src/fs.hpp
    src/mstch.hpp
    src/components.cpp src/components.hpp
    src/class/mutable_wallet.cpp src/class/mutable_wallet.hpp
    src/class/command/command_options.cpp src/class/command/command_options.hpp
    src/class/command/command_factory.cpp src/class/command/command_factory.hpp
    src/class/command/command.cpp src/class/command/command.hpp
    src/class/command/help_command.cpp src/class/command/help_command.hpp
    src/class/command/add_command.cpp src/class/command/add_command.hpp
    src/class/command/init_command.cpp src/class/command/init_command.hpp
    src/class/command/html_command.cpp src/class/command/html_command.hpp
    src/class/command/list_command.cpp src/class/command/list_command.hpp
    src/class/command/version_command.cpp src/class/command/version_command.hpp
    src/class/command/fake_version_command.cpp src/class/command/fake_version_command.hpp
    src/class/command/epic_command.cpp src/class/command/epic_command.hpp
    src/class/entry.cpp src/class/entry.hpp
    src/class/epic.cpp src/class/epic.hpp
    src/class/container/entry_container.cpp src/class/container/entry_container.hpp
    src/class/container/epic_container.cpp src/class/container/epic_container.hpp
    src/class/trait/accountable.cpp src/class/trait/accountable.hpp
    src/class/trait/logable.cpp src/class/trait/logable.hpp
    src/class/trait/idable.cpp src/class/trait/idable.hpp
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

#set(TARGET_WALLET_FILES src/app/fake.cpp)

set(TARGET_WALLET_COMPILE_FEATURES
    cxx_noexcept
    cxx_constexpr
    cxx_final
    cxx_deleted_functions
    cxx_override)

string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
if (CMAKE_BUILD_TYPE_LOWER STREQUAL "release"
    OR CMAKE_BUILD_TYPE_LOWER STREQUAL "debug"
    OR CMAKE_BUILD_TYPE_LOWER STREQUAL "debian")

    # Wallet Target
    set(TARGET_WALLET_NAME "wallet")
    message(STATUS "Setup ${TARGET_WALLET_NAME} target")
    add_executable(${TARGET_WALLET_NAME} ${TARGET_WALLET_FILES})
    add_dependencies(${TARGET_WALLET_NAME} mstch_project)
    target_include_directories(${TARGET_WALLET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_include_directories(${TARGET_WALLET_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(${TARGET_WALLET_NAME} ${Boost_LIBRARIES} ${YAML_CPP_LIBRARIES})
    target_link_libraries(${TARGET_WALLET_NAME} mstch)
    target_compile_features(${TARGET_WALLET_NAME} PRIVATE ${TARGET_WALLET_COMPILE_FEATURES})
    target_compile_definitions(${TARGET_WALLET_NAME} PRIVATE "-DNDEBUG")

    # Install Wallet
    install(TARGETS wallet RUNTIME DESTINATION bin)

    if (CMAKE_BUILD_TYPE_LOWER STREQUAL "debian")
        # Wallet Debug Target
        set(TARGET_WALLET_DEBUG_NAME "wallet-debug")
        message(STATUS "Setup ${TARGET_WALLET_DEBUG_NAME} target")
        add_executable(${TARGET_WALLET_DEBUG_NAME} ${TARGET_WALLET_FILES})
        add_dependencies(${TARGET_WALLET_DEBUG_NAME} mstch_project)
        target_include_directories(${TARGET_WALLET_DEBUG_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
        target_include_directories(${TARGET_WALLET_DEBUG_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
        target_link_libraries(${TARGET_WALLET_DEBUG_NAME} ${Boost_LIBRARIES} ${YAML_CPP_LIBRARIES})
        target_link_libraries(${TARGET_WALLET_DEBUG_NAME} mstch)
        target_compile_features(${TARGET_WALLET_DEBUG_NAME} PRIVATE ${TARGET_WALLET_COMPILE_FEATURES})
        target_compile_definitions(${TARGET_WALLET_DEBUG_NAME} PRIVATE "-DDEBUG")

        # Install Debug Wallet
        install(TARGETS ${TARGET_WALLET_DEBUG_NAME} RUNTIME DESTINATION bin)
    endif ()

    # Install Resources
    install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/resources
        DESTINATION ${PROJECT_SHARE_PATH})
elseif (CMAKE_BUILD_TYPE_LOWER STREQUAL "test")
    # Test Target
    message(STATUS "Setup test target")
    add_executable(test
        src/app/test.cpp
        src/test/entry_test.hpp
        src/components.cpp src/components.hpp
        src/class/entry.cpp src/class/entry.hpp
        src/class/trait/accountable.cpp src/class/trait/accountable.hpp
        src/class/trait/idable.cpp src/class/trait/idable.hpp
    )
    target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_include_directories(test PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(test Catch2::Catch2)
    target_link_libraries(test ${Boost_LIBRARIES} ${YAML_CPP_LIBRARIES})
    target_compile_features(test PRIVATE ${TARGET_WALLET_COMPILE_FEATURES})
else ()
    message(FATAL_ERROR "No build type selected: release, debian, debug, test")
endif ()

message(STATUS "-------- DEBUG --------")
message(STATUS "CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_BUILD_TYPE_LOWER ${CMAKE_BUILD_TYPE_LOWER}")
message(STATUS "CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
#message(STATUS "CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}")
#message(STATUS "CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_SYSTEM_PREFIX_PATH ${CMAKE_SYSTEM_PREFIX_PATH}")
# message(STATUS "CMAKE_INCLUDE_PATH '${CMAKE_INCLUDE_PATH}'")
#message(STATUS "CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH}")
#message(STATUS "CMAKE_INSTALL_LOCALSTATEDIR ${CMAKE_INSTALL_LOCALSTATEDIR}")
#message(STATUS "CMAKE_INSTALL_SYSCONFDIR ${CMAKE_INSTALL_SYSCONFDIR}")
#message(STATUS "CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME}")
#message(STATUS "CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES}")

message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_SHARE_PATH ${PROJECT_SHARE_PATH}")
message(STATUS "PROJECT_SHARE_PREFIX ${PROJECT_SHARE_PREFIX}")
message(STATUS "PROJECT_RESOURCES_PREFIX ${PROJECT_RESOURCES_PREFIX}")

message(STATUS "YAML_CPP_INCLUDE_DIR ${YAML_CPP_INCLUDE_DIR}")
message(STATUS "YAML_CPP_LIBRARIES ${YAML_CPP_LIBRARIES}")

message(STATUS "Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS}")

message(STATUS "-------- ----- --------")
