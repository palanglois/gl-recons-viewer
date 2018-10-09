#ifndef GL_RECONS_VIEWER_DISPLAYFUNC_H
#define GL_RECONS_VIEWER_DISPLAYFUNC_H

#include <cassert>
#include "dataController.h"

#define NORMAL_FACTOR 0.05f

void DrawSmoothShaded(void);
void DrawWireframe(void);
void DrawFlatShaded(void);
void DrawHiddenLine(void);

void drawLines(std::vector<Line>& lineList, bool withPov=false);

#endif //GL_RECONS_VIEWER_DISPLAYFUNC_H
