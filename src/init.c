/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:01:51 by nchaize-          #+#    #+#             */
/*   Updated: 2024/07/30 13:43:29 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_player(t_data *data)
{
	data->player->pos_x = 0;
	data->player->pos_y = 0;
	data->player->a = 0;
	data->player->dir_x = cos(data->player->a);
	data->player->dir_y = sin(data->player->a);
	data->player->move_f = 0;
	data->player->move_b = 0;
	data->player->move_r = 0;
	data->player->move_l = 0;
	data->player->rotate_r = 0;
	data->player->rotate_l = 0;
	return (0);
}

int	init(t_data *data)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	textures->NO = NULL;
	textures->SO = NULL;
	textures->EA = NULL;
	textures->WE = NULL;
	textures->Floor_color = 0;
	textures->Ceiling_color = 0;
	data->textures = textures;
	init_textures(data);
	data->map = NULL;
	data->player = malloc(sizeof(t_player));
	data->mlx = mlx_init();
	init_player(data);
	data->exit = false;
	data->wall = 0;
	data->wall1 = 0;
	data->wall2 = 0;
	data->ray.x1 = data->player->pos_x;
	data->ray.y1 = data->player->pos_y;
	data->ray.x2 = data->player->pos_x;
	data->ray.y2 = data->player->pos_y;
	data->ray.pos_x = data->player->pos_x;
	data->ray.pos_y = data->player->pos_y;
	data->ray.wall_x = data->player->pos_x;
	data->ray.wall_y = data->player->pos_y;
	
	return (0);
}

int	init_textures(t_data *data)
{
	data->textures->NO = malloc(sizeof(t_tx_info));
	data->textures->SO = malloc(sizeof(t_tx_info));
	data->textures->EA = malloc(sizeof(t_tx_info));
	data->textures->WE = malloc(sizeof(t_tx_info));
	return (0);
}