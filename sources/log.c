/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:53:34 by hutzig            #+#    #+#             */
/*   Updated: 2024/07/31 08:58:04 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int	log_guide(void)
{
	ft_putstr_fd("\nGuide for fract-ol usage:\n\t./fractol [fractal_set_name]"
	"\n\nAvailable fractal sets:\n\tmandelbrot\n\tjulia"
	"\n\nMore options:\n\tESC to close the window and quit the program"
	"\n\n", 1);
	return (1);
}

