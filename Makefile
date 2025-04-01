NAME = so_long

# Directories
SRC_DIR = src
GNL_DIR = gnl
OBJ_DIR = obj
INCLUDE_DIR = includes
MLX_DIR = mlx

# Sources
SRC := \
	test.c \

GNL := \
	get_next_line.c \
	get_next_line_utils.c \

#Path to sources
SRC := $(addprefix $(SRC_DIR)/, $(SRC))
GNL := $(addprefix $(GNL_DIR)/, $(GNL))

# Objects
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o) \
		$(GNL:$(GNL_DIR)/%.c=$(OBJ_DIR)/$(GNL_DIR)/%.o)
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o)) \
			 $(addprefix $(OBJ_DIR)/, $(GNL_DIR:.c=.o)) \
# Compilation
CC := gcc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(MLX_DIR) -MMD -MP

# Minilibx directories
MLX_LIB := -L./mlx -lmlx -lX11 -lXext -lGL

#Objects directory
OBJDIRS := $(sort $(dir $(OBJ)))

# Rules
all: $(NAME)

$(MLX_DIR):
	make -C $(MLX_DIR)

$(NAME): $(OBJ) $(MLX_DIR)
	$(CC) $(OBJ) -o $(NAME) $(MLX_LIB)

$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJDIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(GNL_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJDIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIRS):
	@mkdir -p $(OBJDIRS) $(dir $(OBJ))

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	@make -C $(MLX_DIR) clean

re: fclean all

debug : CFLAGS += -g
debug : re

.PHONY: all clean fclean re mlx debug
