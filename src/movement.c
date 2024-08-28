/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:06:16 by pinkdonkeyj       #+#    #+#             */
/*   Updated: 2024/08/28 09:08:48 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	move_mouse(t_data *data, int *x, int *y)
{
	*x = 0;
	*y = 0;
	mlx_mouse_get_pos(data->mlx, data->mlx_win, x, y);
	mlx_mouse_move(data->mlx, data->mlx_win, WINWIDTH / 2, WINHEIGHT / 2);
	return (0);
}

int	move_player(t_data *data)
{
	int	x;
	int	y;
	float	move_x;
	float	move_y;
	
	move_x = data->player->dir_x * 5 / 100;
	move_y = data->player->dir_y * 5 / 100;
	move_mouse(data, &x, &y);
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
	if (data->player->m_x != x && data->player->m_x != 0)
	{
		data->player->a -= (data->player->m_x - x) * 0.00085;
		if (data->player->a > 2 * M_PI)
			data->player->a -= 2 * M_PI;
		data->player->dir_x = cos(data->player->a);
		data->player->dir_y = sin(data->player->a);
	}
	mlx_mouse_get_pos(data->mlx, data->mlx_win, &x, &y);
	data->player->m_x = x;
	data->ray.pos_x = data->player->pos_x;
	data->ray.pos_y = data->player->pos_y;
	return (0);
}
