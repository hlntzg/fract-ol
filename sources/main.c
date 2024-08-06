/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:17:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/06 10:40:28 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_fractol(char **argv, t_fractol *fractol)
{
	fractol->mlx = mlx_init(WIDTH, HEIGHT, argv[1], false);
	if (!(fractol->mlx))
		exit (EXIT_FAILURE);
	fractol->image = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!(fractol->image) || mlx_image_to_window(fractol->mlx, fractol->image, 0, 0) < 0)
	{
		mlx_close_window(fractol->mlx);
		exit (EXIT_FAILURE);
	}
	fractol->set = argv[1];
	fractol->move_factor = 0.025;
	if (ft_strequ(argv[1], "julia"))
	{
		fractol->real_min = -1.7;
		fractol->real_max = 1.7;
		fractol->imag_min = -1.7;
		fractol->imag_max = 1.7;
	}
	else if (ft_strequ(argv[1], "mandelbrot"))
	{
		fractol->real_min = -1.7;
		fractol->real_max = 0.7;
		fractol->imag_min = -1.2;
		fractol->imag_max = 1.2;
	}
}

static void	ft_keyhook_general(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fractol->mlx);
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_G))
		log_guide();
}

static void	ft_keyhook_arrowkeys(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;
	double		delta_x;
	double		delta_y;

	(void) keydata; //review this, should, in main, send the & of the function?
	fractol = (t_fractol *)param;
	delta_x = (fractol->real_max - fractol->real_min) * fractol->move_factor;
	delta_y = (fractol->imag_max - fractol->imag_min) * fractol->move_factor;
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_RIGHT))
	{
		fractol->real_min += delta_x;
		fractol->real_max += delta_x;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_LEFT))
	{
		fractol->real_min -= delta_x;
		fractol->real_max -= delta_x;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_DOWN))
	{
		fractol->imag_min -= delta_y;
		fractol->imag_max -= delta_y;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_UP))
	{
		fractol->imag_min += delta_y;
		fractol->imag_max += delta_y;
	}
}

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

static void	compute_color(t_fractol *fractol, int i)
{
	t_color	c;

	if (i == MAX_ITER)
	{
		fractol->pixel_color = ft_pixel(0, 0, 0, 255);
		return ;
	}
	c.red = (uint32_t)(sin(0.05 * i) * 127.5 + 127.5); // Map sine wave to [0, 255]
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

	pixel_width = (fractol->real_max - fractol->real_min) / WIDTH;
	pixel_height = (fractol->imag_max - fractol->imag_min) / HEIGHT;
	*r = fractol->real_min + (double) x * pixel_width;
	*i = fractol->imag_max - (double) y * pixel_height;
}

static void	mandelbrot(uint32_t pixel_x, uint32_t pixel_y, t_fractol *fractol)
{
	int		i;

	fractol->zx = 0.0;
	fractol->zy = 0.0;
	pixel_to_complex(pixel_x, pixel_y, &(fractol->cx), &(fractol->cy), fractol);
	i = compute_escape_time(fractol->zx, fractol->zy, fractol->cx, fractol->cy);
	compute_color(fractol, i);
}

static void	julia(uint32_t pixel_x, uint32_t pixel_y, t_fractol *fractol)
{
	int		i;

	fractol->cx = fractol->julia_cx;
	fractol->cy = fractol->julia_cy;
	pixel_to_complex(pixel_x, pixel_y, &(fractol->zx), &(fractol->zy), fractol);
	i = compute_escape_time(fractol->zx, fractol->zy, fractol->cx, fractol->cy);
	compute_color(fractol, i);
}

static void	burning_ship(uint32_t pixel_x, uint32_t pixel_y, t_fractol *fractol)
{
	int	i;

	

}

/* this function loops through each pixel on the screen, and use the specific 
fractal set function to map the pixel to a point in the complex plane and
determine its color based on the number of iterations before escape */
//static	void	fractal_visualization(void *param)
static	void	ft_fractol_render(void *param)
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

static void	init_parameters(char **argv, t_fractol *fractol)
{
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

static void	ft_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	fractol->mouse_x = 0;
	fractol->mouse_y = 0;
	mlx_get_mouse_pos(fractol->mlx, &fractol->mouse_x, &fractol->mouse_y);	




	
}

int	main(int argc, char **argv)
{
	t_fractol fractol;

	if (argc < 2 || !is_valid_arg(argv[1]))
		return (log_guide());
	init_fractol(argv, &fractol);
	init_parameters(argv, &fractol);
	mlx_key_hook(fractol.mlx, ft_keyhook_general, &fractol);
	mlx_key_hook(fractol.mlx, ft_keyhook_arrowkeys, &fractol);
	mlx_loop_hook(fractol.mlx, ft_fractol_render, &fractol);
	mlx_scroll_hook(fractol.mlx, ft_scrollhook, &fractol);
	mlx_loop(fractol.mlx);
	mlx_terminate(fractol.mlx);

	return (0);
}
