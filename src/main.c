/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:34:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/07/16 11:51:31 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	wall_check(t_data *data, float dir_x, float dir_y)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	
	x1 = (int)data->ray.x1;
	y1 = (int)data->ray.y1;
	x2 = (int)data->ray.x2;
	y2 = (int)data->ray.y2;
	//data->wall1 = sqrt(pow(fabs(data->ray.x1 - data->player->pos_x), 2) + pow(fabs(data->ray.y1 - data->player->pos_y), 2));
	//data->wall2 = sqrt(pow(fabs(data->ray.x2 - data->player->pos_x), 2) + pow(fabs(data->ray.y2 - data->player->pos_y), 2));
	//printf("--------------\n%f\n%f\n", data->wall1, data->wall2);
	if (data->wall1 <= data->wall2)
	{
		if ((dir_y <= 0 && dir_x >= 0) || (dir_y <= 0 && dir_x <= 0))
		{
			if (data->map[y1 - 1][x1] == '1')
				return (data->ray.pos_x = data->ray.x1,
					data->ray.pos_y = data->ray.y1, data->wall1);
		}
		if ((dir_y >= 0 && dir_x >= 0) || (dir_y >= 0 && dir_x <= 0))
		{
			/*prblm peut etre ici*/
			if (data->map[y1][x1] == '1')
				return (data->ray.pos_x = data->ray.x1,
					data->ray.pos_y = data->ray.y1, data->wall1);
		}
		data->ray.pos_x = data->ray.x1;
		data->ray.pos_y = data->ray.y1;
		raycast_x_wall(data, dir_x, dir_y);
	}
	else if (data->wall2 < data->wall1)
	{
		if ((dir_y <= 0 && dir_x >= 0) || (dir_y >= 0 && dir_x >= 0))
		{
			if (data->map[y2][x2] == '1')
				return (data->ray.pos_x = data->ray.x2,
					data->ray.pos_y = data->ray.y2, data->wall2);
		}
		if ((dir_y <= 0 && dir_x <= 0) || (dir_y >= 0 && dir_x <= 0))
		{
			if (data->map[y2][x2 - 1] == '1')
				return (data->ray.pos_x = data->ray.x2,
					data->ray.pos_y = data->ray.y2, data->wall2);
		}
		data->ray.pos_x = data->ray.x2;
		data->ray.pos_y = data->ray.y2;
		raycast_y_wall(data, dir_x, dir_y);
	}
	/*if (data->wall1 <= data->wall2)
	{
		if ((dir_y <= 0 && dir_x >= 0) || (dir_y <= 0 && dir_x <= 0))
		{
			if (data->map[y1 - 1][x1] == '1')
				return (data->ray.pos_x = data->ray.x1,
					data->ray.pos_y = data->ray.y1, data->wall1);
		}
		else if ((dir_y >= 0 && dir_x >= 0) || (dir_y >= 0 && dir_x <= 0))
		{
			if (data->map[y1][x1] == '1')
				return (data->ray.pos_x = data->ray.x1,
					data->ray.pos_y = data->ray.y1, data->wall1);
		}
		//si rien trouvé aussi regarder y
		if ((dir_y <= 0 && dir_x >= 0) || (dir_y >= 0 && dir_x >= 0))
		{
			if (data->map[y2][x2] == '1')
				return (data->ray.pos_x = data->ray.x2,
					data->ray.pos_y = data->ray.y2, data->wall2);
		}
		else if ((dir_y <= 0 && dir_x <= 0) || (dir_y >= 0 && dir_x <= 0))
		{
			if (data->map[y2][x2 - 1] == '1')
				return (data->ray.pos_x = data->ray.x2,
					data->ray.pos_y = data->ray.y2, data->wall2);
		}
	}
	else if (data->wall2 < data->wall1)
	{
		if ((dir_y <= 0 && dir_x >= 0) || (dir_y >= 0 && dir_x >= 0))
		{
			if (data->map[y2][x2] == '1')
				return (data->ray.pos_x = data->ray.x2,
					data->ray.pos_y = data->ray.y2, data->wall2);
		}
		else if ((dir_y <= 0 && dir_x <= 0) || (dir_y >= 0 && dir_x <= 0))
		{
			if (data->map[y2][x2 - 1] == '1')
				return (data->ray.pos_x = data->ray.x2,
					data->ray.pos_y = data->ray.y2, data->wall2);
		}
		//si rien trouvé aussi regarder x
		if ((dir_y <= 0 && dir_x >= 0) || (dir_y <= 0 && dir_x <= 0))
		{
			if (data->map[y1 - 1][x1] == '1')
				return (data->ray.pos_x = data->ray.x1,
					data->ray.pos_y = data->ray.y1, data->wall1);
		}
		else if ((dir_y >= 0 && dir_x >= 0) || (dir_y >= 0 && dir_x <= 0))
		{
			if (data->map[y1][x1] == '1')
				return (data->ray.pos_x = data->ray.x1,
					data->ray.pos_y = data->ray.y1, data->wall1);
		}
	}*/
	return (0);
}

