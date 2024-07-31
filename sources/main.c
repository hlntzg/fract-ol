/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:17:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/07/31 15:21:30 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_fractol_window(char *arg, t_fractol *fractol)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	
	mlx = mlx_init(WIDTH, HEIGHT, arg, true);
	if (!mlx)
		exit (EXIT_FAILURE);
	(*fractol).mlx = mlx; // fractol->mlx = mlx;
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
	{
		mlx_close_window(mlx);
		exit (EXIT_FAILURE);
	}
	(*fractol).image = image; // fractol->image = image;
	(*fractol).set = arg; // fractol->set = arg;
}

static void	fractol_management(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;

	if (keydata.key == MLX_KEY_G && keydata.action == MLX_PRESS)
		log_guide();
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fractol->mlx);
}
/*
static void	init_hook(t_fractol *fractol)
{
	mlx_key_hook(fractol->mlx, &fractol_management, fractol);
}
*/

static	void	ft_fractal_set(void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	if (ft_strequ(fractol->set, "julia"))
	{
		printf("- julia -");
	}
	if (ft_strequ(fractol->set, "mandelbrot"))
	{
		printf("- mandelbrot -");
	}
}

int	main(int argc, char **argv)
{
	t_fractol fractol;

	if (argc < 2 || !is_valid_arg(argv[1]))
		return (log_guide());
	if (is_valid_arg(argv[1]))
	{
		init_fractol_window(argv[1], &fractol);
		//init_hook(&fractol);
		mlx_key_hook(fractol.mlx, fractol_management, &fractol); // check if it needs to be after the loop_hook! 
		mlx_loop_hook(fractol.mlx, ft_fractal_set, &fractol);
		mlx_loop(fractol.mlx);
		mlx_terminate(fractol.mlx);
	}
	return (0);
}
