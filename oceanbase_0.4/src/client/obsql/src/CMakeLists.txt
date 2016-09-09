cmake_minimum_required(VERSION 2.8.9)
project(obsql)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.libs)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_CXX_FLAGS "-I/usr/include -O3 -Wall -g -fPIC -Wno-deprecated -Wno-unused-result -Wno-unused-but-set-variable -Wno-memset-transposed-args -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-strict-aliasing -Wno-psabi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
    set(GCC_LINK_FLAGS "-L${CMAKE_BINARY_DIR}/.libs -lcommon
                      -Wl,-static,-ltbnet
                      -Wl,-static,-ltbsys
                      -Wl,-e,so_main
                      -pthread -lc -lm  -lrt -lcrypt -lssl -lcrypto -laio -lcurl")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/../../..
    $ENV{TBLIB_ROOT}/include/tbsys $ENV{TBLIB_ROOT}/include/tbnet
)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.cpp" ${PROJECT_SOURCE_DIR}/../../svn_version.cpp)

set(LINK_LIBRARIES 
    ${CMAKE_BINARY_DIR}/.libs/libcommon.a
    ${CMAKE_BINARY_DIR}/.libs/librootserver.a
    ssl crypto aio
)

add_library(obsql_static STATIC ${SOURCES})
target_link_libraries( obsql_static ${LINK_LIBRARIES}  )
set_target_properties( obsql_static PROPERTIES OUTPUT_NAME obsql )


add_library(obsql SHARED ${SOURCES})
target_link_libraries( obsql ${LINK_LIBRARIES}  )
add_custom_command(
    TARGET obsql POST_BUILD
    COMMAND ln -sf libobsql.so ${CMAKE_BINARY_DIR}/.libs/libobsql.so.0
    COMMAND ln -sf libobsql.so ${CMAKE_BINARY_DIR}/.libs/libobsql.so.0.0
    COMMAND ln -sf libobsql.so ${CMAKE_BINARY_DIR}/.libs/libobsql.so.0.0.0
)
