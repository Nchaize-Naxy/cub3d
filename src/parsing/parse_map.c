/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:40:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/07/25 11:43:55 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	handle_identifier(char *line, t_data *data)
{
	char **split;

	split = ft_split(line, ' ');
	if (count_tab(split) > 2)
		return (error("too many arguments found in a single line"), 0);
	if (!split || !split[0])
		return (0);
	else if (!ft_strncmp(split[0], ID_EA, 3))
		data->textures->E_path = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], ID_SO, 3))
		data->textures->S_path = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], ID_NO, 3))
		data->textures->N_path = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], ID_WE, 3))
		data->textures->W_path = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], ID_F, 2))
		data->textures->Floor_color = conv_rgb(ft_strdup(split[1]));
	else if (!ft_strncmp(split[0], ID_C, 2))
		data->textures->Ceiling_color = conv_rgb(ft_strdup(split[1]));
	else if (is_valid_ch(split[0][0]) || split[0][0] == ' ' || split[0][0] == '1')
	{
		free_tab(split);
		return (0);
	}
	free_tab(split);
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
	printf("Hex number 1 is: %s\n", hex_nbr);
	hex_nbr = ft_strjoin(hex_nbr, ft_convert_base(rgb_split[1], tenbase, hexbase));
	printf("Hex number 2 is: %s\n", hex_nbr);
	hex_nbr = ft_strjoin(hex_nbr, ft_convert_base(rgb_split[2], tenbase, hexbase));
	printf("Hex number 3 is: %s\n", hex_nbr);
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
		printf("New map line %zu is %s\n", i, new_map[i]);
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
		printf("Line is %s\n", line);
		data->map = append_line(data->map, line, data);
		print_map(data->map);	
		line = get_next_line(data->map_fd);
	}
	return (1);
}