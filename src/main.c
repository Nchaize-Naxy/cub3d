/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:34:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/18 14:32:15 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(int keysym, t_data *data)
{
	(void) data;
	if (keysym == XK_Escape)
		exit(0);
	if (keysym == XK_w || keysym == XK_Up)
	{
		data->player->pos_x += 0;
		data->player->pos_y -= 3;
		minimap(data);
		play(data);
	}
	else if (keysym == XK_a || keysym == XK_Left)
	{
		data->player->pos_x -= 3;
		data->player->pos_y += 0;
		minimap(data);
		play(data);
	}
	else if (keysym == XK_d || keysym == XK_Right)
	{
		data->player->pos_x += 3;
		data->player->pos_y += 0;
		minimap(data);
		play(data);
	}	
	else if (keysym == XK_s || keysym == XK_Down)
	{
		data->player->pos_x += 0;
		data->player->pos_y += 3;
		minimap(data);
		play(data);
	}
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
				putcase(data, i, j, WHITE);
			else
				putcase(data, i, j, BLACK);
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
	return (0);
}

int	raycast(t_data *data)
{
	data->mlx_win = NULL;
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "cub3d");
	//if (!data->mlx_win)
		//truc
	minimap(data);
	play(data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_input, data);
	mlx_hook(data->mlx_win, DestroyNotify, StructureNotifyMask,
		&on_destroy, data);
	mlx_loop(data->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data *data;

	(void) argc;
	(void) argv;
	data = malloc(sizeof(t_data));
	init(data);
	/*parsing(data)*/
	raycast(data);
	return (0);
}