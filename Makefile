NAME := miniRT
NAME_BONUS := miniRT_bonus
CC ?= cc
CFLAGS ?= -Wall -Wextra -Werror
LDFLAGS ?= -ldl -lglfw -lm

SRC_DIR := src/mandatory
INC_DIR := include/mandatory
OBJ_DIR := obj/mandatory

SRC_BONUS_DIR := src/bonus
INC_BONUS_DIR := include/bonus
OBJ_BONUS_DIR := obj/bonus

LIB_DIR := lib

SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

SRCS_BONUS := $(shell find $(SRC_BONUS_DIR) -name "*.c")
OBJS_BONUS := $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)
DEPS_BONUS := $(OBJS_BONUS:%.o=%.d)

LIBFT_DIR := $(LIB_DIR)/libft
HEADERS := -I$(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

MLX42_DIR := $(LIB_DIR)/MLX42
HEADERS += -I$(MLX42_DIR)/include
MLX42 = $(MLX42_DIR)/build/libmlx42.a

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) $(HEADERS) -I$(INC_DIR) $(OBJS) $(LIBFT) $(MLX42) $(LDFLAGS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) $(HEADERS) -I$(INC_BONUS_DIR) $(OBJS_BONUS) $(LIBFT) $(MLX42) $(LDFLAGS) -pthread -o $(NAME_BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -I$(INC_DIR) -MMD -MP -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -I$(INC_BONUS_DIR) -MMD -MP -c $< -o $@

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

-include $(DEPS) $(DEPS_BONUS)

all: $(NAME)

bonus: $(NAME_BONUS)

libft: $(LIBFT)

mlx42: $(MLX42)

clean:
	@rm -rf obj
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory clean

fclean: clean
	@rm -rf $(NAME) $(NAME)_bonus
	@rm -rf $(MLX42_DIR)/build
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory fclean

re: fclean all

debug: fclean
	@$(MAKE) -C $(LIBFT_DIR) debug
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build -DDEBUG=1
	@cmake --build $(MLX42_DIR)/build -j4
	@$(MAKE) all bonus CFLAGS="$(CFLAGS) -g3" --no-print-directory

sanitize: fclean
	@$(MAKE) -C $(LIBFT_DIR) sanitize
	@$(MAKE) all bonus CFLAGS="$(CFLAGS) -g3 -fsanitize=address,undefined" LDFLAGS="$(LDFLAGS) -fsanitize=address,undefined" --no-print-directory

fast: fclean
	@$(MAKE) -C $(LIBFT_DIR) fast
	@$(MAKE) all bonus CFLAGS="$(CFLAGS) -O3 -march=native -ffast-math -flto" LDFLAGS="$(LDFLAGS) -flto" --no-print-directory

.PHONY: all clean fclean re bonus debug sanitize fast libft mlx42
