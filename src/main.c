/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:34:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/07/30 12:36:11 by gyvergni         ###   ########.fr       */
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
		data->ray.wall_x = x1;
		data->ray.wall_y = y1;
		if (dir_y <= 0)
		{
			if (data->map[y1 - 1][x1] == '1')
				return (data->wall_color = 0x00FFFF00, data->wall_dir = S, data->wall1);
		}
		if (dir_y >= 0)
		{
			if (data->map[y1][x1] == '1')
				return (data->wall_color = 0x00FF0000, data->wall_dir = N, data->wall1);
		}
		data->ray.pos_x = data->ray.x1;
		data->ray.pos_y = data->ray.y1;
		raycast_x_wall(data, dir_x, dir_y, c_a);
	}
	else
	{
		data->ray.wall_x = x2;
		data->ray.wall_y = y2;
		if (dir_x >= 0)
		{
			if (data->map[y2][x2] == '1')
				return (data->wall_color = 0x0000FF00, data->wall_dir = E, data->wall2);
		}
		if (dir_x <= 0)
		{
			if (data->map[y2][x2 - 1] == '1')
				return (data->wall_color = 0x000000FF, data->wall_dir = W, data->wall2);
		}
		data->ray.pos_x = data->ray.x2;
		data->ray.pos_y = data->ray.y2;
		raycast_y_wall(data, dir_x, dir_y, c_a);
	}
	return (0);
}

int	raycast_x_wall(t_data *data, float dir_x, float dir_y, float c_a)
{
	(void) c_a;
	data->ray.y1 = (int)data->ray.pos_y;
	if ((data->ray.pos_y != data->player->pos_y) && (dir_y <= 0))
		data->ray.y1 -= 1;
	if (dir_y >= 0)
		data->ray.y1 += 1;
	data->ray.x1 = (data->ray.y1 - data->ray.pos_y) * (dir_x / dir_y) + data->ray.pos_x;
	data->wall1 = sqrt(pow(data->ray.x1 - data->player->pos_x, 2) + pow(data->ray.y1 - data->player->pos_y, 2) / (dir_x * dir_x + dir_y * dir_y));
	return (0);
}

int	raycast_y_wall(t_data *data, float dir_x, float dir_y, float c_a)
{
	(void) c_a;
	data->ray.x2 = (int)data->ray.pos_x;
	if ((data->ray.pos_x != data->player->pos_x) && (dir_x <= 0))
		data->ray.x2 -= 1;
	if (dir_x >= 0)
		data->ray.x2 += 1;
	data->ray.y2 = (data->ray.x2 - data->ray.pos_x) / (dir_x / dir_y) + data->ray.pos_y;
	data->wall2 = sqrt(pow(data->ray.x2 - data->player->pos_x, 2) + pow(data->ray.y2 - data->player->pos_y, 2) / (dir_x * dir_x + dir_y * dir_y));
	return (0);
}

