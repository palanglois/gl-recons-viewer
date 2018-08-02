#ifndef GL_RECONS_VIEWER_DATACONTROLLER_H
#define GL_RECONS_VIEWER_DATACONTROLLER_H

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <fstream>
#include <string>
#include "tinyply.h"
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "Arcball.hpp"

using namespace std;
using namespace tinyply;

#define MAX_TRIANGLES (1305963)

enum {
    WIREFRAME, HIDDENLINE, FLATSHADED, SMOOTHSHADED
};

struct float3 {
    float x, y, z;
};
struct uint3 {
    uint32_t x, y, z;
};

struct Point {
    float x[3];
    float n[3];
};

struct Triangle {
    Point v[3];
};

struct windowData
{
    Triangle triangleList[MAX_TRIANGLES];
    int triangleCount = 0;
    Arcball arcball;
    long xsize, ysize;
    float aspect;
    int displayMode;
    bool leftButton, middleButton;
};

void LoadOrientedTriangles(std::string filename, windowData *data);

#endif //GL_RECONS_VIEWER_DATACONTROLLER_H
