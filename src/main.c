/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:34:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/17 14:20:03 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	raycast(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "cub3d");
	return (0);
}

int	main(int argc, char **argv)
{
	t_data *data;

	init(data);
	data = malloc(sizeof(t_data));
	data->player = malloc(sizeof(t_player));
	/*parsing(data)*/
	raycast(data);
	return (0);
}