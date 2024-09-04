/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:34:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/09/04 11:34:39 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mlx_booting(t_data *data)
{
	data->mlx_win = NULL;
	data->mlx_win = mlx_new_window(data->mlx, WINWIDTH, WINHEIGHT, "cub3d");
	if (!data->mlx_win)
		return (1);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_input, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, &release_handler, data);
	mlx_hook(data->mlx_win, DestroyNotify, StructureNotifyMask,
		&on_destroy, data);
	mlx_mouse_hide(data->mlx, data->mlx_win);
	data->img.img = mlx_new_image(data->mlx, WINWIDTH, WINHEIGHT);
	if (!data->img.img)
		return (free(data->mlx_win), 1);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	if (!data->img.addr)
		return (free(data->mlx_win), free(data->img.img), 1);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img.img);
	return (0);
}

void	free_data(t_data *data)
{
	free_tab(data->map);
	free(data->textures->EA);
	free(data->textures->SO);
	free(data->textures->NO);
	free(data->textures->WE);
	free(data->textures);
	free(data->player);
	free(data);
}

void	free_textures(t_data *data)
{
	mlx_destroy_image(data->mlx, data->textures->EA->img);
	mlx_destroy_image(data->mlx, data->textures->SO->img);
	mlx_destroy_image(data->mlx, data->textures->NO->img);
	mlx_destroy_image(data->mlx, data->textures->WE->img);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc > 2)
		return (error("Too many arguments"), 1);
	if (argc == 1)
		return (error("Not enough arguments"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (error("An error has occured"), 1);
	if (init(data) != 0)
		return (free(data), 1);
	if (parsing(argv[1], data) == 0)
		return (free_data(data), 1);
	if (mlx_booting(data) != 0)
		return (free_data(data), error("An error has occured"), 1);
	free_textures(data);
	free_data(data);
	return (0);
}
