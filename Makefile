# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 13:19:57 by hutzig            #+#    #+#              #
#    Updated: 2024/08/21 12:05:39 by hutzig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

DIR_MLX = ./lib/MLX42
DIR_LIBFT = ./lib/libft
DIR_SRC = ./sources
DIR_BONUS = ./sources_bonus
DIR_OBJ = $(DIR_SRC)/objects
DIR_OBJ_BONUS = $(DIR_BONUS)/objects_bonus

SOURCES = main.c \
	fractol_rendering.c \
	fractol_utils.c \
 	log.c \
	fractol_colors.c \
	fractal_sets.c \
	fractol_hooks.c \
	fractol_initialization.c \

SOURCES_BONUS = main_bonus.c \
	fractol_rendering_bonus.c \
	fractol_utils_bonus.c \
 	log_bonus.c \
	fractol_colors_bonus.c \
	fractal_sets_bonus.c \
	fractol_hooks_bonus.c \
	fractol_initialization_bonus.c \

SRC = $(addprefix $(DIR_SRC)/,$(SOURCES))
SRC_BONUS = $(addprefix $(DIR_BONUS)/,$(SOURCES_BONUS))

OBJECTS = $(patsubst %.c,$(DIR_OBJ)/%.o,$(notdir $(SOURCES)))
OBJECTS_BONUS = $(patsubst %.c,$(DIR_OBJ_BONUS)/%.o,$(notdir $(SOURCES_BONUS)))

HEADERS = -I ./include -I $(DIR_MLX)/include -I $(DIR_LIBFT)
HEADERS_BONUS = -I ./include_bonus -I $(DIR_MLX)/include -I $(DIR_LIBFT)

MLXLIB = $(DIR_MLX)/build/libmlx42.a
LIBFT = $(DIR_LIBFT)/libft.a

# MLX42 is dependent on other libraries (dl-dynamically loaded, glfw-graphics library framework, m-math)
MLXLIB_FLAGS = $(DIR_MLX)/build/libmlx42.a -ldl -lglfw -lm
LIBFT_FLAGS = -L $(DIR_LIBFT) -lft

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(LIBFT) $(MLXLIB) $(NAME)

$(MLXLIB):
	@cd lib && git clone https://github.com/codam-coding-college/MLX42.git
	@cmake $(DIR_MLX) -B $(DIR_MLX)/build && make -C $(DIR_MLX)/build -j4

$(LIBFT):
	@make -C $(DIR_LIBFT)

$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LIBFT_FLAGS) $(MLXLIB) $(MLXLIB_FLAGS) $(HEADERS) -o $@

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

bonus: $(LIBFT) $(MLXLIB) $(OBJECTS_BONUS)
	@$(CC) $(OBJECTS_BONUS) $(LIBFT_FLAGS) $(MLXLIB) $(MLXLIB_FLAGS) $(HEADERS_BONUS) -o $(NAME)_bonus

$(DIR_OBJ_BONUS)/%.o: $(DIR_BONUS)/%.c | $(DIR_OBJ_BONUS)
	@$(CC) $(CFLAGS) $(HEADERS_BONUS) -c $< -o $@

$(DIR_OBJ_BONUS):
	@mkdir -p $(DIR_OBJ_BONUS)

clean:
	@$(RM) $(DIR_OBJ)
	@$(RM) $(DIR_OBJ_BONUS)
	@$(RM) $(DIR_MLX)/build
	@make -C $(DIR_LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME)_bonus
	@$(RM) $(DIR_MLX)
	@make -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all bonus clean fclean re
