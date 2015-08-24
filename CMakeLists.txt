cmake_minimum_required(VERSION 2.8)

# guard against in-source builds (got this from Eigen)
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build dir
ectory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

#add the customised package searches to the module path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(GSL REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(FFTW3 REQUIRED)
find_package(Einspline REQUIRED)

include_directories(${GSL_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${FFTW_INCLUDES})
include_directories(${EINSPLINE_INCLUDES})

if(CMAKE_COMPILER_IS_GNUCXX )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pedantic -Wall -Wextra -Wfatal-errors")
endif()


add_executable(gslSpline gslSpline.cpp)
target_link_libraries(gslSpline ${GSL_LIBRARIES})

add_executable(eigenSpline eigenSpline.cpp)

add_executable(einsplineSpline einsplineSpline.cpp)
target_link_libraries(einsplineSpline ${EINSPLINE_LIBRARIES} ${FFTW_LIBRARIES})
