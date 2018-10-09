/* Simple geometry viewer:  Left mouse: rotate;  Middle mouse:  zoom;  Right mouse:   menu;  ESC to quit */

#include <cassert>

#include <cmath>

#include <GL/glut.h>

#include "displayFunc.h"
#include "callbackFunc.h"
#include "dataController.h"

using namespace std;


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

    glLightfv(GL_LIGHT0, GL_POSITION, data->light0Position);

    glEnable(GL_LIGHT0);

    glutReshapeFunc(ReshapeCallback);

    glutDisplayFunc(DisplayCallback);

    glutKeyboardFunc(KeyboardCallback);

    glutMouseFunc(MouseCallback);

    glutMotionFunc(MotionCallback);


    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(64.0, data->aspect, data->zNear, data->zFar);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(data->xcam, data->ycam, -data->sdepth);
}


void InitMenu(windowData *data) {

    data->displayMenu = glutCreateMenu(SetDisplayMenu);

    glutAddMenuEntry("Wireframe", WIREFRAME);

    glutAddMenuEntry("Hidden Line", HIDDENLINE);

    //glutAddMenuEntry("Flat Shaded", FLATSHADED);

    glutAddMenuEntry("Smooth Shaded", SMOOTHSHADED);

    data->mainMenu = glutCreateMenu(SetMainMenu);

    glutAddMenuEntry("Open file", 98);

    glutAddSubMenu("Display", data->displayMenu);

    glutAddMenuEntry("Exit", 99);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char **argv) {

    glutInit(&argc, argv);

    // Init the data
    auto *myData = new windowData();
    myData->arcball = Arcball();
    myData->aspect = 5.0f / 4.0f;
    myData->displayMode = HIDDENLINE;
    myData->leftButton = false;
    myData->middleButton = false;
    myData->light0Position[0] = 0.f;
    myData->light0Position[1] = 1.f;
    myData->light0Position[2] = 0.f;
    myData->light0Position[3] = 1.f;
    myData->sdepth = 10.f;
    myData->xcam = 0.f;
    myData->ycam = 0.f;
    myData->zNear = 1.f;
    myData->zFar = 100.f;
    myData->displayPov = false;

    InitGL(myData);

    InitMenu(myData);

    glutSetWindowData(myData);

    // Load data from command line
    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-pov") == 0)
            myData->displayPov = true;
        else
            openFile(argv[i], myData);
    }

    cout
            << "Simple geometry viewer:  Left mouse: rotate;  Middle mouse:  move;  Scroll: zoom;  Right mouse:  menu;  ESC to quit"
            << endl;

    glutMainLoop();

    return 0;
}
