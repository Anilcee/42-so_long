# Compiler ve flag'ler
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Dosya yolları
SRCS = main.c
OBJS = $(SRCS:.c=.o)
NAME = so_long
MLX_DIR = minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a

LINUX_LIBS = -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I$(MLX_DIR) -L$(MLX_DIR) -lmlx $(LINUX_LIBS)

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(MLX_DIR) fclean

re: fclean all
