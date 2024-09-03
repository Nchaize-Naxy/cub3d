/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:40:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/09/03 18:49:39 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*no_back_n(char *string)
{
	size_t	i;
	char	*new_string;

	i = 0;
	new_string = "a\0";
	while (string && string[i])
	{
		if (string[i] == '\n')
		{
			new_string = NULL;
			new_string = ft_strndup(string, i);
			if (!new_string || new_string == NULL)
				return (NULL);
		}
		i++;
	}
	return (new_string);
}

int	get_texture(t_data *data, t_tx_info *texture, char *file)
{
	if (check_extension(file, ".xpm") == 0)
		return (error("Wrong extension on texture files. Need .xpm"), 0);
	texture->img = mlx_xpm_file_to_image(data->mlx, file, &(texture->width), &(texture->height));
	texture->info = (int *)mlx_get_data_addr(texture->img, &(texture->bits_px), &(texture->size_line), &(texture->endian));
	free (file);
	return (1);
}

int	handle_identifier(char *line, t_data *data)
{
	char **split;
	char	*file;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	if (count_tab(split) > 2)
		return (free_tab(split), error("too many arguments found in a single line"), 0);
	if (!split || !split[0])
		return (0);
	file = no_back_n(split[1]);
	if (!file || file == NULL)
		return (free_tab(split), 0);
	if (split && split[0] && !ft_strncmp(split[0], ID_EA, 2))
		return (free_tab(split), get_texture(data, data->textures->EA, file));
	else if (!ft_strncmp(split[0], ID_SO, 2))
		return (free_tab(split), get_texture(data, data->textures->SO, file));
	else if (!ft_strncmp(split[0], ID_NO, 2))
		return (free_tab(split), get_texture(data, data->textures->NO, file));
	else if (!ft_strncmp(split[0], ID_WE, 2))
		return (free_tab(split), get_texture(data, data->textures->WE, file));
	else if (!ft_strncmp(split[0], ID_F, 1))
		data->textures->Floor_color = conv_rgb(file);
	else if (!ft_strncmp(split[0], ID_C, 1))
		data->textures->Ceiling_color = conv_rgb(file);
	else if (is_valid_ch(split[0][0]) || split[0][0] == ' ' || split[0][0] == '1')
		return (free_tab(split), 2);
	return (free_tab(split), 1);
}

int	conv_rgb(char *rgb)
{
	char	**rgb_split;
	char	*hex_nbr;
	char	*hexbase;
	char	*tenbase;
	int		int_value;
	char	*temp;

	tenbase = "0123456789";
	hexbase = "0123456789ABCDEF";
	rgb_split = ft_split(rgb, ',');
	free (rgb);
	if (!rgb_split)
		return (0);
	hex_nbr = ft_convert_base(rgb_split[0], tenbase, hexbase);
	if (!hex_nbr)
		return (free_tab(rgb_split), 0);
	hex_nbr = ft_strjoin_update(hex_nbr, ft_convert_base(rgb_split[1], tenbase, hexbase));
	if (!hex_nbr)
		return (free_tab(rgb_split), 0);
	hex_nbr = ft_strjoin_update(hex_nbr, ft_convert_base(rgb_split[2], tenbase, hexbase));
	if (!hex_nbr)
		return (free_tab(rgb_split), 0);
	temp = ft_convert_base(hex_nbr, hexbase, tenbase);
	int_value = atoi(temp);
	free(temp);
	free(hex_nbr);
	return (free_tab(rgb_split), int_value);
}

int	check_map_line(char *line)
{
	if (!line || line[0] == '\0')
		return (error("empty line"), 0);
	return (1);
}

char	**append_line(char **map, char *line, t_data *data)
{
	size_t	i;
	char **new_map;
	
	i = 0;
	new_map = malloc(sizeof(char *) * (count_tab(map) + 2));
	if (!new_map)
		return (NULL);
	while (map && map[i])
	{
		new_map[i] = dup_map_row(map[i]);
		if (new_map[i] == NULL)
			return(free_tab(map), free_tab(new_map), \
				error("Memory allocation problem encountered while parsing map\n"), NULL);
		if (check_map_line(new_map[i]) == 0)
			return (free_tab(map), free_tab(new_map), NULL);
		free(map[i]);
		i++;
	}
	free(map);
	new_map[i] = dup_map_row(line);
	if (new_map[i] == NULL)
		return (free_tab(new_map), error("memory allocation problem encountered"), NULL);
	new_map[i + 1] = NULL;
	data->map = new_map;
	return (new_map);
}

int	handle_map(char *line, t_data *data)
{
	if (!line)
		return (0);
	while (line != NULL)
	{
		data->map = append_line(data->map, line, data);
		if (!data->map)
			return (free(line), error("failed to create map"), 0);
		free(line);
		line = get_next_line(data->map_fd);
	}
	return (1);
}
