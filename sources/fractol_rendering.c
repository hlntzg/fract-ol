/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:04:31 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/22 12:26:05 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* This function loops through each pixel on the screen, and use the specific 
 * fractal set function to map the pixel to a point in the complex plane. It
 * determines the pixel's color based on the iterations before escape. */
void	ft_fractol_render(void *param)
{
	t_fractol	*fractol;
	uint32_t	x;
	uint32_t	y;

	fractol = (t_fractol *)param;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (ft_strequ(fractol->set, "julia"))
				julia(x, y, fractol);
			if (ft_strequ(fractol->set, "mandelbrot"))
				mandelbrot(x, y, fractol);
			mlx_put_pixel(fractol->image, x, y, fractol->get.color);
			y++;
		}
		x++;
	}
}

/* This function is responsable for iterating a pair of complex numbers
 * until either the absolute value of Z exceeds the system’s max values or the
 * number of iterations exceeds the maximum allowed. It calculates the escape
 * time for mandelbrot and julia fractals, with a slight variation in parameters
 * provided to the function (see details in julia() and mandelbrot()). */
void	compute_escape_time(t_fractol *fractol)
{
	double	tmp;
	double	zx;
	double	zy;
	double	cx;
	double	cy;

	zx = fractol->z.x;
	zy = fractol->z.y;
	cx = fractol->c.x;
	cy = fractol->c.y;
	fractol->iter = 0;
	while ((zx * zx) + (zy * zy) < 4.0 && fractol->iter < fractol->max_iter)
	{
		tmp = zx;
		zx = (zx * zx) - (zy * zy) + cx;
		zy = 2 * tmp * zy + cy;
		fractol->iter++;
	}
}
