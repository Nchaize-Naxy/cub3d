NAME = cub3d

MLX_LINK = -I. -I./minilibx_linux/ -L./minilibx-linux-lmlx -lX11 -lXext
MLX_LIB = ./minilibx-linux/libmlx.a
MLX_EX = $(MLX_LIB) $(MLX_LINK)

CFLAGS = -Wall -Werror -Wextra -I ./includes/

CFILES = main.c\

SRCS_DIR = ./src/

OBJS_DIR = ./.obj/
SRCS = $(addprefix $(SRCS_DIR), $(CFILES))

OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

$(NAME): $(MLX_LIB) $(OBJS) Makefile ./includes/
	$(CC) $(OBJS) $(MLX_EX) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re