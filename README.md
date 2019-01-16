# OpenGL Viewer for 3D Reconstruction

## Build and use instruction

* Dependencies : `sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev libxmu-dev libxi-dev`

Build with CMake.

If a segmentation fault appears at run time, you may have to set the following environment variable : `LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0`

## Use 

Launch : `./gl-recons-viewer /path/to/file1.ply /path/to/file2.ply /path/to/file2.json ...`

* **Left mouse**: rotate  
* **Middle mouse**:  move
* **Scroll**: zoom
* **Right mouse**:  menu
* **ESC** to quit

## Example
Here is a representation of the output of [Line3d++](https://github.com/manhofer/Line3Dpp) by Manuel Hofer. We can observe the camera poses and the visibility lines between each reconstructed 3D line and the point of views that generated it.
![Example image](http://imagine.enpc.fr/~langloip/data/Input_data.png)
