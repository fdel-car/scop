# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 11:18:23 by fdel-car          #+#    #+#              #
#    Updated: 2018/09/19 12:50:53 by fdel-car         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS := $(shell find ./src -name *.c)

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n\033[2K\033[1;32mCompiling libft.a...\033[0;39m"
	@mv *.o src
	@ar rc $@ $(OBJS)
	@ranlib $@

%.o: %.c
	@echo "\033[2K\033[1;33mCreating object of the libft with $^...\033[0;39m\033[1A"
	@gcc $(CFLAGS) -c $^ -I./includes

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	@make all
