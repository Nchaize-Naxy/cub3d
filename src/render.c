/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:09:16 by pinkdonkeyj       #+#    #+#             */
/*   Updated: 2024/09/04 12:18:41 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	((unsigned int *)data->img.addr)[y * (data->img.line_length >> 2) + x]
		= color;
}

int	render(t_data *data)
{
	int		c_a_time;
	int		half_width;

	half_width = WINWIDTH / 2;
	c_a_time = -(half_width);
	move_player(data);
	while (c_a_time <= half_width)
	{
		raycast(data, data->player->dir_x, data->player->dir_y, c_a_time);
		play(data, c_a_time, 0);
		reset_raycast(data);
		c_a_time++;
	}
	data->ray.x1 = data->player->pos_x;
	data->ray.y1 = data->player->pos_y;
	data->ray.x2 = data->player->pos_x;
	data->ray.y2 = data->player->pos_y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	return (0);
}

int	on_destroy(t_data *data)
{
	free_textures(data);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_data(data);
	exit(0);
	return (0);
}

float	get_pixel_pos(t_data *data, t_tx_info **texture, int x_int)
{
	if (data->wall_dir == N || data->wall_dir == S)
	{
		if (data->wall_dir == N)
			*texture = data->textures->NO;
		if (data->wall_dir == S)
			*texture = data->textures->SO;
		x_int = (int) data->ray.pos_x;
		return (data->ray.pos_x - x_int);
	}
	else if (data->wall_dir == E || data->wall_dir == W)
	{
		x_int = (int) data->ray.pos_y;
		if (data->wall_dir == E)
		{
			*texture = data->textures->EA;
			return ((data->ray.pos_y - x_int));
		}
		if (data->wall_dir == W)
		{
			*texture = data->textures->WE;
			return (1 - (data->ray.pos_y - x_int));
		}
	}
	return (0);
}

int	get_pixel(t_data *data, int wall_height, int i, int c_a_time)
{
	float		x;
	int			x_int;
	int			tx_x;
	int			tx_y;
	t_tx_info	*texture;

	texture = NULL;
	x_int = 0;
	x = get_pixel_pos(data, &texture, x_int);
	(void) c_a_time;
	tx_x = texture->width * x;
	tx_y = (texture->height / 2) + (i * texture->height / wall_height);
	return (texture->info[tx_y * (texture->width) + tx_x]);
}

int	play(t_data *data, int c_a_time, int i)
{
	int	wall_height;
	int	half_width;
	int	half_height;

	half_width = WINWIDTH / 2;
	half_height = WINHEIGHT / 2;
	wall_height = round((WINWIDTH / data->wall));
	while (i <= (wall_height) / 2 && i <= half_height)
	{
		my_mlx_put_pixel(data, half_width + c_a_time, (half_height) - i,
			get_pixel(data, wall_height, -i, c_a_time));
		my_mlx_put_pixel(data, half_width + c_a_time, (half_height) + i,
			get_pixel(data, wall_height, i, c_a_time));
		i++;
	}
	while (i <= half_height)
	{
		my_mlx_put_pixel(data, (half_width + c_a_time), ((half_height) - i),
			data->textures->Ceiling_color);
		my_mlx_put_pixel(data, (half_width + c_a_time), ((half_height) + i),
			data->textures->Floor_color);
		i++;
	}
	return (0);
}
