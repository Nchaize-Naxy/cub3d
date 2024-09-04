/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:40:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/09/04 15:37:53 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture(t_data *data, t_tx_info *texture, char *file, int i)
{
	if (check_extension(file, ".xpm") != 0)
		return (free(file), destroy(data, i), \
			error("Error: Texture files must be .xpm"), 1);
	texture->img = mlx_xpm_file_to_image(data->mlx, file, \
		&(texture->width), &(texture->height));
	texture->info = (int *)mlx_get_data_addr(texture->img, &(texture->bits_px), \
		&(texture->size_line), &(texture->endian));
	free (file);
	return (0);
}

int	assign_textures(t_data *data, char *file, char **split)
{
	if (!ft_strncmp(split[0], ID_NO, 2))
		return (get_texture(data, data->textures->NO, file, 0));
	else if (!ft_strncmp(split[0], ID_SO, 2))
		return (get_texture(data, data->textures->SO, file, 1));
	else if (!ft_strncmp(split[0], ID_WE, 2))
		return (get_texture(data, data->textures->WE, file, 2));
	else if (split && split[0] && !ft_strncmp(split[0], ID_EA, 2))
		return (get_texture(data, data->textures->EA, file, 3));
	else if (!ft_strncmp(split[0], ID_F, 1))
	{
		data->textures->Floor_color = conv_rgb(file);
		return (0);
	}
	else if (!ft_strncmp(split[0], ID_C, 1))
	{
		data->textures->Ceiling_color = conv_rgb(file);
		return (0);
	}
	else if (is_valid_ch(split[0][0]) || split[0][0] == ' '
		|| split[0][0] == '1')
		return (2);
	else
		return (0);
}

int	handle_identifier(char *line, t_data *data)
{
	char	**split;
	char	*file;
	int		ret;

	split = ft_split(line, ' ');
	if (!split)
		return (1);
	if (count_tab(split) > 2)
		return (free_tab(split), error("Too many arguments for identifier"), 1);
	file = no_back_n(split[1]);
	if (!file || file == NULL)
		return (free_tab(split), 1);
	ret = assign_textures(data, file, split);
	return (free_tab(split), ret);
}

char	**append_line(char **map, char *line, t_data *data)
{
	size_t	i;
	char	**new_map;

	i = 0;
	new_map = malloc(sizeof(char *) * (count_tab(map) + 2));
	if (!new_map)
		return (NULL);
	while (map && map[i])
	{
		new_map[i] = dup_map_row(map[i]);
		if (new_map[i] == NULL)
			return (free_tab(map), free_tab(new_map), \
				error("Memory allocation failure during parsing"), NULL);
		if (check_map_line(new_map[i]) != 0)
			return (free_tab(map), free_tab(new_map), NULL);
		free(map[i]);
		i++;
	}
	free(map);
	new_map[i] = dup_map_row(line);
	if (new_map[i] == NULL)
		return (free_tab(new_map), error("memory allocation failure"), NULL);
	new_map[i + 1] = NULL;
	data->map = new_map;
	return (new_map);
}

int	handle_map(char *line, t_data *data)
{
	if (!line)
		return (1);
	while (line != NULL)
	{
		data->map = append_line(data->map, line, data);
		if (!data->map)
			return (free(line), error("failed to create map"), 1);
		free(line);
		line = get_next_line(data->map_fd);
	}
	return (0);
}
