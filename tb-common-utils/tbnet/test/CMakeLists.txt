cmake_minimum_required(VERSION 2.8.9)
project(tbnettest)

set(TMP_DIR ${CMAKE_BINARY_DIR}/.tbnettest)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TMP_DIR})

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_LINK_FLAGS "-pthread -lm -lrt")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR}/../src ${PROJECT_SOURCE_DIR} $ENV{TBLIB_ROOT}/include/tbsys)
file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp) 

foreach( test_source ${TEST_SOURCES} )
    get_filename_component( test_binary_name ${test_source} NAME_WE )
    add_executable( ${test_binary_name} ${test_source} )
    target_link_libraries( ${test_binary_name} ${CMAKE_BINARY_DIR}/.libs/libtbnet.so $ENV{TBLIB_ROOT}/lib/libtbsys.so)
endforeach( test_source ${TEST_SOURCES} )