#include "Display.h"
#include "glut/glut.h"
#include <iostream>

using namespace std;

//#pragma comment(lib,"..\\glut\\glut32.lib")

PathTracer* Display::pPathTracer = NULL;

Display::Display(PathTracer* _PathTracer)
{
    pPathTracer = _PathTracer;

    
}

void Display::render()
{
    int width = pPathTracer->getScene()->getWidth();
    int height = pPathTracer->getScene()->getHeight();

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    float* colors = pPathTracer->render();

    glRasterPos2i(0, 0);
    glDrawPixels(width, height, GL_RGB, GL_FLOAT, (GLvoid *)colors);

    glFlush();
}

void Display::update()
{
    glutPostRedisplay();
}

void Display::run()
{
    int width = pPathTracer->getScene()->getWidth();
    int height = pPathTracer->getScene()->getHeight();
    cout << "width:" << width << ",height:" << height << endl;
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 80);
    glutCreateWindow("Monte Carlo Path Tracer");
    glutDisplayFunc(render);

    glutIdleFunc(update);

    glutMainLoop();
}