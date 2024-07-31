/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:25:11 by hutzig            #+#    #+#             */
/*   Updated: 2024/07/31 10:58:19 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../lib/libft/libft.h"
//# include "MiniLibX/mlx.h"
//# include "MiniLibX/mlx_int.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // perror
# include <string.h> // strerror

// resolution
# define WIDTH 1080
# define HEIGHT 1080

typedef struct s_fractol
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int		red;
	int		blue;
	int		green;
	int		alpha;
} t_fractol;

int	log_guide(void);

#endif
