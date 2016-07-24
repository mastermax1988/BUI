cmake_minimum_required (VERSION 2.8)
project (BUI)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
        message(FATAL_ERROR "GCC version >=4.8 required.")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.3)
        message(FATAL_ERROR "Clang version >=3.3 required.")
    endif()
else()
    message(WARNING "Your compiler (${CMAKE_CXX_COMPILER_ID}) has not been tested on this project. Only Clang and GCC has been tested. Please report any problems at the project page on GitHub.")
endif()

#Only tested with versions 1.55 and 1.56
find_package(Boost 1.54.0 COMPONENTS regex system thread coroutine context filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


find_package(Threads REQUIRED)

#include_directories(.)

FILE(GLOB mysrc src/*.cc)


add_executable(bui ${mysrc} main.cc)
target_link_libraries(bui ${Boost_LIBRARIES})
target_link_libraries(bui ${CMAKE_THREAD_LIBS_INIT})

