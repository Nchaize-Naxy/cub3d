/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:09:16 by pinkdonkeyj       #+#    #+#             */
/*   Updated: 2024/08/28 09:21:50 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void my_mlx_put_pixel(t_data *data, int x, int y, int color)																																	
{
	((unsigned int*)data->img.addr)[y*(data->img.line_length >> 2) + x] = color;
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
		play(data, c_a_time);
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
	(void) data;
	exit(0);
	return (0);
}

/* int	get_color_value(t_data *data, char c)
{
	
} */

int	get_pixel(t_data *data, int wall_height, int i, int c_a_time)
{
	double x;
	int	x_int;
	int	tx_x;
	int	tx_y;
	t_tx_info	*texture;
	static int j = 1;

	texture = NULL;
	x = 1;
	if (data->wall_dir == N || data->wall_dir == S)
	{
		if (data->wall_dir == N)
			texture = data->textures->NO;
		if (data->wall_dir == S)
			texture = data->textures->SO;
		x_int = (int) data->ray.pos_x;
		x = (data->ray.pos_x - x_int);
	}
	else if (data->wall_dir == E || data->wall_dir == W)
	{
		x_int = (int) data->ray.pos_y;
		if (data->wall_dir == E)
		{
			texture = data->textures->EA;
			x = ((data->ray.pos_y - x_int));
		}
		if (data->wall_dir == W)
		{
			texture = data->textures->WE;
			x = (1 - (data->ray.pos_y - x_int));
		}
	}
	if (!texture)
	{
		write(1, "no texture\n", 11);
		return (0);
	}
	//printf("x is %f\n", x);
	(void) j;
/* 	if (j %100 == 0)
	{
		printf("wall height is %d\n", wall_height);
		printf("ray.pos_x is %f\nray.pos_y is %f\n", data->ray.pos_x, data->ray.pos_y);
		printf("ray.wall_x is %f\nray.wall_y is %f\n", data->ray.wall_x, data->ray.wall_y);
		printf("x is %f\nx_int is %d\n", x, x_int);
		printf("wall dir is %d\n", data->wall_dir);
	} */
	j++;
	(void) c_a_time;
	tx_x = texture->width * x;
	tx_y = (texture->height / 2) + (i * texture->height / wall_height);
	return (texture->info[tx_y * (texture->width) + tx_x]);
}

int	play(t_data *data, int c_a_time)
{
	int	wall_height;
	int	i;
	int	half_width;
	int	half_height;

	i = 0;
	half_width = WINWIDTH / 2;
	half_height = WINHEIGHT / 2;
	//printf("%d\n", half_width);
/* 	if (data->wall < 1.0)
		wall_height = round(WINWIDTH / (1 - data->wall));
	else */
	wall_height = round((WINWIDTH / data->wall));
	//printf("WINWIDTH is %d, data-> wall is %f, wall_height is %d\n", WINWIDTH, data->wall, wall_height);
	//printf("c_a_time is %d\n", c_a_time);

	while (i <= (wall_height) / 2 && i <= half_height)
	{
		my_mlx_put_pixel(data, half_width + c_a_time, (half_height) - i, get_pixel(data, wall_height, -i, c_a_time));
		my_mlx_put_pixel(data, half_width + c_a_time, (half_height) + i, get_pixel(data, wall_height, i, c_a_time));
		i++;
	}
	while (i <= half_height)
	{
		my_mlx_put_pixel(data, (half_width + c_a_time), ((half_height) - i), data->textures->Ceiling_color);
		my_mlx_put_pixel(data, (half_width + c_a_time), ((half_height) + i), data->textures->Floor_color);
		i++;
	}
	return (0);
}
