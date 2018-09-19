# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/25 18:47:49 by fdel-car          #+#    #+#              #
#    Updated: 2018/09/19 12:50:33 by fdel-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Scop

SRCS = $(shell find ./src -name *.c)

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: lib $(NAME)

$(NAME): $(OBJS)
	@gcc -I./includes `pkg-config --libs glfw3` `pkg-config --libs glew` -o $@ $^ ./libft/libft.a -framework OpenGL
	@# @gcc -I./includes -o $@ $^ ./libft/libft.a -lGLEW -lGLU -lGL -lglfw -lm
	@echo "\033[1;31m$(NAME) compiled successfully"
	@echo "\033[1A\033[0;39m"

$(OBJS): $(SRCS)
	@clang $(CFLAGS) -c $^ `pkg-config --cflags glfw3` `pkg-config --cflags glew` -I./libft/includes -I./includes
	@# @clang $(CFLAGS) -c -fPIC $^ `pkg-config --cflags glew` -I./libft/includes -I./includes
	@mv *.o src

lib:
	@make -C libft

clean:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re lib
