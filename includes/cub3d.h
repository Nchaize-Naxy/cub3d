/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:54:45 by nchaize-          #+#    #+#             */
/*   Updated: 2024/10/18 15:03:17 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdbool.h>
# include "get_next_line.h"

# define WHITE 16777215
# define RED 16711680
# define GREEN 65280
# define BLUE 255
# define YELLOW 16776960
# define CYAN 65535
# define PURPLE 16711935
# define BLACK 3289650

# define WINHEIGHT 1080
# define WINWIDTH 1920

# define ID_NO  "NO"
# define ID_SO  "SO"
# define ID_WE  "WE"
# define ID_EA  "EA"
# define ID_F   "F"
# define ID_C   "C"
# define S		0
# define N		1
# define E		2
# define W		3

typedef struct s_wall
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_wall;

typedef struct s_ray
{
	float	x1;
	float	x2;
	float	y1;
	float	y2;
	float	wall_x;
	float	wall_y;
	float	pos_x;
	float	pos_y;
}	t_ray;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	a;

	int		m_x;
	int		move_f;
	int		move_b;
	int		move_r;
	int		move_l;
	int		rotate_r;
	int		rotate_l;
	int		free_mouse;

}	t_player;

typedef struct s_image
{
	char	*addr;
	void	*img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_tx_info
{
	int		i_create;
	int		*info;
	void	*img;
	int		width;
	int		height;
	int		bits_px;
	int		size_line;
	int		endian;
}	t_tx_info;

typedef struct s_textures
{
	int			i;
	t_tx_info	*no;
	t_tx_info	*so;
	t_tx_info	*ea;
	t_tx_info	*we;
	int			floor_color;
	int			ceiling_color;
}	t_textures;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	int			map_fd;
	bool		exit;
	float		wall;
	float		wall1;
	float		wall2;
	size_t		height;
	size_t		length;
	t_player	*player;
	t_textures	*textures;
	t_ray		ray;
	int			wall_dir;
	t_image		img;
	bool		is_player;
}	t_data;

typedef struct s_parsing
{
	char	*indentifier;
	char	*line;

}	t_parsing;

//functionalities
int		init(t_data *data);
void	free_data(t_data *data, int free_textures);
int		on_focus_in(t_data *data);
int		on_focus_out(t_data *data);

//parsing
int		is_valid_ch(char c);
int		parsing(char *map_name, t_data *data);
char	*dup_map_row(const char *s);
int		check_map(char **map, t_data *data);
int		handle_map(char *line, t_data *data);
int		handle_identifier(char *line, t_data *data);
size_t	count_tab(char **tab);
int		free_tab(char **tab);
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);
int		conv_rgb(char *rgb, char *hexbase);
int		check_empty(int line, int col, t_data *data, char space);
int		check_extension(char *map_name, char *extension);
char	*no_back_n(char **split);
void	destroy(t_data *data);
int		check_map_line(char *line);
int		check_name(char *map_name);
int		check_file_textures(t_data *data);
void	free_new_map(char **tab, size_t i);

//raycast
float	wall_check(t_data *data, float dir_x, float dir_y);
float	wall_check_one(t_data *data, float dir_x, float dir_y, t_wall w);
float	wall_check_two(t_data *data, float dir_x, float dir_y, t_wall w);
int		raycast_x_wall(t_data *data, float dir_x, float dir_y);
int		raycast_y_wall(t_data *data, float dir_x, float dir_y);
int		raycast(t_data *data, float dir_x, float dir_y, int c_a_time);
void	reset_raycast(t_data *data);

//render
int		render(t_data *data);
void	my_mlx_put_pixel(t_data *data, int x, int y, int color);
int		play(t_data *data, int c_a_time, int i);
int		get_pixel(t_data *data, int wall_height, int i, int c_a_time);

//exit
int		on_destroy(t_data *data);
void	destroy_textures(t_data *data);
void	free_textures(t_data *data);

//movement
int		handle_input(int keysym, t_data *data);
int		move_player(t_data *data);
int		move_mouse(t_data *data, int *x, int *y);
int		release_handler(int keysym, t_data *data);
void	movement_f_b(t_data *data, float move_x, float move_y);
void	movement_r_l(t_data *data, float move_x, float move_y);
void	movement_rotation(t_data *data);

//conv_base
int		ft_atoi_base(char *str, char *base);
int		base_check(char *str, size_t len);
int		str_len(char *str);
int		power(unsigned int nbr, size_t len);

//utils
size_t	ft_strlen(const char *str);
int		ft_isalnum(int c);
char	*ft_strdup(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
void	error(char *err_msg);
int		is_alnum(int c);
int		ft_atoi(const char *str);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strjoin_update(char *buffer, char *buffer_read);

//textures
int		init_textures(t_data *data);
void	free_textures(t_data *data);

//init
int		init_mlx(t_data *data);
int		init_data(t_data *data);

#endif
