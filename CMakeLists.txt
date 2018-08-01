cmake_minimum_required(VERSION 3.1)
project(opengl_test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lpthread")
message("FLAGS : ${CMAKE_CXX_FLAGS}")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
include_directories(tinyply)
include_directories(OptionParser)

set(CMAKE_CXX_STANDARD 11)

add_library(tinyplyLib STATIC tinyply/tinyply.cpp )

add_executable(opengl_test main.cpp )
target_link_libraries(opengl_test ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} tinyplyLib)