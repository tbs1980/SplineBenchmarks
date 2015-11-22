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
#find_package(FFTW3 REQUIRED)
#find_package(Einspline REQUIRED)
find_package(Splinter REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra -Wfatal-errors")
endif()

if(GSL_FOUND)
    include_directories(${GSL_INCLUDE_DIRS})
    add_executable(gslSpline gslSpline.cpp)
    target_link_libraries(gslSpline ${GSL_LIBRARIES})
endif(GSL_FOUND)

if(EIGEN3_FOUND)
    include_directories(${EIGEN3_INCLUDE_DIR})
    add_executable(eigenSpline eigenSpline.cpp)
endif(EIGEN3_FOUND)

#if(Einspline_FOUND and FFTW_FOUND)
#include_directories(${FFTW_INCLUDES})
#include_directories(${EINSPLINE_INCLUDES})
#    add_executable(einsplineSpline einsplineSpline.cpp)
#    target_link_libraries(einsplineSpline ${EINSPLINE_LIBRARIES} ${FFTW_LIBRARIES})
#endif(Einspline_FOUND and FFTW3_FOUND)

if(Splinter_FOUND)
    include_directories(${EIGEN3_INCLUDE_DIR})
    include_directories(${Splinter_INCLUDE_DIR})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    add_executable(splinterSpline splinterSpline.cpp)
    target_link_libraries(splinterSpline ${Splinter_LIBRARIES})
endif(Splinter_FOUND)
