/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:01:51 by nchaize-          #+#    #+#             */
/*   Updated: 2024/09/05 11:39:17 by gyvergni         ###   ########.fr       */
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
	data->player->m_x = 0;
	return (0);
}

int	init(t_data *data)
{
	if (init_textures(data) != 0)
		return (error("Memory allocation failure"), 1);
	data->map = NULL;
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (free_textures(data), 1);
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
	data->is_player = false;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free_textures(data), free(data->player), 1);
	return (0);
}

t_tx_info	*init_pole(t_data *data, int i)
{
	t_tx_info	*pole;

	pole = malloc(sizeof(t_tx_info));
	if (!pole)
	{
		if (i >= 1)
			free(data->textures->no);
		if (i >= 2)
			free(data->textures->so);
		if (i >= 3)
			free(data->textures->ea);
		return (NULL);
	}
	pole->i_create = -1;
	pole->info = NULL;
	pole->bits_px = 0;
	pole->size_line = 0;
	pole->endian = 0;
	pole->height = 0;
	pole->img = NULL;
	pole->width = 0;
	return (pole);
}

int	init_textures(t_data *data)
{
	data->textures = malloc(sizeof(t_textures));
	if (!data->textures)
		return (1);
	data->textures->floor_color = 0;
	data->textures->ceiling_color = 0;
	data->textures->no = init_pole(data, 0);
	if (!data->textures->no)
		return (free(data->textures), 1);
	data->textures->so = init_pole(data, 1);
	if (!data->textures->so)
		return (free(data->textures), 1);
	data->textures->ea = init_pole(data, 2);
	if (!data->textures->ea)
		return (free(data->textures), 1);
	data->textures->we = init_pole(data, 3);
	if (!data->textures->we)
		return (free(data->textures), 1);
	return (0);
}
