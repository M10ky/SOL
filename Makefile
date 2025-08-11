NAME = so_long

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

FT_PRINTF_DIR = ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a

SRC = so_long.c \
		map.c \
		validate_map.c \
		ft_utils.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_check.c \
		ft_init_and_free.c \
		ft_control.c \
		ft_utils2.c

FT_PRINTF_SRC = \
	$(FT_PRINTF_DIR)/ft_check.c \
	$(FT_PRINTF_DIR)/ft_print_char.c \
	$(FT_PRINTF_DIR)/ft_print_hex.c \
	$(FT_PRINTF_DIR)/ft_print_int.c \
	$(FT_PRINTF_DIR)/ft_print_pointer.c \
	$(FT_PRINTF_DIR)/ft_print_string.c \
	$(FT_PRINTF_DIR)/ft_print_unsigned.c \
	$(FT_PRINTF_DIR)/ft_printf.c \
	$(FT_PRINTF_DIR)/ft_utils.c

OBJ = $(SRC:.c=.o)
FT_PRINTF_OBJ = $(FT_PRINTF_SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -L$(FT_PRINTF_DIR) -lftprintf

all: $(MLX_LIB) $(FT_PRINTF_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(FT_PRINTF_LIB): $(FT_PRINTF_OBJ)
	ar rcs $(FT_PRINTF_LIB) $(FT_PRINTF_OBJ)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c so_long.h
	$(CC) $(CFLAGS) -c $< -o $@

$(FT_PRINTF_DIR)/%.o: $(FT_PRINTF_DIR)/%.c $(FT_PRINTF_DIR)/ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(FT_PRINTF_OBJ)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(FT_PRINTF_LIB) $(MLX_LIB)

re: fclean all
