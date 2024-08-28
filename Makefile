NAME = cub3d
CFLAGS = -Wall -Werror -Wextra -I./includes

MLX_LINK = -I ./minilibx_linux/ -L./minilibx-linux -lmlx -lX11 -lm -lXext
MLX_LIB = ./minilibx-linux/libmlx.a
MLX_EX = $(MLX_LINK)

HEADERS = ./includes/cub3d.h\
		./includes/get_next_line.h\

CFILES = main.c\
	init.c\
	utils.c\
	raycast.c\
	movement.c\
	render.c\

CFILES_GNL = get_next_line.c\
	get_next_line_utils.c\

CFILES_PARSING = \
	check_map.c\
	check_empty.c\
	ft_split.c\
	parsing.c\
	parse_map.c\
	conv_base.c\
	conv_base_utils.c\

SRCS_DIR = ./src/
SRCS_GNL_DIR = ./src/gnl/
SRCS_PARSING_DIR = ./src/parsing/

OBJS_DIR = ./.obj/

SRCS = $(addprefix $(SRCS_DIR), $(CFILES))
SRCS_GNL = $(addprefix $(SRCS_GNL_DIR), $(CFILES_GNL))
SRCS_PARSING = $(addprefix $(SRCS_PARSING_DIR), $(CFILES_PARSING))

OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))
OBJS_GNL = $(addprefix $(OBJS_DIR), $(notdir $(SRCS_GNL:.c=.o)))
OBJS_PARSING = $(addprefix $(OBJS_DIR), $(notdir $(SRCS_PARSING:.c=.o)))

$(NAME): $(MLX_LIB) $(OBJS) $(OBJS_GNL) $(OBJS_PARSING) $(HEADERS) Makefile ./includes/
	$(CC) $(OBJS) $(OBJS_GNL) $(OBJS_PARSING) -o $(NAME) $(MLX_EX)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)%.o: $(SRCS_GNL_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJS_DIR)%.o: $(SRCS_PARSING_DIR)%.c
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
