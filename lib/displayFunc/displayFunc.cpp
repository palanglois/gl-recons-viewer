#include "displayFunc.h"


void DrawSmoothShaded(void) {

    windowData *data = (windowData *) glutGetWindowData();
    int triangleCount = data->triangleCount;
    Triangle *triangleList = data->triangleList;

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
    windowData *data = (windowData *) glutGetWindowData();
    int triangleCount = data->triangleCount;
    Triangle *triangleList = data->triangleList;

    int i;


    for (i = 0; i < triangleCount; ++i) {

        glColor3f(0.4, 0.4, 0.4);

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

        glColor3f(0.8, 0.0, 0.0);

        glBegin(GL_LINE_STRIP);

        glVertex3fv(triangle_center);
        glVertex3fv(norm_extr);

        glEnd();
    }
}


void DrawFlatShaded(void) {
    windowData *data = (windowData *) glutGetWindowData();
    int triangleCount = data->triangleCount;
    Triangle *triangleList = data->triangleList;

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
    windowData *data = (windowData *) glutGetWindowData();
    int triangleCount = data->triangleCount;
    Triangle *triangleList = data->triangleList;

    glEnable(GL_POLYGON_OFFSET_FILL);

    glColor3f(0, 0, 0);

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < triangleCount; ++i) {

        glVertex3fv(triangleList[i].v[0].x);

        glVertex3fv(triangleList[i].v[1].x);

        glVertex3fv(triangleList[i].v[2].x);
    }

    glEnd();

    glDisable(GL_POLYGON_OFFSET_FILL);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    for (int i = 0; i < triangleCount; ++i) {
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

