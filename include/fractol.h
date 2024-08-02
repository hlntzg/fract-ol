/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:25:11 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/02 14:29:57 by hutzig           ###   ########.fr       */
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

// resolution
# define WIDTH 1024
# define HEIGHT 1024
# define MAX_ITER 150

typedef struct s_fractol
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	char		*set;
	double		julia_cx;
	double		julia_cy;
	double		real_min;
	double		real_max;
	double		imag_min;
	double		imag_max;
} t_fractol;

typedef struct s_fractal
{
	double	zx;
	double	zy;
	double	cx;
	double	cy;
} t_fractal;

// functions
int	log_guide(void);
int	is_valid_arg(char *arg);

#endif
