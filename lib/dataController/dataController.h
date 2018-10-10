#ifndef GL_RECONS_VIEWER_DATACONTROLLER_H
#define GL_RECONS_VIEWER_DATACONTROLLER_H

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <fstream>
#include <string>
#include "tinyfiledialogs.h"
#include "json.hpp"
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "Arcball.hpp"
#include "Line.h"

using namespace std;

#define MAX_TRIANGLES (3305963)

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
    std::vector<Line> lineList;
    int triangleCount = 0;
    Arcball arcball;
    long xsize, ysize;
    float aspect;
    int displayMode;
    bool leftButton, middleButton;
    int displayMenu, mainMenu;
    GLfloat light0Position[4];
    float sdepth;
    float xcam, ycam;
    float zNear, zFar;
    bool displayPov;
};

void openAndDetectFile(void);
void LoadLinesFromJson(std::string fileName, windowData *data);
void LoadOrientedTriangles(std::string fileName, windowData *data);
void openFile(const std::string &fileName, windowData *data);

/* Conversion from json to Vec3d */
inline Vector3d json2vec3d(const nlohmann::json& jsonData)
{
    assert(jsonData.type() == nlohmann::json::value_t::array);
    assert(jsonData.size() == 3);
    return {jsonData[0], jsonData[1], jsonData[2]};
}

#endif //GL_RECONS_VIEWER_DATACONTROLLER_H
