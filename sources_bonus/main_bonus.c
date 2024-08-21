/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:17:41 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/21 12:10:13 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc < 2 || !is_valid_arg(argc, argv))
		return (log_guide());
	init_fractol(&fractol, argv);
	mlx_key_hook(fractol.mlx, ft_keyhook_general, &fractol);
	mlx_loop_hook(fractol.mlx, ft_keyhook_colors, &fractol);
	mlx_loop_hook(fractol.mlx, ft_keyhook_julia, &fractol);
	mlx_loop_hook(fractol.mlx, ft_keyhook_arrowkeys, &fractol);
	mlx_loop_hook(fractol.mlx, ft_fractol_render, &fractol);
	mlx_scroll_hook(fractol.mlx, ft_scrollhook, &fractol);
	mlx_loop(fractol.mlx);
	mlx_terminate(fractol.mlx);
	return (0);
}
