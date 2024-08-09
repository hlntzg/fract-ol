/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_sets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:58:38 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/09 10:07:51 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* this function maps the pixel coordinates to complex number (r real part,
i imaginary part), by calculating the size of each pixel in the complex plane 
and translating the coordinates(x, y) to complex number */
void	pixel_to_complex(double *r, double *i, t_fractol *fractol)
{
	double	pixel_width;
	double	pixel_height;

	pixel_width = (fractol->real.max - fractol->real.min) / WIDTH;
	pixel_height = (fractol->imag.max - fractol->imag.min) / HEIGHT;
	*r = fractol->real.min + (double) fractol->pixel_x * pixel_width;
	*i = fractol->imag.max - (double) fractol->pixel_y * pixel_height;
}

void	mandelbrot(uint32_t x, uint32_t y, t_fractol *fractol)
{
	fractol->zx = 0.0;
	fractol->zy = 0.0;
	fractol->pixel_x = x;
	fractol->pixel_y = y;
	pixel_to_complex(&(fractol->cx), &(fractol->cy), fractol);
	compute_escape_time(fractol);
	compute_color(fractol);
}

void	julia(uint32_t x, uint32_t y, t_fractol *fractol)
{
	fractol->cx = fractol->julia_c.x;
	fractol->cy = fractol->julia_c.y;
	fractol->pixel_x = x;
	fractol->pixel_y = y;
	pixel_to_complex(&(fractol->zx), &(fractol->zy), fractol);
	compute_escape_time(fractol);
	compute_color(fractol);
}

void	burning_ship(uint32_t x, uint32_t y, t_fractol *fractol)
{
	fractol->zx = 0.0;
	fractol->zy = 0.0;
	fractol->pixel_x = x;
	fractol->pixel_y = y;
	pixel_to_complex(&(fractol->cx), &(fractol->cy), fractol);
	compute_escape_time_burning(fractol);
	compute_color(fractol);
}
