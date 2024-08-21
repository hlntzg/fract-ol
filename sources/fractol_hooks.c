/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:10:49 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/21 15:35:17 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* General key hook function to handle closing the window, reseting the image
 * on the screen and its colors, and adjusts the max number of iterations. */
void	ft_keyhook_general(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(fractol->mlx, fractol->image);
		mlx_close_window(fractol->mlx);
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_KP_SUBTRACT)
		&& fractol->max_iter > 5)
		fractol->max_iter *= 0.9;
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_KP_ADD)
		&& fractol->max_iter < 500)
		fractol->max_iter *= 1.1;
}

/* Key hook function to modify the Julia set's constant (julia_c). */
void	ft_keyhook_julia(void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_LEFT_CONTROL))
	{
		if (mlx_is_key_down(fractol->mlx, MLX_KEY_LEFT_SHIFT))
			fractol->julia_c.x *= 0.9;
		else
			fractol->julia_c.x *= 1.1;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_RIGHT_CONTROL))
	{
		if (mlx_is_key_down(fractol->mlx, MLX_KEY_RIGHT_SHIFT))
			fractol->julia_c.y *= 0.9;
		else
			fractol->julia_c.y *= 1.1;
	}
}

/* Key hook function to move the fractal view using arrow keys.
 * Arrow keys: Adjust the view by shifting the real and imaginary ranges.
 * The view shifts by a fraction of the current view's range. */
void	ft_keyhook_arrowkeys(void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	fractol->real.delta = fractol->real.max - fractol->real.min;
	fractol->imag.delta = fractol->imag.max - fractol->imag.min;
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_RIGHT))
	{
		fractol->real.min += fractol->real.delta * fractol->move_factor;
		fractol->real.max += fractol->real.delta * fractol->move_factor;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_LEFT))
	{
		fractol->real.min -= fractol->real.delta * fractol->move_factor;
		fractol->real.max -= fractol->real.delta * fractol->move_factor;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_DOWN))
	{
		fractol->imag.min -= fractol->imag.delta * fractol->move_factor;
		fractol->imag.max -= fractol->imag.delta * fractol->move_factor;
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_UP))
	{
		fractol->imag.min += fractol->imag.delta * fractol->move_factor;
		fractol->imag.max += fractol->imag.delta * fractol->move_factor;
	}
}

/* Scroll hook function to handle zooming in and out based on the current mouse
 * position which is defined by pixel_x and pixel_y. Scroll up reduces the view
 * range (zoom in) and scroll down increases the view range (zoom out). */
void	ft_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractol;
	double		mouse_r;
	double		mouse_i;

	(void) xdelta;
	fractol = (t_fractol *)param;
	fractol->pixel_x = 0;
	fractol->pixel_y = 0;
	mlx_get_mouse_pos(fractol->mlx, &(fractol->pixel_x), &(fractol->pixel_y));
	pixel_to_complex(&mouse_r, &mouse_i, fractol);
	if (ydelta > 0)
		fractol->zoom = 0.9;
	else if (ydelta < 0)
		fractol->zoom = 1.1;
	fractol->real.min = mouse_r + (fractol->real.min - mouse_r) * fractol->zoom;
	fractol->real.max = mouse_r + (fractol->real.max - mouse_r) * fractol->zoom;
	fractol->imag.min = mouse_i + (fractol->imag.min - mouse_i) * fractol->zoom;
	fractol->imag.max = mouse_i + (fractol->imag.max - mouse_i) * fractol->zoom;
}
