/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:17:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/08 14:58:13 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_view(t_fractol *fractol)
{
	if (ft_strequ(fractol->set, "julia"))
	{
		fractol->real_min = -1.7;
		fractol->real_max = 1.7;
		fractol->imag_min = -1.7;
		fractol->imag_max = 1.7;
	}
	else if (ft_strequ(fractol->set, "mandelbrot"))
	{
		fractol->real_min = -2.0;
		fractol->real_max = 0.6;
		fractol->imag_min = -1.2;
		fractol->imag_max = 1.2;
	}
	else if (ft_strequ(fractol->set, "burning"))
	{
		fractol->real_min = -1.0;
		fractol->real_max = 2.0;
		fractol->imag_min = -1.0;
		fractol->imag_max = 2.0;
	}
}

static void	init_julia(t_fractol *fractol, char **argv)
{
	fractol->set = argv[1];
	if (!ft_strequ(argv[1], "julia"))
		return ;
	if (!argv[2] || !argv[3])
	{
		fractol->julia_cx = -0.745429;
		fractol->julia_cy = 0.05;
	}
	else if (is_signed_decimal(argv[2]) && is_signed_decimal(argv[3]))
	{
		fractol->julia_cx = ft_atof(argv[2]);
		fractol->julia_cy = ft_atof(argv[3]);
	}
//	else
//		log_err("Invalid argument for extra parameters", strerror(5));
}

void	init_colors(t_fractol *fractol)
{
	fractol->k_red = 0.01;
	fractol->k_green = 0.01;
	fractol->k_blue = 0.01;
}

static void	init_fractol(t_fractol *fractol, char **argv)
{
	fractol->set = argv[1];
	fractol->mlx = mlx_init(WIDTH, HEIGHT, fractol->set, true);
	if (!(fractol->mlx))
		exit (EXIT_FAILURE);
	fractol->image = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fractol->mlx, fractol->image, 0, 0);
	if (!(fractol->image))
	{
		mlx_close_window(fractol->mlx);
		exit (EXIT_FAILURE);
	}
	if (ft_strequ(argv[1], "julia"))
		init_julia(fractol, argv);	
	fractol->max_iter = 50;
	fractol->move_factor = 0.025;
	init_view(fractol);
	init_colors(fractol);
}


int	main(int argc, char **argv)
{
	t_fractol fractol;

	if (argc < 2 || !is_valid_arg(argv[1]))
		return (log_guide());
	init_fractol(&fractol, argv);
	mlx_key_hook(fractol.mlx, ft_keyhook_general, &fractol);
	mlx_loop_hook(fractol.mlx, ft_keyhook_colors, &fractol);
	mlx_loop_hook(fractol.mlx, ft_keyhook_arrowkeys, &fractol);
	mlx_loop_hook(fractol.mlx, ft_fractol_render, &fractol);
	mlx_scroll_hook(fractol.mlx, ft_scrollhook, &fractol);
	mlx_loop(fractol.mlx);
	mlx_terminate(fractol.mlx);
//	free(fractol.mlx);	
	return (0);
}
