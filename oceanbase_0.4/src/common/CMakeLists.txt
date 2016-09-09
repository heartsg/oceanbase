cmake_minimum_required(VERSION 2.8.9)
project(common)

set(TMP_DIR ${CMAKE_BINARY_DIR}/.libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TMP_DIR})

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_CXX_FLAGS "-DPACKAGE_VERSION=0.42 -O3 -Wall -fPIC -Wno-deprecated -Wno-unused-result -Wno-unused-but-set-variable -Wno-memset-transposed-args -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-strict-aliasing -Wno-psabi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
    set(GCC_LINK_FLAGS "-pthread -lc -lm  -lrt -lcrypt -lssl")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/.. ${PROJECT_SOURCE_DIR}/location $ENV{TBLIB_ROOT}/include/tbsys $ENV{EASY_ROOT}/include/easy)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.cpp" 
    "${PROJECT_SOURCE_DIR}/location/*.cpp" "${PROJECT_SOURCE_DIR}/location/*.h" 
    "${PROJECT_SOURCE_DIR}/hash/*.cpp" "${PROJECT_SOURCE_DIR}/hash/*.h" 
    "${PROJECT_SOURCE_DIR}/cmbtree/*.h" 
    "${PROJECT_SOURCE_DIR}/nb_accessor/*.cpp" "${PROJECT_SOURCE_DIR}/nb_accessor/*.h" 
    ${PROJECT_SOURCE_DIR}/location/ob_pool.ipp ${PROJECT_SOURCE_DIR}/../../svn_version.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_rpc_client.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_rpc_client.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_info_mgr.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_info_mgr.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_info_mgr_rpc_stub.h)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_ups_info_mgr_rpc_stub.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_pool.cpp)
add_library(common STATIC ${SOURCES})
target_link_libraries( common $ENV{EASY_LIB_PATH}/libeasy.a  )
target_link_libraries( common $ENV{TBLIB_ROOT}/lib/libtbsys.a  )


add_subdirectory(btree)
add_subdirectory(compress)
add_subdirectory(roottable)
add_subdirectory(timezone)
