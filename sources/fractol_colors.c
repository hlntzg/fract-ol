/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:49:08 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/09 10:57:11 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	compute_color(t_fractol *fractol)
{
	if (fractol->iter == fractol->max_iter)
	{
		fractol->get.color = ft_pixel(0, 0, 0, 255);
		return ;
	}
	fractol->get.red = (sin(fractol->k_red * fractol->iter) * 255);
	fractol->get.green = (sin(fractol->k_green * fractol->iter) * 255);
	fractol->get.blue = (sin(fractol->k_blue * fractol->iter) * 255);
	fractol->get.alpha = 255;
	fractol->get.color = ft_pixel(fractol->get.red, fractol->get.green, fractol->get.blue, fractol->get.alpha);
}

uint32_t	ft_pixel(uint32_t red, uint32_t green, uint32_t blue, uint32_t a)
{
	return (red << 24 | green << 16 | blue << 8 | a);
}
