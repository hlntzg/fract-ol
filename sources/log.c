/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:53:34 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/23 15:09:35 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Logs an error message to stderr with a red color prefix based on the ANSI
 * escape codes, then resets all attributes to default. */
int	log_err(char *str, char *strerror)
{
	ft_putstr_fd("\033[0;31m", 1);
	ft_putstr_fd(strerror, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd("\033[0m", 1);
	return (1);
}

/* This function log instructions for the user in the stdout. */
int	log_guide(void)
{
	ft_putstr_fd("\nAvailable fractal sets:"
		"\n\tmandelbrot;""\n\tjulia;"
		"\n\nGuide for fract-ol usage:"
		"\n\t./fractol [fractal_set_name] or to create a specific Julia set:"
		"\n\t./fractol julia [signed_double_a] [signed_double_b]"
		"\n\nExamples for Julia sets:\n\t-0.4\t0.6\n\t0.285\t0.01\n\t0\t0.8"
		"\n\t-1.476\t0\n\t-0.12\t-0.77"
		"\n\nGeneral guide:"
		"\n\tESC to close the window and quit the program;"
		"\n\tArrow keys (right, left, down and up) to move the view;"
		"\n\tScroll to zoom in and out according to the mouse position;"
		"\n\tPress the + or - key on the keypad to increase or decrease the "
		"number of iterations and add more or less detail to the fractal image;"
		"\n\nMore options for Julia:""\n\tCONTROL_LEFT to increase the real part "
		"of the complex constant, and CONTROL_LEFT + SHIFT_LEFT to decrease it;"
		"\n\tCONTROL_RIGHT to increase the imaginary part of the complex "
		"constant, and CONTROL_RIGHT + SHIFT_RIGHT to decrease it;"
		"\n\n", 1);
	return (1);
}
