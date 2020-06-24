#include "fractal.h"

void    draw_triangle(t_point2D p1, t_point2D p2, t_point2D p3,
                    GLfloat r, GLfloat g, GLfloat b)
{
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1.0, 0, 0); // red
        // glVertex2f( -0.8, -0.8 );
        glVertex2f(p1.x, p1.y);
        glColor3f(0, 1.0, 0); // green
        // glVertex2f( 0.8, -0.8 );
        glVertex2f(p2.x, p2.y);
        glColor3f(0, 0, 1.0); // blue
        // glVertex2f( 0, 0.9 );
        glVertex2f(p3.x, p3.y);
    }
    glEnd(); 
}
