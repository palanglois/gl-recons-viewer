cmake_minimum_required(VERSION 3.1)
project(gl-recons-viewer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
message("FLAGS : ${CMAKE_CXX_FLAGS}")

### EXTERNAL ###

# OpenGL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

# Eigen
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)

# Tinyply
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/tinyply)
add_library(tinyplyLib STATIC external/tinyply/tinyply.cpp )

# Tiny-file-dialogs
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/tinyfiledialogs)
add_library(tinyfiledialogs STATIC external/tinyfiledialogs/tinyfiledialogs.c)

### LOCAL LIBS ###

# Arcball
include_directories(lib/arcball)
add_library(arcball STATIC lib/arcball/Arcball.cpp)

# Display functions
include_directories(lib/displayFunc)
add_library(displayFunc STATIC lib/displayFunc/displayFunc.cpp)

# Data Controller
include_directories(lib/dataController)
add_library(dataController STATIC lib/dataController/dataController.cpp)
target_link_libraries(dataController tinyplyLib tinyfiledialogs)

# Callback functions
include_directories(lib/callbackFunc)
add_library(callbackFunc STATIC lib/callbackFunc/callbackFunc.cpp)
target_link_libraries(callbackFunc displayFunc dataController)

### MAIN EXECUTABLE ###

add_executable(gl-recons-viewer main.cpp )
target_link_libraries(gl-recons-viewer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}
        arcball displayFunc dataController callbackFunc)