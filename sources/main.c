/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:17:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/07 18:16:11 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_struct(t_fractol *fractol)
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
static void	init_fractol(t_fractol *fractol)
{
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
	fractol->max_iter = 50;
	fractol->move_factor = 0.025;
	fractol->k_red = 0.01;
	fractol->k_green = 0.01;
	fractol->k_blue = 0.01;
	init_struct(fractol);
}

static void	ft_keyhook_general(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fractol->mlx);
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
		log_guide();
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		init_struct(fractol);
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_KP_ADD))
		fractol->max_iter *= 2;
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_KP_SUBTRACT))
		fractol->max_iter *= 0.5;
}
	
static void	ft_keyhook_colors(void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_R))
	{
		if (mlx_is_key_down(fractol->mlx, MLX_KEY_LEFT_SHIFT))
			fractol->k_red *= 0.5;
		else
			fractol->k_red *= 2;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_G))
	{
		if (mlx_is_key_down(fractol->mlx, MLX_KEY_LEFT_SHIFT))
			fractol->k_green *= 0.5;
		else
			fractol->k_green *= 2;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_B))
	{
		if (mlx_is_key_down(fractol->mlx, MLX_KEY_LEFT_SHIFT))
			fractol->k_blue *= 0.5; 
		else
			fractol->k_blue *= 2;
	}
}

static void	ft_keyhook_arrowkeys(void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	fractol->real_delta = fractol->real_max - fractol->real_min;
	fractol->imag_delta = fractol->imag_max - fractol->imag_min;
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_RIGHT))
	{
		fractol->real_min += fractol->real_delta * fractol->move_factor;
		fractol->real_max += fractol->real_delta * fractol->move_factor;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_LEFT))
	{
		fractol->real_min -= fractol->real_delta * fractol->move_factor;
		fractol->real_max -= fractol->real_delta * fractol->move_factor;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_DOWN))
	{
		fractol->imag_min -= fractol->imag_delta * fractol->move_factor;
		fractol->imag_max -= fractol->imag_delta * fractol->move_factor;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_UP))
	{
		fractol->imag_min += fractol->imag_delta * fractol->move_factor;
		fractol->imag_max += fractol->imag_delta * fractol->move_factor;
	}
}

static	void	compute_escape_time_burning(t_fractol *fractol)
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


static	void	compute_escape_time(t_fractol *fractol)
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

static void	compute_color(t_fractol *fractol)
{
	t_color	c;

	if (fractol->iter == fractol->max_iter)
	{
		fractol->pixel_color = ft_pixel(0, 0, 0, 255);
		return ;
	}
	c.red = (sin(fractol->k_red * fractol->iter) * 255);
	c.green = (sin(fractol->k_green * fractol->iter) * 255);
	c.blue = (sin(fractol->k_blue * fractol->iter) * 255);
	c.alpha = 255;
	fractol->pixel_color = ft_pixel(c.red, c.green, c.blue, c.alpha);
}
	
/* this function maps the pixel coordinates to complex number (r real part,
i imaginary part), by calculating the size of each pixel in the complex plane 
and translating the coordinates(x, y) to complex number */
void	pixel_to_complex(uint32_t x, uint32_t y, double *r, double *i, t_fractol *fractol)
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
	fractol->zx = 0.0;
	fractol->zy = 0.0;
	pixel_to_complex(pixel_x, pixel_y, &(fractol->cx), &(fractol->cy), fractol);
	compute_escape_time(fractol);
	compute_color(fractol);
}

static void	julia(uint32_t pixel_x, uint32_t pixel_y, t_fractol *fractol)
{
	fractol->cx = fractol->julia_cx;
	fractol->cy = fractol->julia_cy;
	pixel_to_complex(pixel_x, pixel_y, &(fractol->zx), &(fractol->zy), fractol);
	compute_escape_time(fractol);
	compute_color(fractol);
}

static void	burning_ship(uint32_t pixel_x, uint32_t pixel_y, t_fractol *fractol)
{
	fractol->zx = 0.0;
	fractol->zy = 0.0;
	pixel_to_complex(pixel_x, pixel_y, &(fractol->cx), &(fractol->cy), fractol);
	compute_escape_time_burning(fractol);
	compute_color(fractol);
}

/* this function loops through each pixel on the screen, and use the specific 
fractal set function to map the pixel to a point in the complex plane and
determine its color based on the number of iterations before escape */
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
			if (ft_strequ(fractol->set, "burning"))
				burning_ship(x, y, fractol);
			mlx_put_pixel(fractol->image, x, y, fractol->pixel_color);
			y++;
		}
		x++;
	}
}

static void	init_parameters(char **argv, t_fractol *fractol)
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

static void	ft_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractol;
	double		mouse_real;
	double		mouse_imag;

	(void) xdelta;
	fractol = (t_fractol *)param;
	fractol->mouse_x = 0;
	fractol->mouse_y = 0;
	mlx_get_mouse_pos(fractol->mlx, &(fractol->mouse_x), &(fractol->mouse_y));
	pixel_to_complex(fractol->mouse_x, fractol->mouse_y, &mouse_real, &mouse_imag, fractol);
	if (ydelta > 0)
		fractol->zoom = 0.9;
	else if (ydelta < 0)
		fractol->zoom = 1.1;
	fractol->real_min = mouse_real + (fractol->real_min - mouse_real) * fractol->zoom;
	fractol->real_max = mouse_real + (fractol->real_max - mouse_real) * fractol->zoom;
	fractol->imag_min = mouse_imag + (fractol->imag_min - mouse_imag) * fractol->zoom;
	fractol->imag_max = mouse_imag + (fractol->imag_max - mouse_imag) * fractol->zoom;
}

int	main(int argc, char **argv)
{
	t_fractol fractol;

	if (argc < 2 || !is_valid_arg(argv[1]))
		return (log_guide());
	init_parameters(argv, &fractol);
	init_fractol(&fractol);
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
