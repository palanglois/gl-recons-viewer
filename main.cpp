/* Simple geometry viewer:  Left mouse: rotate;  Middle mouse:  zoom;  Right mouse:   menu;  ESC to quit

 The function InitGeometry() initializes  the geometry that will be displayed. */

#include <assert.h>

#include <math.h>

#include <stdlib.h>

#include <fstream>
#include <string>
#include <iostream>
#include <cstring>

#include "option_parser.h"

#include <GL/glut.h>

#include "tinyply.h"

using namespace std;
using namespace tinyply;

#define MAX_TRIANGLES (1305963)
#define NORMAL_FACTOR 0.05f


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

Triangle triangleList[MAX_TRIANGLES];

int triangleCount = 0;


/* Viewer state */

float sphi = 90.0, stheta = 45.0;

float sdepth = 10;

float zNear = 1.0, zFar = 100.0;

float aspect = 5.0 / 4.0;

float xcam = 0, ycam = 0;

long xsize, ysize;

int downX, downY;

bool leftButton = false, middleButton = false;

int i, j;

GLfloat light0Position[] = {0, 1, 0, 1.0};

int displayMenu, mainMenu;

enum {
    WIREFRAME, HIDDENLINE, FLATSHADED, SMOOTHSHADED
};

int displayMode = HIDDENLINE;


void MyIdleFunc(void) { glutPostRedisplay(); } /* things to do while idle */

void RunIdleFunc(void) { glutIdleFunc(MyIdleFunc); }

void PauseIdleFunc(void) { glutIdleFunc(NULL); }

void DrawSmoothShaded(void) {

    int i;

    assert(triangleCount < MAX_TRIANGLES);

    glColor3f(0.8f, 0.2f, 0.8f);

    glBegin(GL_TRIANGLES);

    for (i = 0; i < triangleCount; ++i) {

        glNormal3fv(triangleList[i].v[0].n);

        glVertex3fv(triangleList[i].v[0].x);

        glNormal3fv(triangleList[i].v[1].n);

        glVertex3fv(triangleList[i].v[1].x);

        glNormal3fv(triangleList[i].v[2].n);

        glVertex3fv(triangleList[i].v[2].x);
    }

    glEnd();

    for (i = 0; i < triangleCount; ++i) {

        float center_x = (triangleList[i].v[0].x[0] + triangleList[i].v[1].x[0] + triangleList[i].v[2].x[0]) / 3.f;
        float center_y = (triangleList[i].v[0].x[1] + triangleList[i].v[1].x[1] + triangleList[i].v[2].x[1]) / 3.f;
        float center_z = (triangleList[i].v[0].x[2] + triangleList[i].v[1].x[2] + triangleList[i].v[2].x[2]) / 3.f;

        float triangle_center[3] = {center_x, center_y, center_z};

        float norm_extr_x = center_x + NORMAL_FACTOR * triangleList[i].v[0].n[0];
        float norm_extr_y = center_y + NORMAL_FACTOR * triangleList[i].v[0].n[1];
        float norm_extr_z = center_z + NORMAL_FACTOR * triangleList[i].v[0].n[2];

        float norm_extr[3] = {norm_extr_x, norm_extr_y, norm_extr_z};

        glColor3f(1.0, 0.0, 0.0);

        glBegin(GL_LINE_STRIP);

        glVertex3fv(triangle_center);
        glVertex3fv(norm_extr);

        glEnd();

    }
}

void DrawWireframe(void) {

    int i;


    for (i = 0; i < triangleCount; ++i) {

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_LINE_STRIP);

        glVertex3fv(triangleList[i].v[0].x);

        glVertex3fv(triangleList[i].v[1].x);

        glVertex3fv(triangleList[i].v[2].x);

        glVertex3fv(triangleList[i].v[0].x);

        glEnd();

        float center_x = (triangleList[i].v[0].x[0] + triangleList[i].v[1].x[0] + triangleList[i].v[2].x[0]) / 3.f;
        float center_y = (triangleList[i].v[0].x[1] + triangleList[i].v[1].x[1] + triangleList[i].v[2].x[1]) / 3.f;
        float center_z = (triangleList[i].v[0].x[2] + triangleList[i].v[1].x[2] + triangleList[i].v[2].x[2]) / 3.f;

        float triangle_center[3] = {center_x, center_y, center_z};

        float norm_extr_x = center_x + NORMAL_FACTOR * triangleList[i].v[0].n[0];
        float norm_extr_y = center_y + NORMAL_FACTOR * triangleList[i].v[0].n[1];
        float norm_extr_z = center_z + NORMAL_FACTOR * triangleList[i].v[0].n[2];

        float norm_extr[3] = {norm_extr_x, norm_extr_y, norm_extr_z};

        glColor3f(1.0, 0.0, 0.0);

        glBegin(GL_LINE_STRIP);

        glVertex3fv(triangle_center);
        glVertex3fv(norm_extr);

        glEnd();
    }
}


