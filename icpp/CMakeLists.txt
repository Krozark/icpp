cmake_minimum_required (VERSION 2.8)

# define a macro that helps defining an option
macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# project name
project (icpp)

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)


# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)

# add an option for choosing the build type (shared or static)
#set_option(BUILD_SHARED_LIBS FALSE BOOL "TRUE to build as shared libraries, FALSE to build it as static libraries")

#add an option for building the examples
set_option(BUILD_EXAMPLES TRUE BOOL "TRUE to build the examples, FALSE to ignore them")

# add an option for building the API documentation
set_option(BUILD_DOC TRUE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

# add an option for building the API documentation

if(${WIN32})
    find_library(LIB_PTHREAD "winpthread-1")
    find_library(LIB_KERNEL kernel32)#dlopen
    set(LIBS ${LIB_PTHREAD} ${LIB_KERNEL})
else()
    find_library(LIB_PTHREAD pthread)
    find_library(LIB_DL dl)#dlopen
    set(LIBS ${LIB_PTHREAD} ${LIB_DL})
endif()

find_library(LIB_AVCALL avcall)
find_library(LIB_READLINE readline)
find_library(LIB_UTILS utils)
set(LIBS ${LIBS} ${LIB_AVCALL} ${LIB_READLINE} ${LIB_UTILS})

#set(includepath "-I${CMAKE_CURRENT_SOURCE_DIR}/include")
set(DEFINES "")
set(WARNING "-Wall")
set(FLAGS "-g -std=c++0x")
set(CMAKE_CXX_FLAGS "${DEFINES} ${WARNING} ${FLAGS}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples)

# add the subdirectories
add_subdirectory(src/${CMAKE_PROJECT_NAME})

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
#build doc
if(BUILD_DOC)
    add_subdirectory(doc)
endif()

