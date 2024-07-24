/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:14:42 by nchaize-          #+#    #+#             */
/*   Updated: 2024/07/24 11:15:10 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	wall_check(t_data *data, float dir_x, float dir_y, float c_a)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	
	x1 = (int)data->ray.x1;
	y1 = (int)data->ray.y1;
	x2 = (int)data->ray.x2;
	y2 = (int)data->ray.y2;
	//printf("--------------\nwall 1 : %f\nwith x1 y1 : %d, %d\nwall 2 : %f\nwith x2 y2 : %d, %d\n--------------\ndir x : %f\ndir y : %f\n--------------\n\n", data->wall1, x1, y1, data->wall2, x2, y2, dir_x, dir_y);
	if (data->wall1 <= data->wall2)
	{
		if (dir_y <= 0)
		{
			if (data->map[y1 - 1][x1] == '1')
				return (data->wall_color = YELLOW, data->wall1);
		}
		if (dir_y >= 0)
		{
			if (data->map[y1][x1] == '1')
				return (data->wall_color = RED, data->wall1);
		}
		data->ray.pos_x = data->ray.x1;
		data->ray.pos_y = data->ray.y1;
		raycast_x_wall(data, dir_x, dir_y, c_a);
	}
	else
	{
		if (dir_x >= 0)
		{
			if (data->map[y2][x2] == '1')
				return (data->wall_color = GREEN, data->wall2);
		}
		if (dir_x <= 0)
		{
			if (data->map[y2][x2 - 1] == '1')
				return (data->wall_color = BLUE, data->wall2);
		}
		data->ray.pos_x = data->ray.x2;
		data->ray.pos_y = data->ray.y2;
		raycast_y_wall(data, dir_x, dir_y, c_a);
	}
	return (0);
}

int	raycast_x_wall(t_data *data, float dir_x, float dir_y, float c_a)
{
	(void) dir_x;
	data->ray.y1 = (int)data->ray.pos_y;
	if ((data->ray.pos_y != data->player->pos_y) && (dir_y <= 0))
		data->ray.y1 -= 1;
	if (dir_y >= 0)
		data->ray.y1 += 1;
	data->ray.x1 = (data->ray.y1 - data->ray.pos_y) / tan(data->player->a + c_a) + data->ray.pos_x;
	data->wall1 = sqrt(pow(data->ray.x1 - data->player->pos_x, 2) + pow(data->ray.y1 - data->player->pos_y, 2));
	return (0);
}

int	raycast_y_wall(t_data *data, float dir_x, float dir_y, float c_a)
{
	(void) dir_y;
	data->ray.x2 = (int)data->ray.pos_x;
	if ((data->ray.pos_x != data->player->pos_x) && (dir_x <= 0))
		data->ray.x2 -= 1;
	if (dir_x >= 0)
		data->ray.x2 += 1;
	data->ray.y2 = (data->ray.x2 - data->ray.pos_x) * tan(data->player->a + c_a) + data->ray.pos_y;
	data->wall2 = sqrt(pow(data->ray.x2 - data->player->pos_x, 2) + pow(data->ray.y2 - data->player->pos_y, 2));
	return (0);
}

int	raycast(t_data *data, float dir_x, float dir_y, float c_a)
{
	dir_x = cos(data->player->a + c_a);
	dir_y = sin(data->player->a + c_a);
	raycast_x_wall(data, dir_x, dir_y, c_a);
	raycast_y_wall(data, dir_x, dir_y, c_a);
	while (data->wall == 0)
	{
		data->wall = wall_check(data, dir_x, dir_y, c_a);
	}
	return (0);
}