int	raycast(t_data *data, float dir_x, float dir_y, int c_a_time)
{
	dir_x = cos(data->player->a) - (c_a_time * sin(data->player->a)) / WINWIDTH;
	dir_y = sin(data->player->a) + (c_a_time * cos(data->player->a)) / WINWIDTH;
	raycast_x_wall(data, dir_x, dir_y, 0);
	raycast_y_wall(data, dir_x, dir_y, 0);
	while (data->wall == 0)
	{
		data->wall = wall_check(data, dir_x, dir_y, 0);
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

int	move_player(t_data *data)
{
	float	move_x;
	float	move_y;
	
	move_x = data->player->dir_x * 5 / 100;
	move_y = data->player->dir_y * 5 / 100;
	if (data->player->move_f == 1)
	{
		if (data->map[(int)(data->player->pos_y)][(int)(data->player->pos_x + move_x)] != '1')
			data->player->pos_x += move_x;
		if (data->map[(int)(data->player->pos_y + move_y)][(int)(data->player->pos_x)] != '1')
			data->player->pos_y += move_y;
	}
	if (data->player->move_b == 1)
	{
		if (data->map[(int)(data->player->pos_y)][(int)(data->player->pos_x - move_x)] != '1')
			data->player->pos_x -= move_x;
		if (data->map[(int)(data->player->pos_y - move_y)][(int)(data->player->pos_x)] != '1')
			data->player->pos_y -= move_y;
	}
	if (data->player->move_r == 1)
	{
		if (data->map[(int)(data->player->pos_y)][(int)(data->player->pos_x - move_y)] != '1')
			data->player->pos_x -= move_y;
		if (data->map[(int)(data->player->pos_y + move_x)][(int)(data->player->pos_x)] != '1')
			data->player->pos_y += move_x;
	}
	if (data->player->move_l == 1)
	{
		if (data->map[(int)(data->player->pos_y)][(int)(data->player->pos_x + move_y)] != '1')
			data->player->pos_x += move_y;
		if (data->map[(int)(data->player->pos_y - move_x)][(int)(data->player->pos_x)] != '1')
			data->player->pos_y -= move_x;
	}
	if (data->player->rotate_l == 1)
	{
		data->player->a -= 0.02;
		data->player->a -= 0.02;
		if (data->player->a < 0)
			data->player->a += 2 * M_PI;
		data->player->dir_x = cos(data->player->a);
		data->player->dir_y = sin(data->player->a);
	}
	if (data->player->rotate_r == 1)
	{
		data->player->a += 0.02;
		data->player->a += 0.02;
		if (data->player->a > 2 * M_PI)
			data->player->a -= 2 * M_PI;
		data->player->dir_x = cos(data->player->a);
		data->player->dir_y = sin(data->player->a);
	}
	data->ray.pos_x = data->player->pos_x;
	data->ray.pos_y = data->player->pos_y;
	return (0);
}

void my_mlx_put_pixel(t_data *data, int x, int y, int color)																																	
{
	((unsigned int*)data->img.addr)[y*(data->img.line_length >> 2) + x] = color;
}

int	render(t_data *data)
{
	float	c_a;
	int		c_a_time;

	c_a = 0;
	c_a_time = -(WINWIDTH / 2);
	move_player(data);
	/*inutile*/
	data->ray.pos_x = data->player->pos_x;
	data->ray.pos_y = data->player->pos_y;
	//
	data->img.img = mlx_new_image(data->mlx, WINWIDTH, WINHEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length,
						&data->img.endian);
	while (c_a_time <= WINWIDTH / 2)
	{
		raycast(data, data->player->dir_x, data->player->dir_y, c_a_time); 
		play(data, c_a, c_a_time);
		reset_raycast(data);
		c_a_time++;
	}
	data->ray.x1 = data->player->pos_x;
	data->ray.y1 = data->player->pos_y;
	data->ray.x2 = data->player->pos_x;
	data->ray.y2 = data->player->pos_y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
	return (0);
}


int	release_handler(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		data->exit = true;
	if (keysym == XK_w || keysym == XK_Up)
		data->player->move_f = 0;
	if (keysym == XK_a)
		data->player->move_l = 0;
	if (keysym == XK_d)
		data->player->move_r = 0;
	if (keysym == XK_Left)
		data->player->rotate_l = 0;
	if (keysym == XK_Right)
		data->player->rotate_r = 0;
	if (keysym == XK_s || keysym == XK_Down)
		data->player->move_b = 0;
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		data->exit = true;
	if (keysym == XK_w || keysym == XK_Up)
		data->player->move_f = 1;
	if (keysym == XK_a)
		data->player->move_l = 1;
	if (keysym == XK_d)
		data->player->move_r = 1;
	if (keysym == XK_Left)
		data->player->rotate_l = 1;
	if (keysym == XK_Right)
		data->player->rotate_r = 1;
	if (keysym == XK_s || keysym == XK_Down)
		data->player->move_b = 1;
	if (data->exit == true)
		exit(0);
	return (0);
}

int	on_destroy(t_data *data)
{
	(void) data;
	exit(0);
	return (0);
}

void	putcase(t_data *data, int i, int j, int color)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	i *=32;
	j *=32;
	while (y <= 32)
	{
		x = 0;
		while (x <= 32)
		{
			my_mlx_put_pixel(data, x + i, y + j, color);
			x++;
		}
		y++;
	}
}

void	minimap(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				putcase(data, j, i, WHITE);
			else
				putcase(data, j, i, BLACK);
			j++;
		}
		i++;
	}
}

