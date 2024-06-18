/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:54:45 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/18 10:30:27 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <stdlib.h>

typedef struct s_player
{
	int		x;
	int		y;
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	t_player	*player;

}	t_data;

int	init(t_data *data);

#endif