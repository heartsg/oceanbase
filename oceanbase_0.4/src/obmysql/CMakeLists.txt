cmake_minimum_required(VERSION 2.8.9)
project(obmysql)

set(TMP_DIR ${CMAKE_BINARY_DIR}/.libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TMP_DIR})

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_CXX_FLAGS "-O3 -Wall -fPIC -Wno-deprecated -Wno-unused-result -Wno-unused-but-set-variable -Wno-memset-transposed-args -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-strict-aliasing -Wno-psabi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
    set(GCC_LINK_FLAGS "-pthread -lc -lm  -lrt -lcrypt -lssl")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/.. $ENV{TBLIB_ROOT}/include/tbsys $ENV{EASY_ROOT}/include/easy)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.cpp" "${PROJECT_SOURCE_DIR}/packet/*.cpp" "${PROJECT_SOURCE_DIR}/packet/*.h" ${PROJECT_SOURCE_DIR}/ob_mysql_state.map)

add_library(obmysql STATIC ${SOURCES})
target_link_libraries( obmysql $ENV{EASY_LIB_PATH}/libeasy.a  )
target_link_libraries( obmysql $ENV{TBLIB_ROOT}/lib/libtbsys.a  )
