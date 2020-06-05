#include <math.h>
#include <stdio.h>

#include "fractal.h"

t_complex		g_julia_arg;

size_t			in_julia(t_complex z)
{
	t_complex	o;
	t_complex	c;
	int			iter;

	c.re = g_julia_arg.re;
	c.im = g_julia_arg.re;
	for (iter = 0; iter < g_f->iterations; ++iter)
	{
		if (z.re * z.re + z.im * z.im > 4)
		{
			break ;
		}
		o = z;
		z.re = o.re * o.re - o.im * o.im + c.re;
		z.im = 2 * o.re * o.im + c.im;
	}
	return (iter);
}

size_t			in_mandelbrot(t_complex c)
{
	t_complex	o;
	size_t		iter;
	double		tmp;

	tmp = c.re - 0.25;
	if (sqrt(tmp * tmp + c.im * c.im) < 0.5 - 0.5 * cos(atan2(c.im, tmp)))
	{
		return (g_f->iterations);
	}
	o.re = 0;
	o.im = 0;
	for (iter = 0; iter < g_f->iterations; ++iter)
	{
		double re_aquare = o.re * o.re;
		double im_square = o.im * o.im;
		if (re_aquare + im_square > 4)
		{
			break ;
		}
		o.im = 2 * o.re * o.im + c.im;
		o.re = re_aquare - im_square + c.re;
	}
	return (iter);
}