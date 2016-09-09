cmake_minimum_required(VERSION 2.8.9)
project(compactsstablev2)

set(TMP_DIR ${CMAKE_BINARY_DIR}/.libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TMP_DIR})

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_CXX_FLAGS "-D_SSTABLE_NO_STAT_ -O3 -Wall -fPIC -Wno-deprecated -Wno-unused-result -Wno-unused-but-set-variable -Wno-memset-transposed-args -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-strict-aliasing -Wno-psabi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
    set(GCC_LINK_FLAGS "-pthread -lc -lm  -lrt -lcrypt -lssl -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/.. $ENV{TBLIB_ROOT}/include/tbsys $ENV{EASY_ROOT}/include/easy)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_sstable_compact_row.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_sstable_compact_row.h)

add_library(compactsstablev2 STATIC ${SOURCES})
target_link_libraries( compactsstablev2 $ENV{EASY_LIB_PATH}/libeasy.a  )
target_link_libraries( compactsstablev2 $ENV{TBLIB_ROOT}/lib/libtbsys.a  )
