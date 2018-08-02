cmake_minimum_required(VERSION 3.1)
project(opengl_test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
message("FLAGS : ${CMAKE_CXX_FLAGS}")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
include_directories(tinyply)
include_directories(OptionParser)
include_directories(arcball)

set(CMAKE_CXX_STANDARD 11)

add_library(tinyplyLib STATIC tinyply/tinyply.cpp )
add_library(arcball STATIC arcball/Arcball.cpp)

add_executable(gl-recons-viewer main.cpp )
target_link_libraries(gl-recons-viewer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} tinyplyLib arcball)