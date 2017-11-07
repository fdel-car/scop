# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/25 18:47:49 by fdel-car          #+#    #+#              #
#    Updated: 2017/11/07 17:59:07 by fdel-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

SRCS = src/main.c src/load_obj.c src/init_gl.c

OBJS = main.o load_obj.o init_gl.o

CFLAGS = # -Wall -Wextra -Werror

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
