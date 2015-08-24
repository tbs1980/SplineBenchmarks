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

include_directories(${GSL_INCLUDE_DIRS})

add_executable(gslSpline gslSpline.cpp)
target_link_libraries(gslSpline ${GSL_LIBRARIES})
