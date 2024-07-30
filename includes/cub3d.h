/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:54:45 by nchaize-          #+#    #+#             */
/*   Updated: 2024/07/30 11:48:42 by gyvergni         ###   ########.fr       */
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

	int	move_f;
	int	move_b;
	int	move_r;
	int	move_l;
	int	rotate_r;
	int	rotate_l;
	
}	t_player;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

}	t_image;


typedef struct s_textures
{
	int		i;
	char	*N_path;
	char	*S_path;
	char	*W_path;
	char	*E_path;
	void	*N_img;
	void	*S_img;
	void	*W_img;
	void	*E_img;
	int		Floor_color;
	int		Ceiling_color;
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
	t_image		img;
	int			wall_dir;

	int			wall_color;
	
}	t_data;

typedef struct s_parsing
{
	char	*indentifier;
	char	*line;
	
}	t_parsing;

//functionalities
int	init(t_data *data);
int	play(t_data *data, float c_a, int c_a_time);
int	raycast_x_wall(t_data *data, float dir_x, float dir_y, float c_a);
int	raycast_y_wall(t_data *data, float dir_x, float dir_y, float c_a);
void	minimap(t_data *data);
int	put_ceiling(t_data *data);
int	put_floor(t_data *data);
inline void	my_mlx_put_pixel(t_data *data, int x, int y, int color);

//parsing
int	is_valid_ch(char c);
int parsing(char *map_name, t_data *data);
char	*dup_map_row(const char *s);
int	check_map(char **map, t_data *data);
int	handle_map(char *line, t_data *data);
int	handle_identifier(char *line, t_data *data);
size_t	count_tab(char **tab);
int		free_tab(char **tab);
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);
int	conv_rgb(char *rgb);


//utils
size_t	ft_strlen(const char *str);
int		ft_isalnum(int c);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	error(char *err_msg);
int		is_alnum(int c);
int	ft_atoi(const char *str);

#endif
