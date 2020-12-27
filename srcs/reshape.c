#include "fractal.h"

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2., w / 2., -h / 2., h / 2.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
