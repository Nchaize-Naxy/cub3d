/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:14:42 by nchaize-          #+#    #+#             */
/*   Updated: 2024/08/29 16:07:04 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	wall_check(t_data *data, float dir_x, float dir_y)
{
	t_wall	w;
	float	result;

	result = 0;
	w.x1 = (int)data->ray.x1;
	w.y1 = (int)data->ray.y1;
	w.x2 = (int)data->ray.x2;
	w.y2 = (int)data->ray.y2;
	if (data->wall1 <= data->wall2)
	{
		result = wall_check_one(data, dir_x, dir_y, w);
		if (result != 0)
			return (result);
	}
	else
	{
		result = wall_check_two(data, dir_x, dir_y, w);
		if (result != 0)
			return (result);
	}
	return (0);
}

int	raycast_x_wall(t_data *data, float dir_x, float dir_y)
{
	data->ray.y1 = (int)data->ray.pos_y;
	if ((data->ray.pos_y != data->player->pos_y) && (dir_y <= 0))
		data->ray.y1 -= 1;
	if (dir_y >= 0)
		data->ray.y1 += 1;
	data->ray.x1 = (data->ray.y1 - data->ray.pos_y) * (dir_x / dir_y)
		+ data->ray.pos_x;
	data->wall1 = sqrt(pow(data->ray.x1 - data->player->pos_x, 2)
			+ pow(data->ray.y1 - data->player->pos_y, 2))
		/ sqrt(dir_x * dir_x + dir_y * dir_y);
	return (0);
}

int	raycast_y_wall(t_data *data, float dir_x, float dir_y)
{
	data->ray.x2 = (int)data->ray.pos_x;
	if ((data->ray.pos_x != data->player->pos_x) && (dir_x <= 0))
		data->ray.x2 -= 1;
	if (dir_x >= 0)
		data->ray.x2 += 1;
	data->ray.y2 = (data->ray.x2 - data->ray.pos_x) / (dir_x / dir_y)
		+ data->ray.pos_y;
	data->wall2 = sqrt(pow(data->ray.x2 - data->player->pos_x, 2)
			+ pow(data->ray.y2 - data->player->pos_y, 2))
		/ sqrt(dir_x * dir_x + dir_y * dir_y);
	return (0);
}

int	raycast(t_data *data, float dir_x, float dir_y, int c_a_time)
{
	dir_x = cos(data->player->a) - (c_a_time * sin(data->player->a)) / WINWIDTH;
	dir_y = sin(data->player->a) + (c_a_time * cos(data->player->a)) / WINWIDTH;
	raycast_x_wall(data, dir_x, dir_y);
	raycast_y_wall(data, dir_x, dir_y);
	while (data->wall == 0)
	{
		data->wall = wall_check(data, dir_x, dir_y);
	}
	return (0);
}

void	reset_raycast(t_data *data)
{
	data->wall = 0;
	data->ray.pos_x = data->player->pos_x;
	data->ray.pos_y = data->player->pos_y;
	data->wall1 = 0;
	data->wall2 = 0;
}
