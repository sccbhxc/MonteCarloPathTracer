#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "PathTracer.h"

class Display
{
public:
    static PathTracer* pPathTracer;

    Display(PathTracer* _pPathTracer);

    static void render();
    static void update();
    void run();


};

#endif