cmake_minimum_required(VERSION 2.8.9)
project(tbnetsrctest)

set(TMP_DIR ${CMAKE_BINARY_DIR}/.tbnetsrctest)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TMP_DIR})

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_LINK_FLAGS "-pthread -lm -lrt")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR}/../ ${PROJECT_SOURCE_DIR})

add_executable( dotest dotest.cpp packetqueuetf.cpp sockettf.cpp )
target_link_libraries( dotest ${CMAKE_BINARY_DIR}/.libs/libtbnet.so )