int	find_pixel_tx(t_data *data)
{
	float x;
	float y;
	
	if (data->wall_dir == N || data->wall_dir == S)
		x = data->ray.wall_x - fabs(data->ray.wall_x);
	else if (data->wall_dir == E || data->wall_dir == W)
		y = data->ray.wall_y - fabs(data->ray.wall_y);
	return (0);
}

int	play(t_data *data, float c_a, int c_a_time)
{
	int	wall_height;
	int	wall_height;
	int	i;
	int	half_width;
	int	half_height;

	i = 0;
	(void)c_a;
	half_width = WINWIDTH / 2;
	half_height = WINHEIGHT / 2;
	printf("%d\n", half_width);
	wall_height = round(WINWIDTH / data->wall);
	while (i <= (wall_height) / 2 && i < half_height)
	perp_walldist = (data->wall * sin(M_PI / 2 + c_a));
	wall_height = round(1080 / perp_walldist);
	while (i < (wall_height) / 2 && i < 540)
	{
		if (c_a_time <= half_width)
		if (c_a_time < 960)
		{
			my_mlx_put_pixel(data, half_width + c_a_time, (half_height) - i, data->wall_color);
			my_mlx_put_pixel(data, half_width + c_a_time, (half_height) + i, data->wall_color);
		}
		if (c_a_time > half_width)
		if (c_a_time >= 960)
		{
			my_mlx_put_pixel(data, half_width + (half_width - c_a_time), (half_height) - i, data->wall_color);
			my_mlx_put_pixel(data, half_width + (half_width - c_a_time), (half_height) + i, data->wall_color);
		}
		i++;
	}
	while (i < half_height)
	{
		if (c_a_time <= half_width)
		{
			my_mlx_put_pixel(data, (half_width + c_a_time), ((half_height) - i), data->textures->Ceiling_color);
			my_mlx_put_pixel(data, (half_width + c_a_time), ((half_height) + i), data->textures->Floor_color);
		}
		if (c_a_time > half_width)
		{
			my_mlx_put_pixel(data, (half_width) + (half_width - c_a_time), (half_height) - i, data->textures->Ceiling_color);
			my_mlx_put_pixel(data, (half_width) + (half_width - c_a_time), (half_height) + i, data->textures->Floor_color);
		}
		i++;
	}
	return (0);
}

int	mlx_type_shit(t_data *data)
{
	data->mlx_win = NULL;
	data->mlx_win = mlx_new_window(data->mlx, WINWIDTH, WINHEIGHT, "cub3d");
	//if (!data->mlx_win)
		//truc
	//render(data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_input, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &release_handler, data);
	mlx_hook(data->mlx_win, DestroyNotify, StructureNotifyMask,
		&on_destroy, data);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop(data->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data *data;

	if (argc > 2)
		return (error("Too many arguments"), 1);
	if (argc == 1)
		return (error("Not enough arguments"), 1);
	data = malloc(sizeof(t_data));
	init(data);
	if (parsing(argv[1], data) == 0)
		return (1);
	printf("Floor color out of init is: %d\n", data->textures->Floor_color);
	printf("Celing color out of init is: %d\n", data->textures->Ceiling_color);
	mlx_type_shit(data);
	return (0);
}
