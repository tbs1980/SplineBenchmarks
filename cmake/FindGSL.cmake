# Find gnu scientific library GSL (http://www.gnu.org/software/gsl/)
# 
# Usage:
# find_package(GSL [REQUIRED] [QUIET] )
#
# Search path variable:
# GSL_ROOT
# 
# Once run this will define: 
#
# GSL_FOUND       = system has GSL lib
# GSL_LIBRARIES   = full path to the libraries
# GSL_INCLUDE_DIRS = full path to the header files 
#

find_library(GSL_LIBRARY NAMES gsl HINTS /usr /usr/local PATHS ${GSL_ROOT} /usr /usr/local PATH_SUFFIXES lib lib64 DOC "GSL library")
find_library(GSL_CBLAS_LIBRARY NAMES gslcblas HINTS /usr /usr/local PATHS ${GSL_ROOT} /usr /usr/local PATH_SUFFIXES lib lib64 DOC "GSL cblas library")
find_path(GSL_INCLUDE_DIR NAMES gsl/gsl_version.h HINTS /usr /usr/local PATHS ${GSL_ROOT} /usr /usr/local  PATH_SUFFIXES  include DOC "GSL headers")

set(GSL_LIBRARIES ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY})
set(GSL_INCLUDE_DIRS ${GSL_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(GSL DEFAULT_MSG GSL_LIBRARIES GSL_INCLUDE_DIRS)
mark_as_advanced(GSL_LIBRARIES GSL_INCLUDE_DIRS)



