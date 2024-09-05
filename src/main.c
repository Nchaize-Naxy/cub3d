/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:34:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/09/05 11:38:11 by gyvergni         ###   ########.fr       */
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
		return (mlx_destroy_window(data->mlx, data->mlx_win), 1);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	if (!data->img.addr)
		return (mlx_destroy_window(data->mlx, data->mlx_win),
			mlx_destroy_image(data->mlx, data->img.img), 1);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img.img);
	return (0);
}

void	free_textures(t_data *data)
{
	free(data->textures->ea);
	free(data->textures->so);
	free(data->textures->no);
	free(data->textures->we);
	free(data->textures);
}

void	free_data(t_data *data, int do_free_txt)
{
	if (data->textures && do_free_txt != 1)
		destroy_textures(data);
	free_textures(data);
	if (data->player)
		free(data->player);
	if (data->map)
		free_tab(data->map);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data)
		free(data);
}

void	destroy_textures(t_data *data)
{
	mlx_destroy_image(data->mlx, data->textures->ea->img);
	mlx_destroy_image(data->mlx, data->textures->so->img);
	mlx_destroy_image(data->mlx, data->textures->no->img);
	mlx_destroy_image(data->mlx, data->textures->we->img);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		ret_parsing;

	if (argc > 2)
		return (error("Too many arguments"), 1);
	if (argc == 1)
		return (error("Not enough arguments"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (error("An error has occured"), 1);
	if (init(data) != 0)
		return (free(data), 1);
	ret_parsing = parsing(argv[1], data);
	if (ret_parsing != 0)
		return (free_data(data, ret_parsing), 1);
	if (mlx_booting(data) != 0)
		return (free_data(data, 0), error("An error has occured"), 1);
	free_data(data, 0);
	return (0);
}
