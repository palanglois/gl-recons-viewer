#ifndef GL_RECONS_VIEWER_CALLBACKFUNC_H
#define GL_RECONS_VIEWER_CALLBACKFUNC_H

#include <GL/glut.h>
#include "dataController.h"
#include "displayFunc.h"

void ReshapeCallback(int width, int height);
void SetDisplayMenu(int value);
void SetMainMenu(int value);
void DisplayCallback(void);
void KeyboardCallback(unsigned char ch, int x, int y);
void MouseCallback(int button, int state, int x, int y);
void MotionCallback(int x, int y);

#endif //GL_RECONS_VIEWER_CALLBACKFUNC_H
