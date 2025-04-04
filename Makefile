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
	check_move.c \
	deplacements.c \
	flood_fill.c \
	kill_process.c \
	map.c \
	map2.c \
	test.c \
	utils.c \

DBG := \
	debug.c \

#Path to sources
VPATH = $(SRC_DIR) $(DBG_DIR)

# Objects
OBJ_FILES := $(addprefix $(OBJ_DIR)/$(SRC_DIR)/, $(SRC:.c=.o)) \
			 $(addprefix $(OBJ_DIR)/$(DBG_DIR)/, $(DBG:.c=.o)) \

# Compilation
CC := gcc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR) -MMD -MP

#Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB := -L./mlx -lmlx -lX11 -lXext -lGL

#Objects directory
OBJDIRS := $(sort $(dir $(OBJ_FILES)))

# Rules
all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

$(NAME): $(OBJ_FILES) $(MLX_DIR)/libmlx.a $(LIBFT)
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
debug : $(NAME)

-include $(OBJ_FILES:.o=.d)

.PHONY: all clean fclean re debug

#-MMD → génère un fichier .d par .c, sans les headers système
#-MP  → évite que make plante si un header est supprimé
#-include → insère dynamiquement les dépendances dans le Makefile
