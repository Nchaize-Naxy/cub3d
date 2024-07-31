/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:40:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/07/31 20:24:55 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*no_back_n(char *string)
{
	size_t	i;

	i = 0;
	while (string && string[i])
	{
		if (string[i] == '\n')
			return (ft_strndup(string, i));
		i++;
	}
	return (string);
}

int	handle_identifier(char *line, t_data *data)
{
	char **split;
	t_tx_info	*texture;
	char	*file;

	split = ft_split(line, ' ');
	file = no_back_n(split[1]);
	if (count_tab(split) > 2)
		return (error("too many arguments found in a single line"), 0);
	if (!split || !split[0])
		return (0);
	else if (split && split[0] && !ft_strncmp(split[0], ID_EA, 2))
	{
		texture = data->textures->EA;
		texture->img = mlx_xpm_file_to_image(data->mlx, "metalsheets.xpm", &(texture->width), &(texture->height));
		texture->info = mlx_get_data_addr(texture->img, &(texture->bits_px), &(texture->size_line), &(texture->endian));
		write(1, "f\n", 2);
	}
	else if (!ft_strncmp(split[0], ID_SO, 2))
	{
		texture = data->textures->SO;
		texture->img = mlx_xpm_file_to_image(data->mlx, file, &(texture->width), &(texture->height));
		texture->info = mlx_get_data_addr(texture->img, &(texture->bits_px), &(texture->size_line), &(texture->endian));
	}
	else if (!ft_strncmp(split[0], ID_NO, 2))
	{
		texture = data->textures->NO;
		texture->img = mlx_xpm_file_to_image(data->mlx, file, &(texture->width), &(texture->height));
		texture->info = mlx_get_data_addr(texture->img, &(texture->bits_px), &(texture->size_line), &(texture->endian));
	}
	else if (!ft_strncmp(split[0], ID_WE, 2))
	{
		texture = data->textures->WE;
		texture->img = mlx_xpm_file_to_image(data->mlx, file, &(texture->width), &(texture->height));
		texture->info = mlx_get_data_addr(texture->img, &(texture->bits_px), &(texture->size_line), &(texture->endian));
	}
	else if (!ft_strncmp(split[0], ID_F, 1))
		data->textures->Floor_color = conv_rgb(file);
	else if (!ft_strncmp(split[0], ID_C, 1))
		data->textures->Ceiling_color = conv_rgb(file);
	else if (is_valid_ch(split[0][0]) || split[0][0] == ' ' || split[0][0] == '1')
	{
		free_tab(split);
		free(file);
		return (0);
	}
	free_tab(split);
	free(file);
	return (1);
}

int	conv_rgb(char *rgb)
{
	char **rgb_split;
	char *hex_nbr;
	char *hexbase;
	char *tenbase;

	tenbase = "0123456789";
	hexbase = "0123456789ABCDEF";
	rgb_split = ft_split(rgb, ',');
	if (!rgb_split)
		return (0);
	hex_nbr = ft_convert_base(rgb_split[0], tenbase, hexbase);
	hex_nbr = ft_strjoin(hex_nbr, ft_convert_base(rgb_split[1], tenbase, hexbase));
	hex_nbr = ft_strjoin(hex_nbr, ft_convert_base(rgb_split[2], tenbase, hexbase));
	return (atoi(ft_convert_base(hex_nbr, hexbase, tenbase)));
}

int	check_map_line(char *line)
{
	size_t	i;

	i = 0;
	if (!line || line[0] == '\0')
		return (error("empty line"), 0);
	while (line && line[i])
	{
		if (!is_valid_ch(line[i]) && line[i] != '1')
			return (error("invalid character found in map"), 0);
		i++;
	}
	return (1);
}

char	**append_line(char **map, char *line, t_data *data)
{
	size_t	i;
	char **new_map;
	
	write(1, "a\n", 2);
	i = 0;
	new_map = malloc(sizeof(char *) * (count_tab(map) + 2));
	while (map && map[i])
	{
		new_map[i] = dup_map_row(map[i]);
		if (check_map_line(new_map[i]) == 0)
			return (NULL);
		free(map[i]);
		if (new_map[i] == NULL)
			return (error("memory allocation problem encountered"), NULL);
		i++;
	}
	new_map[i] = dup_map_row(line);
	if (new_map[i] == NULL)
		return (error("memory allocation problem encountered"), NULL);
	new_map[i + 1] = NULL;
	free(map);
	data->map = new_map;
	return (new_map);
}

void	print_map(char **map)
{
	int i;

	i = 0;
	while (map && map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	handle_map(char *line, t_data *data)
{
	if (!line)
		return (0);
	while (line != NULL)
	{
		data->map = append_line(data->map, line, data);
		print_map(data->map);	
		line = get_next_line(data->map_fd);
	}
	return (1);
}