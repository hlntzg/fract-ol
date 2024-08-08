/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:47:42 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/08 14:35:06 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_valid_arg(char *argv)
{
	int	i;

	i = ft_strequ(argv, "mandelbrot") || ft_strequ(argv, "julia") || ft_strequ(argv, "burning");
//	if (i == 0)
//		log_err("Invalid argument for fractal type", strerror(5));
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

double	ft_abs(double nb)
{
	if (nb < 0)
		return (-nb);
	else
		return (nb);
}
