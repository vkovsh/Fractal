#ifndef FRACTAL_H
# define FRACTAL_H
# include <GL/glut.h>
# include <stdbool.h>

# include "retcode.h"

# define MAX_HEIGHT 2048
# define MAX_WIDTH 2048

typedef struct	s_rectangle
{
	int x_0;
	int y_0;
	int x_end;
	int y_end;
}				t_rectangle;

typedef struct  s_complex
{
    double re;
    double im;
}               t_complex;

typedef enum    e_fractaltype
{
    MANDELBROT = 0,
    FRACTAL_TOTAL = 1,
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
	GLuint64		scale;
	t_checker		checker;
	size_t			iterations;
	GLint64			x_0;
	GLint64			y_0;
	GLint64			x_pos;
	GLint64			y_pos;
	bool			is_keypressed;				
	t_fractaltype	ftype;
	uint16_t		height;
	uint16_t		width;
	// GLuint			*pixels_addr;
	// GLuint			**pixels_array;
}					t_fractal;

typedef struct	s_fractalarray
{
	GLuint			*pixels_addr;
	GLuint			**pixels_array;
}				t_fractalaaray;

void    set_colors();

typedef uint32_t t_color;

extern t_fractal	*g_f;
extern t_colordepth	g_colordepth;
extern t_fractalaaray	*g_fractalarray;

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
void		mouse(int button, int state, int x, int y);

t_retcode	init_gl(int argc, char** argv);
t_retcode	init_fractal(const t_fractaltype ftype,
            			const GLuint height,
            			const GLuint width,
            			const size_t iterations);

t_retcode   delete_fractal(t_fractal *f);

size_t		in_mandelbrot(t_complex c);

#endif