cmake_minimum_required(VERSION 2.8.9)
project(updateserver)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.libs)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_CXX_FLAGS "-D_BTREE_ENGINE_ -D__VERSION_ID__=\\\"updateserver_1.0.0.0\\\" -DPACKAGE_VERSION=\\\"0.4\\\" -DPACKAGE_STRING=\\\"oceanbase\\\" -DRELEASEID=\\\"release\\\" -O3 -Wall -fPIC -Wno-deprecated -Wno-unused-result -Wno-unused-but-set-variable -Wno-memset-transposed-args -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-strict-aliasing -Wno-psabi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
    set(GCC_LINK_FLAGS "-pthread -lc -lm  -lrt -ldl -lcrypt -lssl -lcrypto -laio")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/.. $ENV{TBLIB_ROOT}/include/tbsys $ENV{EASY_ROOT}/include/easy)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.cpp" ${PROJECT_SOURCE_DIR}/../../svn_version.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ups_mon.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/main.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_client_wrapper.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_client_wrapper.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_client_wrapper_tsi.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_btree_engine.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_btree_engine.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_lease_task.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_lease_task.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_commit_log_receiver.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_commit_log_receiver.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_rpc_proxy.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_rpc_proxy.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_schema_mgr.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_schema_mgr.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_check_runnable.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_check_runnable.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_fetch_lsync.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_fetch_lsync.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_hash_engine.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_hash_engine.h)

set(LINK_LIBRARIES 
    ${CMAKE_BINARY_DIR}/.libs/libsql.a
    ${CMAKE_BINARY_DIR}/.libs/libsstable.a
    ${CMAKE_BINARY_DIR}/.libs/libcomp.a
    ${CMAKE_BINARY_DIR}/.libs/libcommon.a
    ${CMAKE_BINARY_DIR}/.libs/libsql.a
    ${CMAKE_BINARY_DIR}/.libs/libcommon.a
    ${CMAKE_BINARY_DIR}/.libs/libbtree.a
    ${CMAKE_BINARY_DIR}/.libs/libtimezone.a
    $ENV{TBLIB_ROOT}/lib/libtbsys.a
    $ENV{EASY_LIB_PATH}/libeasy.a
    ssl crypto aio dl crypt
)

add_library(updateserver_static STATIC ${SOURCES})
target_link_libraries( updateserver_static ${LINK_LIBRARIES}  )
set_target_properties( updateserver_static PROPERTIES OUTPUT_NAME updateserver )

add_executable(updateserver ${SOURCES} main.cpp)
target_link_libraries( updateserver ${LINK_LIBRARIES}  )

add_executable(ob_ping ups_mon.cpp)
target_link_libraries( ob_ping ${LINK_LIBRARIES}  )
