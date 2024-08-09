/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:10:49 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/09 11:46:05 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_keyhook_general(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fractol->mlx);
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
		log_guide();
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if (mlx_is_key_down(fractol->mlx, MLX_KEY_LEFT_SHIFT))
			init_colors(fractol);
		init_view(fractol);
	}
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_KP_ADD))
		fractol->max_iter *= 2;
	if (mlx_is_key_down(fractol->mlx, MLX_KEY_KP_SUBTRACT))
		fractol->max_iter *= 0.5;
}

void	ft_keyhook_colors(void *param)
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
