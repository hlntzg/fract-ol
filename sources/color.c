/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:49:08 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/05 13:16:53 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	ft_pixel(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}
