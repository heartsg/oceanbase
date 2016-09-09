cmake_minimum_required(VERSION 2.8.9)
project(compress)

set(TMP_DIR ${CMAKE_BINARY_DIR}/.libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TMP_DIR})

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_CXX_FLAGS "-O3 -Wall -fPIC -Wno-deprecated -Wno-unused-result -Wno-unused-but-set-variable -Wno-memset-transposed-args -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-strict-aliasing -Wno-psabi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
    set(GCC_LINK_FLAGS "-lc -lm  -lrt -ldl")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR})

add_library(comp STATIC ob_compressor.cpp)

add_library(lzo_static STATIC ob_compressor.cpp lzo_compressor.cpp)
set_target_properties(lzo_static
    PROPERTIES LINK_FLAGS -llzo2
    OUTPUT_NAME lzo)
add_library(lzo SHARED ob_compressor.cpp lzo_compressor.cpp)
set_target_properties(lzo
    PROPERTIES LINK_FLAGS -llzo2)
add_custom_command(
    TARGET lzo POST_BUILD
    COMMAND ln -sf liblzo.so ${TMP_DIR}/liblzo.so.0
    COMMAND ln -sf liblzo.so ${TMP_DIR}/liblzo.so.0.0
    COMMAND ln -sf liblzo.so ${TMP_DIR}/liblzo.so.0.0.0
)

add_library(snappy_static STATIC ob_compressor.cpp snappy_compressor.cpp)
set_target_properties(snappy_static
    PROPERTIES LINK_FLAGS -lsnappy
    OUTPUT_NAME snappy)
add_library(snappy SHARED ob_compressor.cpp snappy_compressor.cpp)
set_target_properties(snappy
    PROPERTIES LINK_FLAGS -lsnappy)
add_custom_command(
    TARGET snappy POST_BUILD
    COMMAND ln -sf libsnappy.so ${TMP_DIR}/libsnappy.so.0
    COMMAND ln -sf libsnappy.so ${TMP_DIR}/libsnappy.so.0.0
    COMMAND ln -sf libsnappy.so ${TMP_DIR}/libsnappy.so.0.0.0
)

add_library(none_static STATIC ob_compressor.cpp none_compressor.cpp)
set_target_properties(none_static
    PROPERTIES OUTPUT_NAME none)
add_library(none SHARED ob_compressor.cpp none_compressor.cpp)
add_custom_command(
    TARGET none POST_BUILD
    COMMAND ln -sf libnone.so ${TMP_DIR}/libnone.so.0
    COMMAND ln -sf libnone.so ${TMP_DIR}/libnone.so.0.0
    COMMAND ln -sf libnone.so ${TMP_DIR}/libnone.so.0.0.0
)