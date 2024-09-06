/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:21:30 by nchaize-          #+#    #+#             */
/*   Updated: 2024/09/06 14:37:04 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_focus_out(t_data *data)
{
	data->player->free_mouse = 1;
	return (0);
}

int	on_focus_in(t_data *data)
{
	data->player->free_mouse = 0;
	return (0);
}

int	on_destroy(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	free_data(data, 0);
	exit(0);
	return (0);
}
