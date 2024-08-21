/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_initialization.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:45:39 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/21 14:54:03 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* This function initializes the fractal environment and the MLX42 library and
 * displays the image in the window. Logs the guide for user instructions. */
void	init_fractol(t_fractol *fractol, char **argv)
{
	fractol->set = argv[1];
	fractol->mlx = mlx_init(WIDTH, HEIGHT, fractol->set, false);
	if (!(fractol->mlx))
		exit (EXIT_FAILURE);
	fractol->image = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!(fractol->image))
	{
		mlx_delete_image(fractol->mlx, fractol->image);
		mlx_close_window(fractol->mlx);
		exit (EXIT_FAILURE);
	}
	mlx_image_to_window(fractol->mlx, fractol->image, 0, 0);
	log_guide();
	if (ft_strequ(argv[1], "julia"))
		init_julia(fractol, argv);
	fractol->max_iter = 50;
	fractol->move_factor = 0.025;
	init_view(fractol);
	init_colors(fractol);
}

/* This specific function sets the real and imaginary ranges for different
 * fractal types to initialize the view. */
void	init_view(t_fractol *fractol)
{
	if (ft_strequ(fractol->set, "julia"))
	{
		fractol->real.min = -1.7;
		fractol->real.max = 1.7;
		fractol->imag.min = -1.7;
		fractol->imag.max = 1.7;
	}
	else if (ft_strequ(fractol->set, "mandelbrot"))
	{
		fractol->real.min = -2.0;
		fractol->real.max = 0.6;
		fractol->imag.min = -1.2;
		fractol->imag.max = 1.2;
	}
}

/* This function set low values to initial color parameters, resulting 
 * in a grayscale appearance for the first rendered image. */
void	init_colors(t_fractol *fractol)
{
	fractol->k_red = 0.16;
	fractol->k_green = 0.08;
	fractol->k_blue = 0.04;
}

/* This function initializes the complex constant for the julia fractal
 * set based on parameters from the user or default values. */
void	init_julia(t_fractol *fractol, char **argv)
{
	if (!argv[2])
	{
		fractol->julia_c.x = -0.745429;
		fractol->julia_c.y = 0.05;
	}
	else if (!argv[3])
	{
		fractol->julia_c.x = ft_atof(argv[2]);
		fractol->julia_c.y = 0.0;
	}
	else
	{
		fractol->julia_c.x = ft_atof(argv[2]);
		fractol->julia_c.y = ft_atof(argv[3]);
	}
}
