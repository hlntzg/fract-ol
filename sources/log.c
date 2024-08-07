/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:53:34 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/07 18:23:39 by hutzig           ###   ########.fr       */
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
		"\n\tR and shift + R to increase or decrease the red color channel"
		"\n\tG and shift + G to increase or decrease the green color channel"
		"\n\tB and shift + B to increase or decrease the blue color channel"
		"\n\tUse the arrow keys (right, left, down and up) to move the view;"
		"\n\tUse the scroll to zoom in and out according to the mouse position;"
		"\n\tPress the + or - key on the keypad to increase or decrease the "
		"number of iterations and add more or less detail to the fractal image;"
		"\n\n", 1);
	return (1);
}
