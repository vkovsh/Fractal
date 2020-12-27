#include "fractal.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

uint8_t			gradient_pow(uint8_t gradient, uint8_t stepen)
{
    uint8_t     result;

    result = gradient;
    while (stepen-- != 1)
    {
        result *= gradient;
    }
    return (result);
}

t_color				set_color(uint8_t r, uint8_t g, uint8_t b)
{
	t_color			color;

	color = r | (g << 8) | (b << 16) | 0xff000000;
	return (color);
}

int     colors[1000];

void    set_colors()
{
    srand(time(0));
    for (int i = 0; i < 1000; ++i)
    {
        // colors[i] = set_color(gradient_pow(i, g_colordepth.depth_r),
										// gradient_pow(i, g_colordepth.depth_g),
										// gradient_pow(i, g_colordepth.depth_b));
        colors[i] = rand() % 256;
        colors[i] |= (rand() % 256) << 8;
        colors[i] |= (rand() % 256) << 16;
        colors[i] |= 0xff000000;
    }
}

void    *fill_fractal_array(void *r)
{
    // glClearColor(0.0, 0.0, 0.0, 0.0);

    t_complex c;
	t_rectangle *_r = (t_rectangle *)r;
            
    c.im = (long double)((-g_f->height) / 2 + g_f->y_0) / g_f->scale;
    long double delta = (long double)1 / g_f->scale;
    // printf("delta = %LG\n", delta);
    long double c_re_init = (long double)((-g_f->width) / 2 - g_f->x_0 + _r->x_0) / g_f->scale; 
    for (int i = _r->y_0; i < _r->y_end; ++i)
    {
        c.im += delta;
        c.re = c_re_init;
        for (int j = _r->x_0; j < _r->x_end; ++j)
        {
            c.re += delta;
            size_t iterations = g_f->checker(c);
            if (iterations != g_f->iterations)
			{
                g_fractalarray->pixels_array[i][j] = colors[iterations];
			}
			else
			{
                g_fractalarray->pixels_array[i][j] = 0;
			}
        }
    }
    return (NULL);
}

void    draw(void)
{
    fill_fractal();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Запомнить атрибут
    glPushAttrib(GL_CURRENT_BIT);

    //Вычислить предварительное положение начала вывода битового массива
    double x, y, z;

    //Видовая матрица
    GLdouble modelMatrix[16];
    glGetDoublev(GL_MODELVIEW_MATRIX , modelMatrix);
    
    //Матрица проекций
    GLdouble projMatrix[16];
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    
    //Координаты области вывода
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    gluUnProject(viewport[0] + 1, viewport[1] + 1, 0, modelMatrix, projMatrix, viewport, &x, &y, &z);

    int dx, dy;
    dy = 0;
    dx = 0;

    int xp, yp;
    xp = g_f->x_pos;
    yp = g_f->y_pos;

    if (g_f->y_pos < y)
    {
        dy = y - g_f->y_pos;
        yp = y;
    }

    if (g_f->x_pos < x)
    {
        dx = x - g_f->x_pos;
        xp = x;
    }

    //Установить положение начала вывода битового массива
    glRasterPos2f(xp, yp);
    
    //Задать атрибуты вывода пикселов
    glPixelStorei(GL_UNPACK_ROW_LENGTH, g_f->width); //длина строки
    glPixelStorei(GL_UNPACK_SKIP_ROWS, dy); // сколько строк пропустить?
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, dx); // сколько пикселов пропустить в каждой строке?
    
    //Отобразить пикселы на экране
    glDrawPixels(g_f->width - dx, g_f->height - dy, GL_RGBA, GL_UNSIGNED_BYTE, g_fractalarray->pixels_addr);
    
    //Вернуть исходные значения атрибутам вывода
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

    //Вернуть атрибут
    glPopAttrib();

    glFlush();

    glutSwapBuffers();
}

void			fill_fractal(void)
{
    const int thread_count = 1;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    pthread_t   pth[thread_count];
	t_rectangle r[thread_count];

    clock_t start, stop;
    start = clock();
	for (int i = 0; i < thread_count; ++i)
    {
        r[i] = (t_rectangle){i * g_f->width / thread_count, 0, (i + 1) * g_f->width / thread_count, g_f->height};
	    if (0 != pthread_create(&pth[i], NULL, fill_fractal_array, &r[i]))
        {
            printf("%d error\n", i);
        }
    }
	for (int i = 0; i < thread_count; ++i)
    {
    	pthread_join(pth[i], NULL);
    }
    stop = clock();
    printf("FillTime = %f\n", (double)(stop - start) / CLOCKS_PER_SEC);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    g_f->x_pos = -g_f->width / 2;
    g_f->y_pos = -g_f->height / 2;
    g_f->is_keypressed = false;
}