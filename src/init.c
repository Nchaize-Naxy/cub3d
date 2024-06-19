/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:01:51 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/19 16:48:14 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init(t_data *data)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	data->player = malloc(sizeof(t_player));
	data->mlx = mlx_init();
	data->textures = textures;
	data->player->pos_x = 80;
	data->player->pos_y = 80;
	data->player->dir_x = 0;
	data->player->dir_y = -1;
	data->player->a = 0;
	
	data->map = malloc(sizeof(char *) * 7);
	data->map[0] = "111111";
	data->map[1] = "100001";
	data->map[2] = "100001";
	data->map[3] = "100001";
	data->map[4] = "100001";
	data->map[5] = "111111";
	data->map[6] = NULL;
	
	
	return (0);
}
