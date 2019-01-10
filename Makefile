TARGET := scop
SRCS_DIR := ./srcs
OBJS_DIR := ./objs
CC := clang
CFLAGS := -Wall -Wextra -Werror
ignore-warnings : CFLAGS := -w

# Colors
RESET := \033[0m
GREEN := \033[32;01m
ERROR := \033[31;01m
WARN := \033[33;01m
# Formatting
CLEAR_LINE := \033[2K
MOVE_CURSOR_UP := \033[1A

SRCS := $(shell find $(SRCS_DIR) -name *.c)
OBJS := $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))

all: lib $(OBJS_DIR) $(TARGET)

ignore-warnings: all

$(OBJS_DIR):
	@mkdir -p ./objs

$(TARGET): $(OBJS)
	@# $(CC) $(CFLAGS) -I./includes `pkg-config --libs glfw3` `pkg-config --libs glew` -o $@ $^ ./libft/libft.a # MacOS
	@$(CC) $(CFLAGS) -I./includes -o $@ $^ ./libft/libft.a -lGLEW -lGLU -lGL -lglfw -lm # Linux
	@echo "\n$(GREEN)The target $(TARGET) was compiled successfully!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "$(CLEAR_LINE)Creating object of the $(TARGET) with $^...$(MOVE_CURSOR_UP)"
	@# @$(CC) $(CFLAGS) -c $^ `pkg-config --cflags glfw3` `pkg-config --cflags glew` -o $@ -I./libft/includes -I./includes # MacOS
	@$(CC) $(CFLAGS) -c -fPIC $^ `pkg-config --cflags glew` -o $@ -I./libft/includes -I./includes # Linux

lib:
	@make -C libft

clean:
	@rm -rf objs/

fclean: clean
	@rm -f $(TARGET)

re: fclean
	@make all

.PHONY: all lib clean fclean re ignore-warnings
