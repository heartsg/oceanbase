cmake_minimum_required(VERSION 2.8.9)
project(sql)

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

include_directories(${PROJECT_SOURCE_DIR} $ENV{TBLIB_ROOT}/include/tbsys)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")
add_library(tbnet_static STATIC ${SOURCES})
add_library(tbnet SHARED ${SOURCES})
target_link_libraries( tbnet_static $ENV{TBLIB_ROOT}/lib/libtbsys.so )
target_link_libraries( tbnet $ENV{TBLIB_ROOT}/lib/libtbsys.so )

add_custom_command(
    TARGET tbnet_static POST_BUILD
    COMMAND mv ${TMP_DIR}/libtbnet_static.a ${TMP_DIR}/libtbnet.a
)
add_custom_command(
    TARGET tbnet POST_BUILD
    COMMAND ln -sf libtbnet.so ${TMP_DIR}/libtbnet.so.0
    COMMAND ln -sf libtbnet.so ${TMP_DIR}/libtbnet.so.0.0
    COMMAND ln -sf libtbnet.so ${TMP_DIR}/libtbnet.so.0.0.0
)

set(CMAKE_INSTALL_PREFIX $ENV{TBLIB_ROOT})
file(GLOB INCLUDES "${PROJECT_SOURCE_DIR}/*.h")
install(FILES ${INCLUDES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/tbnet)
file(GLOB STATIC_LIBS ${TMP_DIR}/libtbnet.a)
install(FILES ${STATIC_LIBS} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
file(GLOB SHARED_LIBS ${TMP_DIR}/libtbnet.so ${TMP_DIR}/libtbnet.so.0 ${TMP_DIR}/libtbnet.so.0.0 ${TMP_DIR}/libtbnet.so.0.0.0)
install(FILES ${SHARED_LIBS} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)

