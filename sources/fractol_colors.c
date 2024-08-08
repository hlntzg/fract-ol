/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:49:08 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/08 13:34:47 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	compute_color(t_fractol *fractol)
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
uint32_t	ft_pixel(uint32_t red, uint32_t green, uint32_t blue, uint32_t a)
{
	return (red << 24 | green << 16 | blue << 8 | a);
}
