NAME = so_long

# Directories
SRC_DIR = src
DBG_DIR = debug
LIBFT_DIR = libft
OBJ_DIR = obj
INCLUDE_DIR = includes
MLX_DIR = mlx

# Sources
SRC := \
	kill_process.c \
	textures.c \
	map.c \
	map2.c \
	set.c \
	test.c \

DBG := \
	debug.c \

#Path to sources
VPATH = $(SRC_DIR) $(DBG_DIR)

# Objects
OBJ_FILES := $(addprefix $(OBJ_DIR)/$(SRC_DIR)/, $(SRC:.c=.o)) \
			 $(addprefix $(OBJ_DIR)/$(DBG_DIR)/, $(DBG:.c=.o)) \

# Compilation
CC := gcc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)

#Library
LIBFT = $(LIBFT_DIR)/libft.a

# Minilibx directories
MLX_LIB := -L./mlx -lmlx -lX11 -lXext -lGL

#Objects directory
OBJDIRS := $(sort $(dir $(OBJ_FILES)))

# Rules
all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_DIR):
	make -C $(MLX_DIR)

$(NAME): $(OBJ_FILES) $(MLX_DIR) $(LIBFT)
	$(CC) $(OBJ_FILES) -o $(NAME) $(MLX_LIB) -L$(LIBFT_DIR) -lft

$(OBJ_DIR)/%.o: %.c | $(OBJDIRS)
	$(CC) $(CFLAGS) -c $< -o $@

#Create object directory if doesn't exist
$(OBJDIRS):
	@mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	@make -C $(MLX_DIR) clean

re: fclean all

debug : CFLAGS += -g
debug : re

.PHONY: all clean fclean re mlx debug
