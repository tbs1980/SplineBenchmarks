# - Find the Einspline library
#
# Usage:
#   find_package(Einspline [REQUIRED] [QUIET] )
#
# It sets the following variables:
#   EINSPLINE_FOUND               ... true if Einspline is found on the system
#   EINSPLINE_LIBRARIES           ... full path to Einspline library
#   EINSPLINE_INCLUDES            ... Einspline include directory
#
# The following variables will be checked by the function
#   EINSPLINE_USE_STATIC_LIBS    ... if true, only static libraries are found
#   EINSPLINE_ROOT               ... if set, the libraries are exclusively searched
#                               under this path
#   EINSPLINE_LIBRARY            ... Einspline library to use
#   EINSPLINE_INCLUDE_DIR        ... Einspline include directory
#

#If environment variable EINSPLINEWDIR is specified, it has same effect as EINSPLINE_ROOT
if( NOT EINSPLINE_ROOT AND ENV{EINSPLINEDIR} )
  set( EINSPLINE_ROOT $ENV{EINSPLINEDIR} )
endif()

# Check if we can use PkgConfig
find_package(PkgConfig)

#Determine from PKG
if( PKG_CONFIG_FOUND AND NOT EINSPLINE_ROOT )
  pkg_check_modules( PKG_EINSPLINE QUIET "einspline" )
endif()

#Check whether to search static or dynamic libs
set( CMAKE_FIND_LIBRARY_SUFFIXES_SAV ${CMAKE_FIND_LIBRARY_SUFFIXES} )

if( ${EINSPLINE_USE_STATIC_LIBS} )
  set( CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_STATIC_LIBRARY_SUFFIX} )
else()
  set( CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_SHARED_LIBRARY_SUFFIX} )
endif()

if( EINSPLINE_ROOT )
    #find libs
    find_library( EINSPLINE_LIB NAMES "einspline" PATHS ${EINSPLINE_ROOT} PATH_SUFFIXES "lib" "lib64" NO_DEFAULT_PATH )
    #find includes , only check one header for now
    find_path( EINSPLINE_INCLUDES NAMES "bspline_base.h" PATHS ${EINSPLINE_ROOT} PATH_SUFFIXES "include/einspline" NO_DEFAULT_PATH )
else (EINSPLINE_ROOT)
    find_library( EINSPLINE_LIB NAMES "einspline" PATHS ${PKG_EINSPLINE_LIBRARY_DIRS} ${LIB_INSTALL_DIR} )
    find_path( EINSPLINE_INCLUDES NAMES "bspline_base.h" PATHS ${PKG_EINSPLINE_INCLUDE_DIRS} ${INCLUDE_INSTALL_DIR} )
endif(EINSPLINE_ROOT)

set(EINSPLINE_LIBRARIES ${EINSPLINE_LIB})

set( CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES_SAV} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EINSPLINE DEFAULT_MSG EINSPLINE_INCLUDES EINSPLINE_LIBRARIES)

mark_as_advanced(EINSPLINE_INCLUDES EINSPLINE_LIBRARIES)
