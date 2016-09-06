cmake_minimum_required(VERSION 2.8.9)
project(tbsystest)

set(TMP_DIR ${CMAKE_BINARY_DIR}/.tbsystest)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TMP_DIR})

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_LINK_FLAGS "-pthread -lm -lrt")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR}/../src ${PROJECT_SOURCE_DIR})
file(GLOB TEST_SOURCES 
    ${PROJECT_SOURCE_DIR}/testfilequeue.cpp 
    ${PROJECT_SOURCE_DIR}/testqueuethread.cpp
    ${PROJECT_SOURCE_DIR}/teststringutil.cpp
    ${PROJECT_SOURCE_DIR}/testnetutil.cpp
    ${PROJECT_SOURCE_DIR}/testlog.cpp
    ${PROJECT_SOURCE_DIR}/testfileutil.cpp
    ${PROJECT_SOURCE_DIR}/testtimeutil.cpp
    ${PROJECT_SOURCE_DIR}/testthread.cpp
    ${PROJECT_SOURCE_DIR}/testTimer.cpp
    ${PROJECT_SOURCE_DIR}/testThreadPool.cpp
    ${PROJECT_SOURCE_DIR}/testService.cpp
    ${PROJECT_SOURCE_DIR}/testwarningbuffer.cpp)

foreach( test_source ${TEST_SOURCES} )
    get_filename_component( test_binary_name ${test_source} NAME_WE )
    if (${test_binary_name} MATCHES "testthread" OR 
        ${test_binary_name} MATCHES "testTimer" OR
        ${test_binary_name} MATCHES "testThreadPool" OR
        ${test_binary_name} MATCHES "testService")
        add_executable( ${test_binary_name} ${test_source} "testBase.cpp" )
    else ()
        add_executable( ${test_binary_name} ${test_source} )
    endif ()
    target_link_libraries( ${test_binary_name} ${CMAKE_BINARY_DIR}/.libs/libtbsys.so )
endforeach( test_source ${TEST_SOURCES} )