void DrawFlatShaded(void) {

    int i;

    glEnable(GL_POLYGON_OFFSET_FILL);

    glColor3f(0.8f, 0.2f, 0.8f);

    glBegin(GL_TRIANGLES);

    for (i = 0; i < triangleCount; ++i) {

        glVertex3fv(triangleList[i].v[0].x);

        glVertex3fv(triangleList[i].v[1].x);

        glVertex3fv(triangleList[i].v[2].x);
    }

    glEnd();

    glDisable(GL_POLYGON_OFFSET_FILL);
}


void DrawHiddenLine(void) {

    glEnable(GL_POLYGON_OFFSET_FILL);

    glColor3f(0, 0, 0);

    glBegin(GL_TRIANGLES);

    for (i = 0; i < triangleCount; ++i) {

        glVertex3fv(triangleList[i].v[0].x);

        glVertex3fv(triangleList[i].v[1].x);

        glVertex3fv(triangleList[i].v[2].x);
    }

    glEnd();

    glDisable(GL_POLYGON_OFFSET_FILL);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    for (i = 0; i < triangleCount; ++i) {
        glColor3f(0.4, 0.4, 0.4);
        glBegin(GL_TRIANGLES);

        glVertex3fv(triangleList[i].v[0].x);

        glVertex3fv(triangleList[i].v[1].x);

        glVertex3fv(triangleList[i].v[2].x);
        glEnd();


        float center_x = (triangleList[i].v[0].x[0] + triangleList[i].v[1].x[0] + triangleList[i].v[2].x[0]) / 3.f;
        float center_y = (triangleList[i].v[0].x[1] + triangleList[i].v[1].x[1] + triangleList[i].v[2].x[1]) / 3.f;
        float center_z = (triangleList[i].v[0].x[2] + triangleList[i].v[1].x[2] + triangleList[i].v[2].x[2]) / 3.f;

        float triangle_center[3] = {center_x, center_y, center_z};

        float norm_extr_x = center_x + NORMAL_FACTOR * triangleList[i].v[0].n[0];
        float norm_extr_y = center_y + NORMAL_FACTOR * triangleList[i].v[0].n[1];
        float norm_extr_z = center_z + NORMAL_FACTOR * triangleList[i].v[0].n[2];

        float norm_extr[3] = {norm_extr_x, norm_extr_y, norm_extr_z};

        glColor3f(0.8, 0.0, 0.0);

        glBegin(GL_LINE_STRIP);

        glVertex3fv(triangle_center);
        glVertex3fv(norm_extr);

        glEnd();
    }


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void ReshapeCallback(int width, int height) {

    xsize = width;

    ysize = height;

    aspect = (float) xsize / (float) ysize;

    glViewport(0, 0, xsize, ysize);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutPostRedisplay();
}


void SetDisplayMenu(int value) {

    displayMode = value;

    switch (value) {

        case WIREFRAME:
            glShadeModel(GL_FLAT);
            glDisable(GL_LIGHTING);
            break;

        case HIDDENLINE:
            glShadeModel(GL_FLAT);
            glDisable(GL_LIGHTING);
            break;

        case FLATSHADED:
            glShadeModel(GL_FLAT);
            glEnable(GL_LIGHTING);
            break;

        case SMOOTHSHADED:
            glShadeModel(GL_SMOOTH);
            glEnable(GL_LIGHTING);
            break;
    }

    glutPostRedisplay();
}


void SetMainMenu(int value) {
    switch (value) {
        case 99:
            exit(0);
            break;
    }
}


void DisplayCallback(void) {

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(64.0, aspect, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(xcam, ycam, -sdepth);

    glRotatef(-stheta, 1.0, 0.0, 0.0);

    glRotatef(sphi, 0.0, 0.0, 1.0);

    switch (displayMode) {

        case WIREFRAME:
            DrawWireframe();
            break;

        case HIDDENLINE:
            DrawHiddenLine();
            break;

        case FLATSHADED:
            DrawFlatShaded();
            break;

        case SMOOTHSHADED:
            DrawSmoothShaded();
            break;
    }

    glutSwapBuffers();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void KeyboardCallback(unsigned char ch, int x, int y) {

    switch (ch) {
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}


void MouseCallback(int button, int state, int x, int y) {

    downX = x;
    downY = y;

    leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));

    middleButton = ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN));

    glutPostRedisplay();
}


void MotionCallback(int x, int y) {

    if (leftButton) {
        sphi += (float) (x - downX) / 4.0;
        stheta += (float) (downY - y) / 4.0;
    } // rotate

    if (middleButton) { sdepth += (float) (downY - y) / 10.0; } // scale

    downX = x;
    downY = y;

    glutPostRedisplay();
}

