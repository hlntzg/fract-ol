/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:25:11 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/07 18:21:02 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // perror
# include <string.h> // strerror
# include <math.h>

// resolution
# define WIDTH 1500
# define HEIGHT 1500
/*
typedef struct 	s_juliette
{
	double	x;
	double	y;
}	t_juliette;
*/
typedef struct s_fractol
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	char		*set;
	uint32_t	max_iter;
	uint32_t	iter;
	double		julia_cx;
	double		julia_cy;
	double		real_min;
	double		real_max;
	double		imag_min;
	double		imag_max;
	double		real_delta;
	double		imag_delta;
	double		move_factor;
	double		zoom;
	int32_t		mouse_x;
	int32_t		mouse_y;
	uint32_t	pixel_color;
	double		zx;
	double		zy;
	double		cx;
	double		cy;
	double		k_red;
	double		k_green;
	double		k_blue;

} t_fractol;

typedef struct	s_color
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	alpha;
} t_color;

// functions
int	log_guide(void);
int	is_valid_arg(const char *arg);
int	is_signed_decimal(const char *str);
uint32_t	ft_pixel(uint32_t red, uint32_t green, uint32_t blue, uint32_t a);
double	ft_abs(double nb);

#endif
