/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:34:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/20 16:10:50 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		data->player->pos_x -= data->player->dir_x / 100;
		data->player->pos_y += data->player->dir_y / 100;
	}
	if (data->player->move_l == 1)
	{
		data->player->pos_x += data->player->dir_x / 100;
		data->player->pos_y += data->player->dir_y / 100;
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
	return (0);
}

int	render(t_data *data)
{
	move_player(data);
	minimap(data);
	play(data);
	return (0);
}


int	release_handler(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		data->exit = true;
	if (keysym == XK_w || keysym == XK_Up)
	{
		data->player->move_f = 0;
	}
	if (keysym == XK_a)
	{
		data->player->move_l = 0;
	}
	if (keysym == XK_d)
	{
		data->player->move_r = 0;
	}
	if (keysym == XK_Left)
	{
		data->player->rotate_l = 0;
	}
	if (keysym == XK_Right)
	{
		data->player->rotate_r = 0;
	}
	if (keysym == XK_s || keysym == XK_Down)
	{
		data->player->move_b = 0;
	}
	render(data);
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		data->exit = true;
	if (keysym == XK_w || keysym == XK_Up)
	{
		data->player->move_f = 1;
	}
	if (keysym == XK_a)
	{
		data->player->move_l = 1;
	}
	if (keysym == XK_d)
	{
		data->player->move_r = 1;
	}
	if (keysym == XK_Left)
	{
		data->player->rotate_l = 1;
	}
	if (keysym == XK_Right)
	{
		data->player->rotate_r = 1;
	}
	if (keysym == XK_s || keysym == XK_Down)
	{
		data->player->move_b = 1;
	}
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
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x, data->player->pos_y, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x + 1, data->player->pos_y, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x + 1, data->player->pos_y + 1, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x - 1, data->player->pos_y, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x - 1, data->player->pos_y - 1, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x + 1, data->player->pos_y - 1, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x - 1, data->player->pos_y + 1, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x, data->player->pos_y - 1, RED);
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x, data->player->pos_y + 1, RED);
	
	mlx_pixel_put(data->mlx, data->mlx_win, data->player->pos_x + (data->player->dir_x * 2),
		data->player->pos_y + (data->player->dir_y * 2), GREEN);
	return (0);
}

int	raycast(t_data *data)
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

	if (argc > 3)
		return (error("too many arguments"), 1);
	data = malloc(sizeof(t_data));
	init(data);
	if (parsing(argv[1], data) == 0)
		return (1);
	raycast(data);
	return (0);
}