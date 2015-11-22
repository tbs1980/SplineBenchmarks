# https://github.com/bgrimstad/splinter
#
# Splinter_ROOT root search path
# Splinter_INCLUDE_DIR inlcude directories
# Splinter_LIBRARIES libraries
#


find_path(Splinter_INCLUDE_DIR NAMES datatable.h PATHS ${Splinter_ROOT}/include/SPLINTER)

find_library(Splinter_LIBRARIES NAMES splinter-2-0 PATHS ${Splinter_ROOT}/lib ${Splinter_ROOT}/lib64)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Splinter DEFAULT_MSG
                                  Splinter_INCLUDE_DIR Splinter_LIBRARIES)
mark_as_advanced(Splinter_INCLUDE_DIR Splinter_LIBRARIES)
