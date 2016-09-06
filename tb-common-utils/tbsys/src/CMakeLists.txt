cmake_minimum_required(VERSION 2.8.9)
project(tbsys)

set(TMP_DIR ${CMAKE_BINARY_DIR}/.libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${TMP_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TMP_DIR})

if (CMAKE_COMPILER_IS_GNUCXX)
    set(GCC_CXX_FLAGS "-O3 -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
    set(GCC_LINK_FLAGS "-pthread -lm -lrt")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
endif()

include_directories(${PROJECT_SOURCE_DIR})
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")
add_library(tbsys_static STATIC ${SOURCES})
add_library(tbsys SHARED ${SOURCES})

add_custom_command(
    TARGET tbsys_static POST_BUILD
    COMMAND mv ${TMP_DIR}/libtbsys_static.a ${TMP_DIR}/libtbsys.a
)
add_custom_command(
    TARGET tbsys POST_BUILD
    COMMAND ln -sf libtbsys.so ${TMP_DIR}/libtbsys.so.0
    COMMAND ln -sf libtbsys.so ${TMP_DIR}/libtbsys.so.0.0
    COMMAND ln -sf libtbsys.so ${TMP_DIR}/libtbsys.so.0.0.0
)

set(CMAKE_INSTALL_PREFIX $ENV{TBLIB_ROOT})
file(GLOB INCLUDES "${PROJECT_SOURCE_DIR}/*.h")
install(FILES ${INCLUDES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/tbsys)
file(GLOB STATIC_LIBS ${TMP_DIR}/libtbsys.a)
install(FILES ${STATIC_LIBS} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
file(GLOB SHARED_LIBS ${TMP_DIR}/libtbsys.so ${TMP_DIR}/libtbsys.so.0 ${TMP_DIR}/libtbsys.so.0.0 ${TMP_DIR}/libtbsys.so.0.0.0)
install(FILES ${SHARED_LIBS} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)