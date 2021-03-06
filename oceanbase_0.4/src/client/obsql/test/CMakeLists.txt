cmake_minimum_required(VERSION 2.8.9)
project(obmysqltest)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.tests)


if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_CXX_FLAGS "-Wno-deprecated -Wno-unused-result -Wno-unused-but-set-variable -Wno-memset-transposed-args -Wno-maybe-uninitialized -Wno-unused-local-typedefs -Wno-strict-aliasing -Wno-psabi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
    set(GCC_LINK_FLAGS "-pthread -lc -lm  -lrt -lcrypt -lssl -lcrypto -laio -lcurl")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/../src
    ${PROJECT_SOURCE_DIR}/../../..
    $ENV{TBLIB_ROOT}/include/tbsys $ENV{TBLIB_ROOT}/include/tbnet
)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.cpp" ${PROJECT_SOURCE_DIR}/../../svn_version.cpp)

set(LINK_LIBRARIES 
    ${CMAKE_BINARY_DIR}/.libs/libobsql.a
    ${CMAKE_BINARY_DIR}/.libs/libcommon.a
    $ENV{TBLIB_ROOT}/lib/libtbsys.a
    $ENV{EASY_LIB_PATH}/libeasy.a
    pthread mysqlclient curl aio
)

add_executable(sqltest ob_sql_test.cpp)
target_link_libraries( sqltest ${LINK_LIBRARIES}  )

add_executable(msqltest ob_sql_test_multh.cpp)
target_link_libraries( msqltest ${LINK_LIBRARIES}  )

add_executable(whiletest ob_sql_while_test.cpp)
target_link_libraries( whiletest ${LINK_LIBRARIES}  )
