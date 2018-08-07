# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/25 18:47:49 by fdel-car          #+#    #+#              #
#    Updated: 2018/08/02 18:05:49 by fdel-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

SRCS = src/main.c src/load_obj.c src/init_gl.c src/matrice.c src/vector.c\
src/callback.c src/load_texture.c src/matrice_tools.c src/vector_op.c\
src/norm_vector.c src/unload_main.c src/unload_parser.c src/norm_parser.c\
src/handle_texture.c src/load_data.c src/load_material.c

OBJS = main.o load_obj.o init_gl.o matrice.o vector.o callback.o load_texture.o\
matrice_tools.o vector_op.o norm_vector.o unload_main.o unload_parser.o\
norm_parser.o handle_texture.o load_data.o load_material.o

CFLAGS = -Wall -Wextra -Werror

all: lib $(NAME)

$(NAME): $(OBJS)
	@gcc -I./includes `pkg-config --libs glfw3` `pkg-config --libs glew` \
	-o $@ $^ ./libft/libft.a -framework OpenGL
	@echo "\033[1;31m$(NAME) compiled successfully"
	@echo "\033[1A\033[0;39m"

$(OBJS): $(SRCS)
	@clang $(CFLAGS) -c $^ `pkg-config --cflags glfw3` \
	`pkg-config --cflags glew` -I./libft/includes -I./includes

lib:
	@make -C libft

clean:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re lib
