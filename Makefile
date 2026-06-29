NAME := miniRT
CC ?= cc
CFLAGS ?= -Wall -Wextra -Werror
LDFLAGS ?= -ldl -lglfw -pthread -lm

SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
LIB_DIR := lib

HEADERS := -I$(INC_DIR)

SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

LIBFT_DIR := $(LIB_DIR)/libft
HEADERS += -I$(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

MLX42_DIR := $(LIB_DIR)/MLX42
HEADERS += -I$(MLX42_DIR)/include
MLX42 = $(MLX42_DIR)/build/libmlx42.a

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(MLX42) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -MMD -MP -c $< -o $@

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ] || [ ! -f $(LIBFT_DIR)/Makefile ]; then \
		git submodule update --init --recursive; \
	fi
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX42):
	@if [ ! -d "$(MLX42_DIR)" ] || [ ! -f $(MLX42_DIR)/CMakeLists.txt ]; then \
		git submodule update --init --recursive; \
	fi
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build -DDEBUG=0
	@cmake --build $(MLX42_DIR)/build -j4

-include $(DEPS)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(MLX42_DIR)/build
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory fclean

re: fclean all

bonus: re
	@mv $(NAME) $(NAME)_bonus

debug: fclean
	@$(MAKE) -C $(LIBFT_DIR) debug
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build -DDEBUG=1
	@cmake --build $(MLX42_DIR)/build -j4
	@$(MAKE) all CFLAGS="$(CFLAGS) -g3" --no-print-directory

sanitize: fclean
	@$(MAKE) -C $(LIBFT_DIR) sanitize
	@$(MAKE) all CFLAGS="$(CFLAGS) -g3 -fsanitize=address,undefined" LDFLAGS="$(LDFLAGS) -fsanitize=address,undefined" --no-print-directory

libft: $(LIBFT)

mlx42: $(MLX42)

.PHONY: all clean fclean re bonus debug sanitize libft mlx42
