/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:04:31 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/08 14:07:23 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* this function loops through each pixel on the screen, and use the specific 
fractal set function to map the pixel to a point in the complex plane and
determine its color based on the number of iterations before escape */
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
			if (ft_strequ(fractol->set, "burning"))
				burning_ship(x, y, fractol);
			mlx_put_pixel(fractol->image, x, y, fractol->pixel_color);
			y++;
		}
		x++;
	}
}

void	compute_escape_time_burning(t_fractol *fractol)
{
	double	tmp;
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	
	zx = fractol->zx;
	zy = fractol->zy;
	cx = fractol->cx;
	cy = fractol->cy;
	fractol->iter = 0;
	while ((zx * zx) + (zy * zy) < 4.0 && fractol->iter < fractol->max_iter)
	{
		tmp = zx;
		zx = (zx * zx) - (zy * zy) - cx;
		zy = 2 * ft_abs(tmp * zy) - cy;
		fractol->iter++;
	}
}

void	compute_escape_time(t_fractol *fractol)
{
	double	tmp;
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	
	zx = fractol->zx;
	zy = fractol->zy;
	cx = fractol->cx;
	cy = fractol->cy;
	fractol->iter = 0;
	while ((zx * zx) + (zy * zy) < 4.0 && fractol->iter < fractol->max_iter)
	{
		tmp = zx;
		zx = (zx * zx) - (zy * zy) + cx;
		zy = 2 * tmp * zy + cy;
		fractol->iter++;
	}
}
