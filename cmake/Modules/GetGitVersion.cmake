find_package(Git)

if (__get_git_version)
    return()
endif ()

set(__get_git_version INCLUDED)

function(get_git_hash var)
    set(ENV{TZ} "UTC")

    if (GIT_EXECUTABLE)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} --git-dir ./.git rev-parse --short HEAD
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            RESULT_VARIABLE status
            OUTPUT_VARIABLE GIT_HASH
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET)

        if (NOT ${status})
            message(STATUS "Git Hash: ${GIT_HASH}")
            set(${var} "${GIT_HASH}" PARENT_SCOPE)
        endif ()
    endif ()
endfunction()

function (get_git_version var)
    if (GIT_EXECUTABLE)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} --git-dir ./.git describe --match "v[0-9]*.[0-9]*.[0-9]*" --abbrev=8
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
            RESULT_VARIABLE status
            OUTPUT_VARIABLE GIT_VERSION
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET)

        if (NOT ${status})
            string(REGEX REPLACE "^v" "" GIT_VERSION "${GIT_VERSION}")
            string(REGEX REPLACE "-g.*$" "" GIT_VERSION "${GIT_VERSION}")

            message(STATUS "Git Version: ${GIT_VERSION}")
            set (${var} "${GIT_VERSION}" PARENT_SCOPE)
        endif ()
    endif ()
endfunction ()
