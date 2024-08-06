/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:53:34 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/06 12:19:53 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int	log_guide(void)
{
	ft_putstr_fd("\nGuide for fract-ol usage:"
	"\n\t./fractol [fractal_set_name]"
	"\n\nAvailable fractal sets:"
	"\n\tmandelbrot;"
	"\n\tjulia;"
	"\n\tburning;"
	"\n\nMore options:"
	"\n\tTAB to display this guide;"
	"\n\tESC to close the window and quit the program;"
	"\n\tUse arrow keys (right, left, down and up) to move the current view;"
	"\n\tPress the + or - key on the keypad to increase or decrease the "
	"number of iterations and add more or less detail to the fractal image;"
	"\n\n", 1);
	return (1);
}
