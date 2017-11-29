# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/25 18:47:49 by fdel-car          #+#    #+#              #
#    Updated: 2017/11/29 18:52:13 by fdel-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

SRCS = src/main.c src/load_obj.c src/init_gl.c src/matrice.c src/vector.c src/callback.c src/load_texture.c

OBJS = main.o load_obj.o init_gl.o matrice.o vector.o callback.o load_texture.o

CFLAGS = -Wall -Wextra -Werror

all: lib $(NAME)

$(NAME): $(OBJS)
	@gcc  -I./includes `pkg-config --libs glfw3` `pkg-config --libs glew` \
	-o $@ $^ ./libft/libft.a -framework OpenGL
	@echo "\033[1;31m$(NAME) compiled successfully"
	@echo "\033[1A\033[0;39m"

$(OBJS): $(SRCS)
	@clang $(CFLAGS) -c $^ `pkg-config --cflags glfw3` \
	`pkg-config --cflags glew` -I./libft/includes -I./includes

lib:
	@make libft

clean:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re lib
