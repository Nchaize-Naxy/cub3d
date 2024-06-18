NAME = cub3d
CFLAGS = -Wall -Werror -Wextra -I./includes

MLX_LINK = -I ./minilibx_linux/ -L./minilibx-linux -lmlx -lX11 -lm -lXext
MLX_LIB = ./minilibx-linux/libmlx.a
MLX_EX = $(MLX_LINK)

CFILES = main.c init.c

SRCS_DIR = ./src/

OBJS_DIR = ./.obj/
SRCS = $(addprefix $(SRCS_DIR), $(CFILES))

OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

$(NAME): $(MLX_LIB) $(OBJS) Makefile ./includes/
	$(CC) $(OBJS) -o $(NAME) $(MLX_EX)

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