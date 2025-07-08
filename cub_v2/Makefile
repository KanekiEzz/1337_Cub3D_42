# Directories
MLX_DIR		= ./src/lib/.mlx
MLX_LIB		= $(MLX_DIR)/libmlx.a
LIBFT_DIR	= ./src/lib/libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
SRC_DIR		= ./src
OBJ_DIR		= ./obj
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lbsd

SRCS		= \
			$(SRC_DIR)/lib/gnl/get_next_line.c \
			$(SRC_DIR)/lib/gnl/get_next_line_utils.c \
			$(SRC_DIR)/lib/malloc/ft_malloc.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_2.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_3.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_4.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_5.c \
			$(SRC_DIR)/components/parsing/map_parsing.c \
			$(SRC_DIR)/components/rendring/core/init.c \
        	$(SRC_DIR)/components/rendring/player/controls.c \
        	$(SRC_DIR)/components/rendring/player/movement.c \
        	$(SRC_DIR)/components/rendring/utils/map_utils.c \
        	$(SRC_DIR)/components/rendring/graphics.c \
        	$(SRC_DIR)/components/rendring/minimap.c \
        	$(SRC_DIR)/components/rendring/raycaster.c \
        	$(SRC_DIR)/components/rendring/eye/eye.c \
        	$(SRC_DIR)/components/rendring/floor_sky/floor_sky.c \
        	$(SRC_DIR)/components/rendring/weapon/weapon.c \
        	$(SRC_DIR)/components/rendring/door/door.c \
        	$(SRC_DIR)/components/rendring/enemy/enemy.c \
			$(SRC_DIR)/main/main.c \


OBJS		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

NAME		= cub3D

all: $(MLX_LIB) $(LIBFT_LIB) $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/lib/gnl
	@mkdir -p $(OBJ_DIR)/lib/malloc
	@mkdir -p $(OBJ_DIR)/components/parsing
	@mkdir -p $(OBJ_DIR)/components/rendring
	@mkdir -p $(OBJ_DIR)/components/rendring/core
	@mkdir -p $(OBJ_DIR)/components/rendring/player
	@mkdir -p $(OBJ_DIR)/components/rendring/utils
	@mkdir -p $(OBJ_DIR)/components/rendring/eye/eye.c \
	@mkdir -p $(OBJ_DIR)/components/rendring/floor_sky/floor_sky.c \
	@mkdir -p $(OBJ_DIR)/components/rendring/weapon/weapon.c \
	@mkdir -p $(OBJ_DIR)/components/rendring/door/door.c \
	@mkdir -p $(OBJ_DIR)/components/rendring/enemy/enemy.c \
	@mkdir -p $(OBJ_DIR)/main

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	@$(MAKE) -s -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) ./src/include/cub3d.h
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)
	@echo "$(NAME) compiled successfully"

clean:
	@$(MAKE) -s -C $(MLX_DIR) clean
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: all clean fclean re
