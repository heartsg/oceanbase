cmake_minimum_required(VERSION 2.8.9)
project(rootserver)

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

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.cpp" ${PROJECT_SOURCE_DIR}/../../svn_version.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_clist2str.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_root_main.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/main.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_schema_reader.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_check_point2str.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_str2check_point.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_root_admin2.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_root_admin2_main.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/ob_rs_stress.cpp)

set(LINK_LIBRARIES 
    ${CMAKE_BINARY_DIR}/.libs/libroottable.a
    ${CMAKE_BINARY_DIR}/.libs/libcommon.a
    ${CMAKE_BINARY_DIR}/.libs/libsql.a
    ${CMAKE_BINARY_DIR}/.libs/libcommon.a
    ${CMAKE_BINARY_DIR}/.libs/libtimezone.a
    $ENV{TBLIB_ROOT}/lib/libtbsys.a
    $ENV{EASY_LIB_PATH}/libeasy.a
    ssl crypto aio
)

add_library(rootserver_static STATIC ${SOURCES})
target_link_libraries( rootserver_static ${LINK_LIBRARIES}  )
set_target_properties( rootserver_static PROPERTIES OUTPUT_NAME rootserver )

add_executable(rootserver ${SOURCES} ob_root_main.cpp main.cpp)
target_link_libraries( rootserver ${LINK_LIBRARIES}  )

add_executable(schema_reader ${SOURCES} ob_schema_reader.cpp)
target_link_libraries( schema_reader ${LINK_LIBRARIES}  )

add_executable(checkpoint2str ${SOURCES} ob_check_point2str.cpp)
target_link_libraries( checkpoint2str ${LINK_LIBRARIES}  )

add_executable(str2checkpoint ${SOURCES} ob_str2check_point.cpp)
target_link_libraries( str2checkpoint ${LINK_LIBRARIES}  )

add_executable(rs_admin ${SOURCES} ob_root_admin2.cpp ob_root_admin2_main.cpp)
target_link_libraries( rs_admin ${LINK_LIBRARIES}  )

add_executable(rs_stress ${SOURCES} ob_rs_stress.cpp)
target_link_libraries( rs_stress ${LINK_LIBRARIES}  )