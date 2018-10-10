#include "callbackFunc.h"


void ReshapeCallback(int width, int height) {
    windowData *data = (windowData *) glutGetWindowData();
    Arcball& arcball = data->arcball;

    arcball.SetWidthHeight(width, height);
    long& xsize = data->xsize;
    long& ysize = data->ysize;
    float& aspect = data->aspect;

    xsize = width;

    ysize = height;

    aspect = (float) xsize / (float) ysize;

    glViewport(0, 0, xsize, ysize);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutPostRedisplay();
}

void SetDisplayMenu(int value) {
    windowData *data = (windowData *) glutGetWindowData();
    int& displayMode = data->displayMode;

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
        case 98:
            openAndDetectFile();
            break;
    }
}


void DisplayCallback(void) {
    windowData *data = (windowData *) glutGetWindowData();
    int& displayMode = data->displayMode;

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
    (void)x;
    (void)y;
    switch (ch) {
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}


void MouseCallback(int button, int state, int x, int y) {
    windowData *data = (windowData *) glutGetWindowData();
    Arcball& arcball = data->arcball;
    bool& leftButton = data->leftButton;
    bool& middleButton = data->middleButton;


    leftButton = (button == GLUT_LEFT_BUTTON);

    if (leftButton) {
        if (state == GLUT_DOWN)
            arcball.StartRotation(x, y);
        else
            arcball.StopRotation();
    }

    middleButton = (button == GLUT_MIDDLE_BUTTON);

    if (middleButton) {
        if (state == GLUT_DOWN)
            arcball.StartDragging(x, y);
        else
            arcball.StopDragging();
    }

    if ((button == 3) || (button == 4)) // It's a wheel event
    {
        int direction = (button == 3) ? 1 : -1;
        // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
        if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
        arcball.StartZooming(0, 0);
        arcball.UpdateZooming(-direction * y, direction * x);
        arcball.StopZooming();
    }

    glutPostRedisplay();
}


void MotionCallback(int x, int y) {
    windowData *data = (windowData *) glutGetWindowData();
    Arcball& arcball = data->arcball;
    bool& leftButton = data->leftButton;
    bool& middleButton = data->middleButton;

    if (leftButton)
        arcball.UpdateRotation(x, y);

    if (middleButton)
        arcball.UpdateDragging(x, y);

    glutPostRedisplay();
}