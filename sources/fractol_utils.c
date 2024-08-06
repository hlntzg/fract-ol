/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:47:42 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/06 11:46:34 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_valid_arg(const char *arg)
{
	int	i;

	i = ft_strequ(arg, "mandelbrot") || ft_strequ(arg, "julia") || ft_strequ(arg, "burning");
//	if (i == 0)
//		log_err("Invalid argument for fractal type", strerror(5));
// IS IT POSSIBLE TO COMBINE AND CHECK FOR ARGV[2] AND ARGV[3] IF ITS JULIA?	
	return (i);
}

int	is_signed_decimal(const char *str)
{
	int	decimal_point;
	int	digit_before_point;
	int	digit_after_point;

	decimal_point = 0;
	digit_before_point = 0;
	digit_after_point = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str == '.')
		{
			if (decimal_point == 1)
				return (0);
			decimal_point = 1;
		}
		else if (ft_isdigit(*str))
		{
			if (decimal_point == 1)
				digit_after_point = 1;
			else
				digit_before_point = 1;
		}
		else
			return (0);
		str++;
	}
	return ((digit_before_point || decimal_point) && (digit_before_point || digit_after_point));
}
