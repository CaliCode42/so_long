NAME = so_long

# Directories
SRC_DIR = src
DBG_DIR = debug
GNL_DIR = gnl
FT_PRINTF_DIR = ft_printf
OBJ_DIR = obj
INCLUDE_DIR = includes
MLX_DIR = mlx

# Sources
SRC := \
	kill_process.c \
	textures.c \
	test.c \

DBG := \
	debug.c \

#GNL Sources
GNL := \
	get_next_line.c \
	get_next_line_utils.c \

# Sources ft_printf
PRINTF_FILES := \
	ft_atoi_base.c \
	ft_check_precision.c \
	ft_check_width.c \
	ft_convert_nb.c \
	ft_fill_withzero.c \
	ft_itoa_base.c \
	ft_memset.c \
	ft_parse_format.c \
	ft_present.c \
	ft_printf.c \
	ft_putformat.c \
	ft_putstr.c \
	ft_render_format.c \
	ft_strcpy.c \
	ft_strjoin.c \
	ft_strlen_int.c \
	print_type.c \
	ft_free.c \
	ft_pickstr.c \

#Path to sources
SRC := $(addprefix $(SRC_DIR)/, $(SRC))
DBG := $(addprefix $(DBG_DIR)/, $(DBG))
GNL := $(addprefix $(GNL_DIR)/, $(GNL))
PRINTF_FILES := $(addprefix $(FT_PRINTF_DIR)/, $(PRINTF_FILES))

# Objects
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o) \
		$(DBG:$(DBG_DIR)/%.c=$(OBJ_DIR)/$(DBG_DIR)/%.o) \
		$(PRINTF_FILES:$(FT_PRINTF_DIR)/%.c=$(OBJ_DIR)/$(FT_PRINTF_DIR)/%.o) \
		$(GNL:$(GNL_DIR)/%.c=$(OBJ_DIR)/$(GNL_DIR)/%.o)
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o)) \
			 $(addprefix $(OBJ_DIR)/, $(DBG:.c=.o)) \
			 $(addprefix $(OBJ_DIR)/, $(PRINTF_FILES:.c=.o)) \
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

$(OBJ_DIR)/$(DBG_DIR)/%.o: $(DBG_DIR)/%.c | $(OBJDIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(FT_PRINTF_DIR)/%.o: $(FT_PRINTF_DIR)/%.c | $(OBJDIRS)
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
