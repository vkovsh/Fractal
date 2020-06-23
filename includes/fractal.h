#ifndef FRACTAL_H
# define FRACTAL_H
# include <GL/glut.h>
# include <stdbool.h>

# include "retcode.h"

# define MAX_HEIGHT 2048
# define MAX_WIDTH 2048

typedef struct	s_point2D
{
	double		x;
	double		y;
}				t_point2D;

typedef struct	s_rectangle
{
	int x_0;
	int y_0;
	int x_end;
	int y_end;
}				t_rectangle;

typedef struct  s_complex
{
    long double re;
    long double im;
}               t_complex;

typedef enum    e_fractaltype
{
    MANDELBROT = 0,
	JULIA = 1,
    FRACTAL_TOTAL = 2,
}               t_fractaltype;

typedef size_t	(*t_checker)(t_complex);

typedef struct		s_colordepth
{
	GLubyte			depth_r;
	GLubyte			depth_g;
	GLubyte			depth_b;
}					t_colordepth;

typedef struct		s_fractal
{
	t_fractaltype	type;
	long double		scale;
	t_checker		checker;
	uint16_t		iterations;
	long double		x_0;
	long double		y_0;
	int16_t			x_pos;
	int16_t			y_pos;
	bool			is_keypressed;
	uint16_t		height;
	uint16_t		width;
}					t_fractal;

typedef struct		s_fractalarray
{
	GLuint			*pixels_addr;
	GLuint			**pixels_array;
}					t_fractalaaray;

void    set_colors();

typedef uint32_t t_color;

extern t_fractal		*g_f;
extern t_colordepth		g_colordepth;
extern t_fractalaaray	*g_fractalarray;
extern t_complex		g_julia_arg;

// typedef struct      s_environment
// {
// 	size_t			height;
// 	size_t			width;
// 	t_fractaltype	fractal_type;
// 	double			z;
// 	pthread_t		pth;
// 	int				iter;
// 	double			x_abs;
// 	double			y_abs;
// 	int				animation;
// 	t_complex		julia_arg;
// 	int				move;
// 	int				zoom;
// 	int				do_iter;
// 	int				julia_an;
// 	int				julia_freeze;
// 	int				do_opacity;
// 	int				(*checker)(t_complex);
// }					t_environment;

void		fill_fractal(void);

void		*fill_fractal_array(void *r);

void		draw(void);
void		reshape(int w, int h);
void		motion(int x, int y);
void		passive_motion(int x, int y);
void		mouse(int button, int state, int x, int y);

t_retcode	init_gl(int argc, char** argv);
t_retcode	init_fractal(const t_fractaltype ftype,
            			const GLuint height,
            			const GLuint width,
            			const size_t iterations);

t_retcode   delete_fractal(t_fractal *f);

size_t		in_mandelbrot(t_complex c);
size_t		in_julia(t_complex z);

#endif