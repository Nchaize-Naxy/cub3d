/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:40:26 by nchaize-          #+#    #+#             */
/*   Updated: 2024/08/29 16:15:36 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	wall_check_one(t_data *data, float dir_x, float dir_y, t_wall w)
{
	data->ray.wall_x = w.x1;
	data->ray.wall_y = w.y1;
	if (dir_y <= 0)
	{
		if (data->map[w.y1 - 1][w.x1] == '1')
			return (data->ray.pos_x = data->ray.x1,
				data->ray.pos_y = data->ray.y1,
				data->wall_dir = S, data->wall1);
	}
	if (dir_y >= 0)
	{
		if (data->map[w.y1][w.x1] == '1')
			return (data->ray.pos_x = data->ray.x1,
				data->ray.pos_y = data->ray.y1,
				data->wall_dir = N, data->wall1);
	}
	data->ray.pos_x = data->ray.x1;
	data->ray.pos_y = data->ray.y1;
	raycast_x_wall(data, dir_x, dir_y);
	return (0);
}

float	wall_check_two(t_data *data, float dir_x, float dir_y, t_wall w)
{
	data->ray.wall_x = w.x2;
	data->ray.wall_y = w.y2;
	if (dir_x >= 0)
	{
		if (data->map[w.y2][w.x2] == '1')
			return (data->ray.pos_x = data->ray.x2,
				data->ray.pos_y = data->ray.y2,
				data->wall_dir = E, data->wall2);
	}
	if (dir_x <= 0)
	{
		if (data->map[w.y2][w.x2 - 1] == '1')
			return (data->ray.pos_x = data->ray.x2,
				data->ray.pos_y = data->ray.y2,
				data->wall_dir = W, data->wall2);
	}
	data->ray.pos_x = data->ray.x2;
	data->ray.pos_y = data->ray.y2;
	raycast_y_wall(data, dir_x, dir_y);
	return (0);
}
