/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:53:34 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/08 14:56:03 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int	log_guide(void)
{
	ft_putstr_fd("\nThe available fractal sets:"
		"\n\tmandelbrot;""\n\tjulia;""\n\tburning;"
		"\n\nGuide for fract-ol usage:"
		"\n\t./fractol [fractal_set_name] or to create specific Julia set:"
		"\n\t./fractol [fractal_set_name] [usigned_double_a] [usigned_double_b]"
		"\n\nExamples for Julia sets:\n\t-0.4\t0.6\n\t0.285\t0.01\n\t0\t0.8"
		"\n\t-1.476\t0\n\t-0.12\t-0.77"
		"\n\nMore options:"
		"\n\tTAB to display this guide;"
		"\n\tESC to close the window and quit the program;"
		"\n\tSPACE to resize the fractal and SHIFT + SPACE to reset colors"
		"\n\tR and SHIFT + R to increase or decrease the red color channel"
		"\n\tG and SHIFT + G to increase or decrease the green color channel"
		"\n\tB and SHIFT + B to increase or decrease the blue color channel"
		"\n\tArrow keys (right, left, down and up) to move the view;"
		"\n\tScroll to zoom in and out according to the mouse position;"
		"\n\tPress the + or - key on the keypad to increase or decrease the "
		"number of iterations and add more or less detail to the fractal image;"
		"\n\n", 1);
	return (1);
}