void catchKey(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)
        xcam += 0.2;
    else if (key == GLUT_KEY_RIGHT)
        xcam -= 0.2;
    else if (key == GLUT_KEY_DOWN)
        ycam += 0.2;
    else if (key == GLUT_KEY_UP)
        ycam -= 0.2;
    glutPostRedisplay();
}


void InitGL() {

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(600, 600);

    glutCreateWindow("Plane orientation Viewer");

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glPolygonOffset(1.0, 1.0);

    glDisable(GL_CULL_FACE);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

    glEnable(GL_LIGHT0);

    glutReshapeFunc(ReshapeCallback);

    glutDisplayFunc(DisplayCallback);

    glutKeyboardFunc(KeyboardCallback);

    glutMouseFunc(MouseCallback);

    glutMotionFunc(MotionCallback);

    glutSpecialFunc(catchKey);
}


void InitMenu() {

    displayMenu = glutCreateMenu(SetDisplayMenu);

    glutAddMenuEntry("Wireframe", WIREFRAME);

    glutAddMenuEntry("Hidden Line", HIDDENLINE);

    //glutAddMenuEntry("Flat Shaded", FLATSHADED);

    glutAddMenuEntry("Smooth Shaded", SMOOTHSHADED);

    mainMenu = glutCreateMenu(SetMainMenu);

    glutAddSubMenu("Display", displayMenu);

    glutAddMenuEntry("Exit", 99);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void InitGeometry(std::string filename) {
    std::ifstream ss(filename, std::ios::binary);
    PlyFile file;
    file.parse_header(ss);

    std::shared_ptr<PlyData> vertices, normals, faces;

    try { vertices = file.request_properties_from_element("vertex", {"x", "y", "z"}); }
    catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

    try { normals = file.request_properties_from_element("face", {"nx", "ny", "nz"}); }
    catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

    try { faces = file.request_properties_from_element("face", {"vertex_index"}); }
    catch (const std::exception &e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

    file.read(ss);

    std::vector<float3> verts(vertices->count);
    const size_t numVerticesBytes = vertices->buffer.size_bytes();
    std::memcpy(verts.data(), vertices->buffer.get(), numVerticesBytes);
    std::vector<float3> norms(normals->count);
    const size_t numNormalsBytes = normals->buffer.size_bytes();
    std::memcpy(norms.data(), normals->buffer.get(), numNormalsBytes);
    std::vector<uint3> facs(faces->count);
    const size_t numFacesBytes = faces->buffer.size_bytes();
    std::memcpy(facs.data(), faces->buffer.get(), numFacesBytes);
    triangleCount = int(facs.size());
    for (int i = 0; i < facs.size(); i++) {
        triangleList[i].v[0].x[0] = verts[facs[i].x].x;
        triangleList[i].v[0].x[1] = verts[facs[i].x].y;
        triangleList[i].v[0].x[2] = verts[facs[i].x].z;

        triangleList[i].v[0].n[0] = norms[i].x;
        triangleList[i].v[0].n[1] = norms[i].y;
        triangleList[i].v[0].n[2] = norms[i].z;

        triangleList[i].v[1].x[0] = verts[facs[i].y].x;
        triangleList[i].v[1].x[1] = verts[facs[i].y].y;
        triangleList[i].v[1].x[2] = verts[facs[i].y].z;

        triangleList[i].v[1].n[0] = norms[i].x;
        triangleList[i].v[1].n[1] = norms[i].y;
        triangleList[i].v[1].n[2] = norms[i].z;

        triangleList[i].v[2].x[0] = verts[facs[i].z].x;
        triangleList[i].v[2].x[1] = verts[facs[i].z].y;
        triangleList[i].v[2].x[2] = verts[facs[i].z].z;

        triangleList[i].v[2].n[0] = norms[i].x;
        triangleList[i].v[2].n[1] = norms[i].y;
        triangleList[i].v[2].n[2] = norms[i].z;
    }

}


int main(int argc, char **argv) {

    //Create parsing options
    op::OptionParser opt;
    opt.add_option("-h", "--help", "show option help");
    opt.add_option("-i", "--input", "Input ply file", "");

    //Parsing options
    bool correctParsing = opt.parse_options(argc, argv);
    if (!correctParsing)
        return EXIT_FAILURE;

    if (op::str2bool(opt["-h"]) || opt["-i"] == "") {
        opt.show_help();
        return 0;
    }

    string filename = opt["-i"];


    glutInit(&argc, argv);

    InitGL();

    InitMenu();

    InitGeometry(filename);

    cout << "Simple geometry viewer:  Left mouse: rotate;  Middle mouse:  zoom;  Right mouse:   menu;  ESC to quit"
         << endl;

    glutMainLoop();

    return 0;
}