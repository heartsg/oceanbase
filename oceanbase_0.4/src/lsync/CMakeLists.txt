cmake_minimum_required(VERSION 2.8.9)
project(lsyncserver)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.libs)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_CXX_FLAGS "-DPACKAGE_VERSION=\\\"0.4\\\" -DPACKAGE_STRING=\\\"oceanbase\\\" -DRELEASEID=\\\"release\\\" -O3 -Wall -fPIC -Wno-deprecated -Wno-unused-result -Wno-unused-but-set-variable -Wno-memset-transposed-args -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-strict-aliasing -Wno-psabi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
    set(GCC_LINK_FLAGS "-pthread -lc -lm  -lrt -lcrypt -lssl -lcrypto -laio")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/.. $ENV{TBLIB_ROOT}/include/tbsys $ENV{EASY_ROOT}/include/easy)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_lsync_server_main.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/main.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_seekable_log_reader.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_seekable_log_reader.h)


set(LINK_LIBRARIES 
    ${CMAKE_BINARY_DIR}/.libs/libupdateserver.a
    ${CMAKE_BINARY_DIR}/.libs/librootserver.a
    ${CMAKE_BINARY_DIR}/.libs/libmergeserver.a
    ${CMAKE_BINARY_DIR}/.libs/libsstable.a
    ${CMAKE_BINARY_DIR}/.libs/libcommon.a
    ${CMAKE_BINARY_DIR}/.libs/libcomp.a
    ${CMAKE_BINARY_DIR}/.libs/libsql.a
    ${CMAKE_BINARY_DIR}/.libs/libcommon.a
    ${CMAKE_BINARY_DIR}/.libs/libbtree.a
    $ENV{TBLIB_ROOT}/lib/libtbsys.a
    $ENV{EASY_LIB_PATH}/libeasy.a
    ssl crypto aio dl crypt
)

add_library(lsyncserver_static STATIC ${SOURCES})
target_link_libraries( lsyncserver_static ${LINK_LIBRARIES}  )
set_target_properties( lsyncserver_static PROPERTIES OUTPUT_NAME lsyncserver )

add_executable(lsyncserver ${SOURCES} ob_lsync_server_main.cpp main.cpp)
target_link_libraries( lsyncserver ${LINK_LIBRARIES}  )
