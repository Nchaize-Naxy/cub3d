/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:54:45 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/19 15:34:07 by nchaize-         ###   ########.fr       */
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

# define WHITE 16777215
# define RED 16711680
# define GREEN 65280
# define BLUE 255
# define YELLOW 16776960
# define CYAN 65535
# define PURPLE 16711935
# define BLACK 3289650

# define ID_NO  "NO"
# define ID_SO  "SO"
# define ID_WE  "WE"
# define ID_EA  "EA"
# define ID_F   "F"
# define ID_C   "C"

typedef struct s_player
{
	int		x;
	int		y;
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	a;
	
}	t_player;

typedef struct	s_textures
{
	char	*N_path;
	char	*S_path;
	char	*W_path;
	char	*E_path;

	char	*Floor_color;
	char	*Ceiling_color;
}	t_textures;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	int			map_fd;
	size_t		height;
	size_t		length;
	t_player	*player;
	t_textures	*textures;
}	t_data;

typedef struct s_parsing
{
	char	*indentifier;
	char	*line;
	
}	t_parsing;

//functionalities
int	init(t_data *data);
int	play(t_data *data);
void	minimap(t_data *data);

//parsing
int	is_valid_ch(char c);

//utils
size_t	ft_strlen(const char *str);
int		ft_isalnum(int c);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif