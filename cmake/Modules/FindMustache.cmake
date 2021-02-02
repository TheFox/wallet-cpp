
if (__find_mustache)
    return()
endif ()

set(__find_mustache INCLUDED)

message(STATUS "Installing external project: mstch")

include(ExternalProject)
#include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

set(MSTCH_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/vendor/mstch")
set(MSTCH_STAMP_DIR "${MSTCH_PREFIX}/stamp")
set(MSTCH_DOWNLOAD_DIR "${MSTCH_PREFIX}/download")
set(MSTCH_SOURCE_DIR "${MSTCH_PREFIX}/src")
set(MSTCH_BINARY_DIR "${MSTCH_PREFIX}/bin")
set(MSTCH_INSTALL_DIR "${MSTCH_PREFIX}/install")

ExternalProject_Add(mstch_project
    PREFIX ${MSTCH_PREFIX}
    STAMP_DIR ${MSTCH_STAMP_DIR}
    DOWNLOAD_DIR ${MSTCH_DOWNLOAD_DIR}
    SOURCE_DIR ${MSTCH_SOURCE_DIR}
    BINARY_DIR ${MSTCH_BINARY_DIR}
    INSTALL_DIR ${MSTCH_INSTALL_DIR}

    GIT_REPOSITORY "https://github.com/no1msd/mstch.git"
    GIT_TAG "1.0.2"
    UPDATE_DISCONNECTED ON
    BUILD_ALWAYS OFF
    GIT_SHALLOW ON
    GIT_SUBMODULES ""

    UPDATE_COMMAND ""
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${MSTCH_INSTALL_DIR}"
)

include_directories(${MSTCH_SOURCE_DIR}/include)
link_directories(${MSTCH_INSTALL_DIR}/lib)
add_library(libmstch INTERFACE IMPORTED GLOBAL)