int	raycast_x_wall(t_data *data, float dir_x, float dir_y)
{
	(void) dir_x;
	data->ray.y1 = (int)data->ray.y1;
	if (dir_y >= 0)
		data->ray.y1 += 1;
	data->ray.x1 = (data->ray.y1 - data->ray.pos_y) / tan(data->player->a) + data->ray.pos_x;
	data->wall1 = sqrt(pow(fabs(data->ray.x1 - data->player->pos_x), 2) + pow(fabs(data->ray.y1 - data->player->pos_y), 2));
	return (0);
}

int	raycast_y_wall(t_data *data, float dir_x, float dir_y)
{
	(void) dir_y;
	data->ray.x2 = (int)data->ray.pos_x;
	if (dir_x >= 0)
		data->ray.x2 += 1;
	data->ray.y2 = (data->ray.x2 - data->ray.pos_x) * tan(data->player->a) + data->ray.pos_y;
	data->wall2 = sqrt(pow(fabs(data->ray.x2 - data->player->pos_x), 2) + pow(fabs(data->ray.y2 - data->player->pos_y), 2));
	while (data->wall == 0)
	return (0);
}

int	raycast(t_data *data, float dir_x, float dir_y)
{
	raycast_x_wall(data, dir_x, dir_y);
	raycast_y_wall(data, dir_x, dir_y);
	
	//data->wall1 = sqrt(pow(fabs(data->ray.x1 - data->player->pos_x), 2) + pow(fabs(data->ray.y1 - data->player->pos_y), 2));
	//data->wall2 = sqrt(pow(fabs(data->ray.x2 - data->player->pos_x), 2) + pow(fabs(data->ray.y2 - data->player->pos_y), 2));
	while (data->wall == 0)
		data->wall = wall_check(data, dir_x, dir_y);
	
	return (0);
}

int	move_player(t_data *data)
{
	if (data->player->move_f == 1)
	{
		data->player->pos_x += data->player->dir_x / 100;
		data->player->pos_y += data->player->dir_y / 100;
	}
	if (data->player->move_b == 1)
	{
		data->player->pos_x -= data->player->dir_x / 100;
		data->player->pos_y -= data->player->dir_y / 100;
	}
	if (data->player->move_r == 1)
	{
		data->player->pos_x -= data->player->dir_y / 100;
		data->player->pos_y += data->player->dir_x / 100;
	}
	if (data->player->move_l == 1)
	{
		data->player->pos_x += data->player->dir_y / 100;
		data->player->pos_y -= data->player->dir_x / 100;
	}
	if (data->player->rotate_l == 1)
	{
		data->player->a -= 0.01;
		if (data->player->a < 0)
			data->player->a += 2 * M_PI;
		data->player->dir_x = cos(data->player->a) * 5;
		data->player->dir_y = sin(data->player->a) * 5;
	}
	if (data->player->rotate_r == 1)
	{
		data->player->a += 0.01;
		if (data->player->a > 2 * M_PI)
			data->player->a -= 2 * M_PI;
		data->player->dir_x = cos(data->player->a) * 5;
		data->player->dir_y = sin(data->player->a) * 5;
	}
	data->ray.pos_x = data->player->pos_x;
	data->ray.pos_y = data->player->pos_y;
	return (0);
}

int	render(t_data *data)
{
	move_player(data);
	minimap(data);
	//while (data->wall == 0)
		raycast(data, data->player->dir_x, data->player->dir_y);
	play(data);
	data->wall = 0;
	data->ray.pos_x = data->player->pos_x;
	data->ray.pos_y = data->player->pos_y;
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
	render(data);
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
	while (y <= 32)
	{
		x = 0;
		while (x <= 32)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, x + (32 * i), y + (32 * j), color);
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

int	play(t_data *data)
{
	mlx_pixel_put(data->mlx, data->mlx_win, (data->player->pos_x) * 32, (data->player->pos_y) * 32, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x * 32 + 1, data->player->pos_y * 32, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x * 32 + 1, data->player->pos_y * 32 + 1, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x * 32 - 1, data->player->pos_y * 32, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x * 32 - 1, data->player->pos_y * 32 - 1, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x * 32 + 1, data->player->pos_y * 32 - 1, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x * 32 - 1, data->player->pos_y * 32 + 1, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x * 32, data->player->pos_y * 32 - 1, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x * 32, data->player->pos_y * 32 + 1, RED);
	
	mlx_pixel_put(data->mlx, data->mlx_win, (data->player->pos_x * 32) + (data->player->dir_x * 2),
		(data->player->pos_y * 32) + (data->player->dir_y * 2), GREEN);
	return (0);
}

int	mlx_type_shit(t_data *data)
{
	data->mlx_win = NULL;
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "cub3d");
	//if (!data->mlx_win)
		//truc
	render(data);
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
	data = malloc(sizeof(t_data));
	init(data);
	if (parsing(argv[1], data) == 0)
		return (1);
	mlx_type_shit(data);
	return (0);
}