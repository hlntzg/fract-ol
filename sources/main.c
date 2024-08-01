/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:17:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/01 17:41:48 by hutzig           ###   ########.fr       */
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

/* x is the z_real and y is the z_img */
static	int	compute_escape_time(double x, double y, double c_real, double c_img)
{
	double	tmp;
	int	i;

	i = 0;
	while ((x * x) + (y * y) < 4.0 && i < MAX_ITER)
	{
		tmp = x;
		x = (x * x) - (y * y) + c_real;
		y = 2 * tmp * y + c_img;
		i++;
	}
	return (i);
}

static int	mandelbrot(unit32_t pixel_x, unit32_t pixel_y, fractol *fractol)
{
	
	compute_escape_time();
	if (escape_time == MAX_ITER)
		return (); //function to color points within the set (black?)
	else
		return (); //function to color the pixel (gradient coloring? t = escape_time / MAX_ITER?)
}

static int	julia(unit32_t pixel_x, unit32_t pixel_y, fractol *fractol)
{

}

/* this function loops through each pixel on the screen, and use the specific 
fractal set function to map the pixel to a point in the complex plane and
determine its color based on the number of iterations before escape */
static	void	fractal_visualization(void *param)
{
	t_fractol	*fractol;
	unit32_t	x;
	unit32_t	y;
	int		pixel_color;

	fractol = (t_fractol *)param;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (ft_strequ(fractol->set, "julia"))
				pixel_color = julia(x, y, fractol);
			if (ft_strequ(fractol->set, "mandelbrot"))
				pixel_color = mandelbrot(x, y, fractol);
			mlx_put_pixel(fractol->image, x, y, pixel_color);
			y++;
		}
		x++;
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
		mlx_loop_hook(fractol.mlx, fractal_visualization, &fractol);
		mlx_loop(fractol.mlx);
		mlx_terminate(fractol.mlx);
	}
	return (0);
}
