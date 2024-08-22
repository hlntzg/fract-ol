/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:47:42 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/22 09:53:13 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* This function validates the extra command-line arguments provided for julia
 *  set and logs error messages and return 0 if it is invalid arguments. */
int	is_valid_extra_args(int argc, char **argv)
{
	if (argc == 3 && ft_strequ(argv[1], "julia"))
	{
		if (!is_signed_decimal(argv[2]))
			log_err("Invalid argument for [unsigned_double_a], "
				"follow the instructions.", strerror(22));
		return (is_signed_decimal(argv[2]));
	}
	else if (argc == 4 && ft_strequ(argv[1], "julia"))
	{
		if (!is_signed_decimal(argv[2]) || !is_signed_decimal(argv[3]))
			log_err("Invalid argument for [unsigned_double_a], "
				"and/or [unsigned_double_b], "
				"follow the instructions.", strerror(22));
		return (is_signed_decimal(argv[2]) && is_signed_decimal(argv[3]));
	}
	log_err("Invalid extra arguments, follow the instructions.", strerror(5));
	return (0);
}

/* This function checks the validity of argument according to available fractal
 * setsa and return error message and 0, or return 1 if arguments is valid. */
int	is_valid_arg(int argc, char **argv)
{
	int	i;

	if (argc == 2)
	{
		i = (ft_strequ(argv[1], "mandelbrot") || ft_strequ(argv[1], "julia"));
		if (i == 0)
			log_err("Invalid argument for [fractal_set_name], "
				"follow the instructions.", strerror(22));
		return (i);
	}
	else
		return (is_valid_extra_args(argc, argv));
}

int	is_signed_decimal(const char *str)
{
	int	decimal_point;
	int	digits;

	decimal_point = 0;
	digits = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str == '.')
		{
			if (decimal_point)
				return (0);
			decimal_point = 1;
		}
		else if (ft_isdigit((unsigned char) *str))
			digits = 1;
		else
			return (0);
		str++;
	}
	return (digits);
}
