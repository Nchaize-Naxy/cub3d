/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:01:51 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/25 17:58:16 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init(t_data *data)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	textures->N_path = NULL;
	textures->S_path = NULL;
	textures->W_path = NULL;
	textures->E_path = NULL;
	textures->Floor_color = NULL;
	textures->Ceiling_color = NULL;
	data->map = NULL;
	data->player = malloc(sizeof(t_player));
	data->mlx = mlx_init();
	data->textures = textures;
	data->player->pos_x = 2.5;
	data->player->pos_y = 2.5;
	data->player->a = 0;
	data->player->dir_x = cos(data->player->a) * 5;
	data->player->dir_y = sin(data->player->a) * 5;
	data->exit = false;
	data->ray.x1 = 0;
	data->ray.y1 = 0;
	data->ray.x2 = 0;
	data->ray.y2 = 0;
	data->ray.pos_x = data->player->pos_x;
	data->ray.pos_y = data->player->pos_y;
	
/* 	data->map = malloc(sizeof(char *) * 7);
	data->map[0] = "111111";
	data->map[1] = "100001";
	data->map[2] = "100001";
	data->map[3] = "100001";
	data->map[4] = "100001";
	data->map[5] = "111111";
	data->map[6] = NULL; */
	
	
	return (0);
}
