# OpenGL Viewer for 3D Reconstruction

## Build and use instruction

* Dependencies : `sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev`

Build with CMake.

If a segmentation fault appears at run time, you may have to set the following environment variable : `LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0`

Use : `./opengl_test -i /path/to/file.ply`