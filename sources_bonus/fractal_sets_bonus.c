/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_sets_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:58:38 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/21 12:08:28 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

/* This function maps the pixel coordinates to complex number (r real part, i
 * imaginary part), by calculating the size of each pixel in the complex plane 
 * and translating the coordinates on the screen(x, y) to complex number. */
void	pixel_to_complex(double *r, double *i, t_fractol *fractol)
{
	double	pixel_width;
	double	pixel_height;

	pixel_width = (fractol->real.max - fractol->real.min) / WIDTH;
	pixel_height = (fractol->imag.max - fractol->imag.min) / HEIGHT;
	*r = fractol->real.min + (double) fractol->pixel_x * pixel_width;
	*i = fractol->imag.max - (double) fractol->pixel_y * pixel_height;
}

/* This function initializes the complex number z to (0, 0), converts the
 * pixel coordinates to a complex number c, and then calculates the escape
 * time and computes a color to each pixel on mandelbrot set. */
void	mandelbrot(uint32_t x, uint32_t y, t_fractol *fractol)
{
	fractol->z.x = 0.0;
	fractol->z.y = 0.0;
	fractol->pixel_x = x;
	fractol->pixel_y = y;
	pixel_to_complex(&(fractol->c.x), &(fractol->c.y), fractol);
	compute_escape_time(fractol);
	compute_color(fractol);
}

/* This function uses a fixed complex number c, converts the pixel coordinates
 * to a complex number z, and then calculates the escape time and correspondent
 * color to each pixel on julia set. */
void	julia(uint32_t x, uint32_t y, t_fractol *fractol)
{
	fractol->c.x = fractol->julia_c.x;
	fractol->c.y = fractol->julia_c.y;
	fractol->pixel_x = x;
	fractol->pixel_y = y;
	pixel_to_complex(&(fractol->z.x), &(fractol->z.y), fractol);
	compute_escape_time(fractol);
	compute_color(fractol);
}

/* This function initializes the complex number z to (0, 0), converts the
 * pixel coordinates to a complex number c, and then calculates the escape
 * time using the burning ship equation and determines the color. */
void	burning_ship(uint32_t x, uint32_t y, t_fractol *fractol)
{
	fractol->z.x = 0.0;
	fractol->z.y = 0.0;
	fractol->pixel_x = x;
	fractol->pixel_y = y;
	pixel_to_complex(&(fractol->c.x), &(fractol->c.y), fractol);
	compute_escape_time_burning(fractol);
	compute_color(fractol);
}
