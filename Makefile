# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 13:19:57 by hutzig            #+#    #+#              #
#    Updated: 2024/07/29 17:27:44 by hutzig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

MLX_DIR = ./lib/MLX42

SOURCES = main.c 

OBJECTS = $(SOURCES:.c=.o)

HEADERS = -I ./include -I $(MLX_DIR)/include

# MLX42 is dependent on other libraries (dl - dynamically loaded library, glfw - graphics library framework, m - math library
LIBS = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -lm -lpthread 

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: libmlx $(NAME)

libmlx:
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@$(RM) $(OBJECTS)
	@$(RM) $(MLX_DIR)/build

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
