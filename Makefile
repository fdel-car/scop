# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/25 18:47:49 by fdel-car          #+#    #+#              #
#    Updated: 2017/11/07 15:38:24 by fdel-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

SRCS = src/main.c
		# src/load_texture.c src/matrice.c src/vector.c \
		src/vector_bis.c src/init.c src/callback.c src/obj_parser.c \
		src/handle_mtl.c

OBJS = main.o
		# load_texture.o matrice.o vector.o vector_bis.o init.o callback.o \
		obj_parser.o handle_mtl.o

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	# @make re -C libft
	@gcc  -I./includes `pkg-config --libs glfw3` `pkg-config --libs glew` \
	-o $@ $^ ./libft/libft.a -framework OpenGL
	@echo "\033[1;31m$(NAME) compiled successfully"
	@echo "\033[1A\033[0;39m"

$(OBJS): $(SRCS)
	@clang $(CFLAGS) -c $^ `pkg-config --cflags glfw3` \
	`pkg-config --cflags glew` -I./libft/includes -I./includes

clean:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
