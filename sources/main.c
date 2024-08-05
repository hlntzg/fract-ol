/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:17:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/05 13:06:10 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_fractol_window(char **argv, t_fractol *fractol)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	
	mlx = mlx_init(WIDTH, HEIGHT, argv[1], true);
	if (!mlx)
		exit (EXIT_FAILURE);
	fractol->mlx = mlx;
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
	{
		mlx_close_window(mlx);
		exit (EXIT_FAILURE);
	}
	fractol->image = image;
	fractol->set = argv[1];
	fractol->real_min = -2.0;
	fractol->real_max = 2.0;
	fractol->imag_min = -2.0;
	fractol->imag_max = 2.0;
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

static void	compute_color_julia(t_fractol *fractol, int i)
{
	//t_color	c;

	if (i == MAX_ITER)
	{
		fractol->pixel_color = ft_pixel(0, 0, 0, 255);
		return ;
	}
/*	else
	{
		if (color_range == )

		else if ()

		else if ()

		fractol->pixel_color = ft_pixel(c.red, c.green, c.blue, c.alpha);
	}*/
}

static void	compute_color_mandelbrot(t_fractol *fractol, int i)
{
	t_color	c;

	if (i == MAX_ITER)
	{
		fractol->pixel_color = ft_pixel(0, 0, 0, 255);
		return ;
	}
	c.red = (uint32_t)(sin(0.02 * i) * 127.5 + 127.5); // Map sine wave to [0, 255]
	c.green = (uint32_t)(sin(0.0 * i) * 127.5 + 127.5); // 0
	c.blue = (uint32_t)(sin(0.0 * i) * 127.5 + 127.5); // 0
	c.alpha = 255;
	fractol->pixel_color = ft_pixel(c.red, c.green, c.blue, c.alpha);
}
	
/* this function maps the pixel coordinates to complex number (r real part,
i imaginary part), by calculating the size of each pixel in the complex plane 
and translating the coordinates(x, y) to complex number */
static void	pixel_to_complex(uint32_t x, uint32_t y, double *r, double *i, t_fractol *fractol)
{
	double	pixel_width;
	double	pixel_height;

//	real_min = -2.0;
//	real_max = 2.0;
//	imag_min = -2.0;
//	imag_max = 2.0;
	pixel_width = (fractol->real_max - fractol->real_min) / WIDTH;
	pixel_height = (fractol->imag_max - fractol->imag_min) / HEIGHT;
	*r = fractol->real_min + (double) x * pixel_width;
	*i = fractol->imag_max - (double) y * pixel_height;
//	*r = real_min + (double) x * (real_max - real_min / WIDTH);
//	*i = imag_max - (double) y * (imag_max - imag_min / HEIGHT);
}

static void	mandelbrot(uint32_t pixel_x, uint32_t pixel_y, t_fractol *fractol)
{
	t_fractal	number;
	int		i;
	
	number.zx = 0.0;
	number.zy = 0.0;
	pixel_to_complex(pixel_x, pixel_y, &(number.zx), &(number.zy), fractol);
	//number->cx = pixel_to_complex(pixel_x, 0);
	//number->cy = pixel_to_complex(0, pixel_y);
	i = compute_escape_time(number.zx, number.zy, number.cx, number.cy);
	compute_color_mandelbrot(fractol, i);
}

static void	julia(uint32_t pixel_x, uint32_t pixel_y, t_fractol *fractol)
{
	t_fractal	number;
	int		i;

	pixel_to_complex(pixel_x, pixel_y, &(number.zx), &(number.zy), fractol);
	//number->zx = pixel_to_complex(pixel_x, 0, fractol);
	//number->zy = pixel_to_complex(0, pixel_y, fractol);
	number.cx = -0.745429;//fractol->julia_cx:
	number.cy = 0.05; //fractol->julia_cy;
	i = compute_escape_time(number.zx, number.zy, number.cx, number.cy);
	printf("julia before color");
	compute_color_julia(fractol, i);
}

/* this function loops through each pixel on the screen, and use the specific 
fractal set function to map the pixel to a point in the complex plane and
determine its color based on the number of iterations before escape */
static	void	fractal_visualization(void *param)
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
			mlx_put_pixel(fractol->image, x, y, fractol->pixel_color);
			y++;
		}
		x++;
	}
}

void	init_extra_parameters(char **argv, t_fractol *fractol)
{
	if (!ft_strequ(argv[1], "julia"))
		return ;
	else
	{
		if (is_signed_decimal(argv[2]) && is_signed_decimal(argv[3]))
		{
			fractol->julia_cx = ft_atof(argv[2]);
			fractol->julia_cy = ft_atof(argv[3]);
		}
		else if (!argv[2] || !argv[3])
		{
			fractol->julia_cx = -0.745429;
			fractol->julia_cy = 0.05;
		}
//		else
	//		log_err("Invalid argument for extra parameters", strerror(5));
	}
}

int	main(int argc, char **argv)
{
	t_fractol fractol;

	if (argc < 2 || !is_valid_arg(argv[1]))
		return (log_guide());
	if (is_valid_arg(argv[1]))
	{
		init_fractol_window(&(*argv), &fractol);
		if (argc > 2)
			init_extra_parameters(&(*argv), &fractol);
		//init_hook(&fractol);
		mlx_key_hook(fractol.mlx, fractol_management, &fractol);
		mlx_loop_hook(fractol.mlx, fractal_visualization, &fractol);
		mlx_loop(fractol.mlx);
		mlx_terminate(fractol.mlx);
	}
	return (0);
}
