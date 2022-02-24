cmake_minimum_required (VERSION 2.8.12)
project (CMakeHelloWorld)

#set(CMAKE_SYSROOT "/opt/rtems/6/lib/pkgconfig")
#Set the pkg config path to where rtems packages are
SET(ENV{RTEMS_PATH} /opt/rtems/6)
SET(ENV{RTEMS_BSP_NAME} kcu105)

SET(ENV{PKG_CONFIG_PATH} $ENV{RTEMS_PATH}/lib/pkgconfig)
SET(TARGETPREFIX $ENV{RTEMS_PATH}/bin/microblaze-rtems6-)

find_package(PkgConfig REQUIRED)
pkg_search_module(PKG_RTEMS REQUIRED IMPORTED_TARGET microblaze-rtems6-kcu105)

SET(CMAKE_C_COMPILER            ${TARGETPREFIX}gcc)
SET(CMAKE_CXX_COMPILER          ${TARGETPREFIX}g++)
SET(CMAKE_LINKER                ${TARGETPREFIX}ld)
SET(CMAKE_ASM_COMPILER          ${TARGETPREFIX}as)
SET(CMAKE_STRIP                 ${TARGETPREFIX}strip)
SET(CMAKE_NM                    ${TARGETPREFIX}nm)
SET(CMAKE_AR                    ${TARGETPREFIX}ar)
SET(CMAKE_OBJDUMP               ${TARGETPREFIX}objdump)
SET(CMAKE_OBJCOPY               ${TARGETPREFIX}objcopy)
string( REPLACE  ";" " " PKG_RTEMS_LDFLAGS "${PKG_RTEMS_LDFLAGS}")
string( REPLACE  ";" " " PKG_RTEMS_CFLAGS "${PKG_RTEMS_CFLAGS}")
string( REPLACE  ";" " " PKG_RTEMS_STATIC_LDFLAGS "${PKG_RTEMS_STATIC_LDFLAGS}")

set(CMAKE_C_FLAGS   ${PKG_RTEMS_CFLAGS} )
set(CMAKE_CXX_FLAGS ${PKG_RTEMS_CFLAGS})

set(CMAKE_EXE_LINKER_FLAGS_INIT ${PKG_RTEMS_LDFLAGS})
set(CMAKE_SHARED_LINKER_FLAGS_INIT ${PKG_RTEMS_STATIC_LDFLAGS})
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS ${PKG_RTEMS_STATIC_LDFLAGS})
#set( CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" )

set( CMAKE_C_FLAGS_INIT PKG_RTEMS_CFLAGS)
set(LINKER_SCRIPT "$ENV{RTEMS_PATH}/microblaze-rtems6/$ENV{RTEMS_BSP_NAME}/lib/linkcmds")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM   NEVER)

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY   ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE   ONLY)

SET(CMAKE_PREFIX_PATH                   /)

#version number
set (CMakeHelloWorld_VERSION_MAJOR 1)
set (CMakeHelloWorld_VERSION_MINOR 0)


## DEBUG print out all variables 
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

#include the subdirectory containing our libs

add_executable (hello_rtems 
	init.c
	hello.c
)


# Indicate which libraries to include during the link process.
install (TARGETS hello_rtems DESTINATION bin)
