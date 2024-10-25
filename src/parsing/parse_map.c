/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:40:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/10/25 14:40:08 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture(t_data *data, t_tx_info *texture, char *file)
{
	if (check_extension(file, ".xpm") != 0)
		return (destroy(data), \
			error("Error: Texture files must be .xpm"), 1);
	if (access(file, R_OK) == -1)
		return (destroy(data), \
			error("Cannot access texture file"), 1);
	texture->img = mlx_xpm_file_to_image(data->mlx, file, \
		&(texture->width), &(texture->height));
	if (!texture->img)
	{
		error("xpm file has invalid content");
		return (1);
	}
	texture->info = (int *)mlx_get_data_addr(texture->img, &(texture->bits_px), \
		&(texture->size_line), &(texture->endian));
	texture->i_create = 0;
	return (0);
}

int	assign_textures(t_data *data, char *file, char **split)
{
	if (!ft_strcmp(split[0], ID_WE))
		return (get_texture(data, data->textures->we, file));
	else if (!ft_strcmp(split[0], ID_NO))
		return (get_texture(data, data->textures->no, file));
	else if (!ft_strcmp(split[0], ID_SO))
		return (get_texture(data, data->textures->so, file));
	else if (split && split[0] && !ft_strcmp(split[0], ID_EA))
		return (get_texture(data, data->textures->ea, file));
	else if (!ft_strcmp(split[0], ID_F))
	{
		data->textures->floor_color = conv_rgb(file, "0123456789ABCDEF");
		return (0);
	}
	else if (!ft_strcmp(split[0], ID_C))
	{
		data->textures->ceiling_color = conv_rgb(file, "0123456789ABCDEF");
		return (0);
	}
	else if (split[0][0] == ' ' || split[0][0] == '1')
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
		return (destroy(data), 1);
	if (count_tab(split) > 2)
		return (free_tab(split), destroy(data), error("Indentifier error"), 1);
	if (split[0] && split[0][0] != '\n' && split[0][0] != 'C' &&
		split[0][0] != 'F' && split[0][0] != '1' && !(is_valid_ch(split[0][0])))
		return (error("Invalid line"), destroy(data), free_tab(split), 1);
	file = no_back_n(split);
	if (!file || file == NULL)
		return (free_tab(split), destroy(data), 1);
	ret = assign_textures(data, file, split);
	free(file);
	return (free_tab(split), ret);
}

char	**append_line(char **map, char *line, t_data *data)
{
	size_t	i;
	char	**new_map;

	(void) line;
	i = 0;
	new_map = malloc(sizeof(char *) * (count_tab(map) + 2));
	if (!new_map)
		return (NULL);
	while (map && map[i])
	{
		new_map[i] = dup_map_row(map[i]);
		if (!new_map[i])
			return (free_tab(map), free_tab(new_map), NULL);
		else if (check_map_line(new_map[i]) != 0)
			return (free_tab(map), free_new_map(new_map, i), NULL);
		i++;
	}
	free_tab(map);
	new_map[i] = dup_map_row(line);
	if (new_map[i] == NULL)
		return (free_tab(new_map), NULL);
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
		if (line[0] == '\n' || line[0] == '\0')
			return (free(line), error("invalid line in map"), 1);
		data->map = append_line(data->map, line, data);
		if (!data->map)
			return (free(line), error("failed to create map"), 1);
		free(line);
		line = get_next_line(data->map_fd);
	}
	return (0);
}
