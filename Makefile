# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 13:19:57 by hutzig            #+#    #+#              #
#    Updated: 2024/08/09 14:32:12 by hutzig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

DIR_MLX = ./lib/MLX42
DIR_LIBFT = ./lib/libft
DIR_SRC = ./sources

SOURCES = main.c \
	fractol_rendering.c \
	fractol_utils.c \
 	log.c \
	fractol_colors.c \
	fractal_sets.c \
	fractol_hooks.c \
	fractol_initialization.c \

SRC = $(addprefix $(DIR_SRC)/,$(SOURCES))

OBJECTS = $(SRC:.c=.o)

HEADERS = -I ./include -I $(DIR_MLX)/include -I $(DIR_LIBFT)

# MLX42 is dependent on other libraries (dl - dynamically loaded library, glfw - graphics library framework, m - math library)
MLXLIB = $(DIR_MLX)/build/libmlx42.a -ldl -lglfw -lm -lpthread 

LIBFT = -L $(DIR_LIBFT) -lft

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

$(NAME): mlx libft $(OBJECTS)
	@$(CC) $(OBJECTS) $(LIBFT) $(MLXLIB) $(HEADERS) -o $@

mlx:
	@cd lib && git clone https://github.com/codam-coding-college/MLX42.git
	@cmake $(DIR_MLX) -B $(DIR_MLX)/build && make -C $(DIR_MLX)/build -j4

libft:
	@make -C $(DIR_LIBFT)

$(DIR_SRC)/%.o: $(DIR_SRC)/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@$(RM) $(OBJECTS)
	@$(RM) $(DIR_MLX)/build
	@make -C $(DIR_LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all mlx libft clean fclean re
