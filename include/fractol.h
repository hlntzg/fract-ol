/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:25:11 by hutzig            #+#    #+#             */
/*   Updated: 2024/08/09 09:59:14 by hutzig           ###   ########.fr       */
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

typedef struct 	s_range
{
	double	min;
	double	max;
	double	delta;
}	t_range;

typedef struct 	s_set
{
	double	x;
	double	y;
}	t_set;

typedef struct s_fractol
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	char		*set;
	uint32_t	max_iter;
	uint32_t	iter;
	t_set		julia_c;
	//double		julia_cx;
	//double		julia_cy;
	double		real_min;
	double		real_max;
	double		imag_min;
	double		imag_max;
	//double		real_delta;
	//double		imag_delta;
	t_range		real;
	t_range		imag;
	double		move_factor;
	double		zoom;
	uint32_t	pixel_color;
	double		zx;
	double		zy;
	double		cx;
	double		cy;
	double		k_red;
	double		k_green;
	double		k_blue;
	int32_t		pixel_x;
	int32_t		pixel_y;
}	t_fractol;

typedef struct	s_color
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	alpha;
}	t_color;

int	log_err(char *str, char *strerror);
int	log_guide(void);
int	is_valid_arg(int argc, char **argv);
int	is_signed_decimal(const char *str);
double	ft_abs(double nb);

void	init_fractol(t_fractol *fractol, char **argv);
void	init_view(t_fractol *fractol);
void	init_colors(t_fractol *fractol);
void	init_julia(t_fractol *fractol, char **argv);

void	ft_fractol_render(void *param);
void	julia(uint32_t x, uint32_t y, t_fractol *fractol);
void	mandelbrot(uint32_t x, uint32_t y, t_fractol *fractol);
void	burning_ship(uint32_t x, uint32_t y, t_fractol *fractol);

void	pixel_to_complex(double *r, double *i, t_fractol *fractol);
void	compute_escape_time(t_fractol *fractol);
void	compute_escape_time_burning(t_fractol *fractol);
void	compute_color(t_fractol *fractol);

void	ft_keyhook_general(mlx_key_data_t keydata, void *param);
void	ft_keyhook_colors(void *param);
void	ft_keyhook_arrowkeys(void *param);
void	ft_scrollhook(double xdelta, double ydelta, void *param);

uint32_t	ft_pixel(uint32_t red, uint32_t green, uint32_t blue, uint32_t a);

#endif
