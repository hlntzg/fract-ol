/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:47:42 by hutzig            #+#    #+#             */
/*   Updated: 2024/07/31 13:48:11 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_valid_arg(char *arg)
{
	int	i;

	i = ft_strequ(arg, "mandelbrot") || ft_strequ(arg, "julia");
//	if (i == 0)
//		log_err("Invalid argument for fractal type", strerror(5));
	return (i);
}
