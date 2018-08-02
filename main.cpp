/* Simple geometry viewer:  Left mouse: rotate;  Middle mouse:  zoom;  Right mouse:   menu;  ESC to quit */

#include <cassert>

#include <cmath>

#include "option_parser.h"

#include <GL/glut.h>

#include "displayFunc.h"
#include "callbackFunc.h"

using namespace std;


/* Viewer state */

float sdepth = 10;

float zNear = 1.0, zFar = 100.0;

float xcam = 0, ycam = 0;

GLfloat light0Position[] = {0, 1, 0, 1.0};

int displayMenu, mainMenu;


void InitGL(windowData *data) {

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


    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(64.0, data->aspect, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(xcam, ycam, -sdepth);
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

    // Init the data
    windowData *myData = new windowData();
    myData->arcball = Arcball();
    myData->aspect = 5.0f / 4.0f;
    myData->displayMode = HIDDENLINE;
    myData->leftButton = false;
    myData->middleButton = false;
    LoadOrientedTriangles(filename, myData);

    InitGL(myData);

    InitMenu();

    glutSetWindowData(myData);

    cout
            << "Simple geometry viewer:  Left mouse: rotate;  Middle mouse:  move;  Scroll: zoom;  Right mouse:  menu;  ESC to quit"
            << endl;

    glutMainLoop();

    return 0;
}
