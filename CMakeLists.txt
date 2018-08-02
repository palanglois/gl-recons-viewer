cmake_minimum_required(VERSION 3.1)
project(opengl_test)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
message("FLAGS : ${CMAKE_CXX_FLAGS}")

# OpenGL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

# Eigen
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)

# Option Parser
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/OptionParser)

# Tinyply
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/tinyply)
add_library(tinyplyLib STATIC external/tinyply/tinyply.cpp )

# Arcball
include_directories(lib/arcball)
add_library(arcball STATIC lib/arcball/Arcball.cpp)

add_executable(gl-recons-viewer main.cpp )
target_link_libraries(gl-recons-viewer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} tinyplyLib arcball)