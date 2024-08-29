/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:51:22 by nchaize-          #+#    #+#             */
/*   Updated: 2024/08/29 16:03:03 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movement_f_b(t_data *data, float move_x, float move_y)
{
	if (data->player->move_f == 1)
	{
		if (data->map[(int)(data->player->pos_y)]
				[(int)(data->player->pos_x + move_x)] != '1')
			data->player->pos_x += move_x;
		if (data->map[(int)(data->player->pos_y + move_y)]
				[(int)(data->player->pos_x)] != '1')
			data->player->pos_y += move_y;
	}
	if (data->player->move_b == 1)
	{
		if (data->map[(int)(data->player->pos_y)]
				[(int)(data->player->pos_x - move_x)] != '1')
			data->player->pos_x -= move_x;
		if (data->map[(int)(data->player->pos_y - move_y)]
				[(int)(data->player->pos_x)] != '1')
			data->player->pos_y -= move_y;
	}
}

void	movement_r_l(t_data *data, float move_x, float move_y)
{
	if (data->player->move_r == 1)
	{
		if (data->map[(int)(data->player->pos_y)]
				[(int)(data->player->pos_x - move_y)] != '1')
			data->player->pos_x -= move_y;
		if (data->map[(int)(data->player->pos_y + move_x)]
				[(int)(data->player->pos_x)] != '1')
			data->player->pos_y += move_x;
	}
	if (data->player->move_l == 1)
	{
		if (data->map[(int)(data->player->pos_y)]
				[(int)(data->player->pos_x + move_y)] != '1')
			data->player->pos_x += move_y;
		if (data->map[(int)(data->player->pos_y - move_x)]
				[(int)(data->player->pos_x)] != '1')
			data->player->pos_y -= move_x;
	}
}

void	movement_rotation(t_data *data)
{
	if (data->player->rotate_l == 1)
	{
		data->player->a -= 0.02;
		if (data->player->a < 0)
			data->player->a += 2 * M_PI;
		data->player->dir_x = cos(data->player->a);
		data->player->dir_y = sin(data->player->a);
	}
	if (data->player->rotate_r == 1)
	{
		data->player->a += 0.02;
		if (data->player->a > 2 * M_PI)
			data->player->a -= 2 * M_PI;
		data->player->dir_x = cos(data->player->a);
		data->player->dir_y = sin(data->player->a);
	}
}
