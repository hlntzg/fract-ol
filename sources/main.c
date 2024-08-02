/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:17:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/02 12:43:19 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_fractol_window(int argc, char **argv, t_fractol *fractol)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	
	mlx = mlx_init(WIDTH, HEIGHT, argv[1], true);
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
	(*fractol).set = argv[1]; // fractol->set = argv[1];
	if (argc > 2)
		init_extra_parameters(*argv);
	
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

static	int	compute_escape_time(double zx, double zy, double cx, double cy)
{
	double	tmp;
	int	i;

	i = 0;
	while ((zx * zx) + (zy * zy) < 4.0 && i < MAX_ITER)
	{
		tmp = zx;
		zx = (zx * zx) - (zy * zy) + cx;
		zy = 2 * tmp * zy + cy;
		i++;
	}
	return (i);
}

static void	pixel_to_complex(uint32_t x, uint32_t y, double *real, double *imag);
{
	double	real_min;
	double	real_max;
	double	imag_min;
	double	imag_max;

	real_min = -2.0;
	real_max = 2.0;
	imag_min = -2.0;
	imag_max = 2.0;
	*real = real_min + (double) x * (real_max - real_min / WIDTH);
	*imag = imag_max - (double) y * (imag_max - imag_min / HEIGHT);
}

static int	mandelbrot(uint32_t pixel_x, uint32_t pixel_y, fractol *fractol)
{
	t_fractal	number;
	int		i;
	
	number.zx = 0.0;
	number.zy = 0.0;
	pixel_to_complex(pixel_x, pixel_y, &(number.zx), &(number.zy); 
	//number->cx = pixel_to_complex(pixel_x, 0);
	//number->cy = pixel_to_complex(0, pixel_y);
	i = compute_escape_time(number.zx, number.zy, number.cx, number.cy);
	if (i == MAX_ITER)
		return (); //function to color points within the set (black?)
	else
		return (); //function to color the pixel (gradient coloring? t = escape_time / MAX_ITER?)
}

static int	julia(uint32_t pixel_x, uint32_t pixel_y, fractol *fractol)
{
	t_fractal	number;
	int		i;

	pixel_to_complex(pixel_x, pixel_y, &(number.zx), &(number.zy);
	//number->zx = pixel_to_complex(pixel_x, 0, fractol);
	//number->zy = pixel_to_complex(0, pixel_y, fractol);
	number.cx = -0.745429;//fractol->julia_cx:
	number.cy = 0.05; //fractol->julia_cy;
	i = compute_escape_time(number.zx, number.zy, number.cx, number.cy);
	if (i == MAX_ITER)
		return (); //function to color points within the set (black?)
	else
		return (); //
}

/* this function loops through each pixel on the screen, and use the specific 
fractal set function to map the pixel to a point in the complex plane and
determine its color based on the number of iterations before escape */
static	void	fractal_visualization(void *param)
{
	t_fractol	*fractol;
	uint32_t	x;
	uint32_t	y;
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
		init_fractol_window(argc, *argv, &fractol);
		//init_hook(&fractol);
		mlx_key_hook(fractol.mlx, fractol_management, &fractol); // check if it needs to be after the loop_hook! 
		mlx_loop_hook(fractol.mlx, fractal_visualization, &fractol);
		mlx_loop(fractol.mlx);
		mlx_terminate(fractol.mlx);
	}
	return (0);
}
