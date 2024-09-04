/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:17 by gyvergni          #+#    #+#             */
/*   Updated: 2024/09/04 21:03:39 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	count_tab(char **tab)
{
	size_t	n;

	n = 0;
	while (tab && tab[n])
		n++;
	return (n);
}

int	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

int	parse_line(char *line, t_data *data)
{
	int	check;

	check = handle_identifier(line, data);
	if (check == 2)
	{
		if (handle_map(line, data) != 0)
			return (destroy_textures(data), 1);
		if (check == 1)
			return (1);
		return (0);
	}
	free(line);
	if (check == 1)
		return (1);
	return (0);
}

int	read_file(t_data *data)
{
	char	*line;

	line = get_next_line(data->map_fd);
	while (line != NULL)
	{
		if (parse_line(line, data) != 0)
			return (1);
		line = get_next_line(data->map_fd);
	}
	return (0);
}

int	parsing(char *map_name, t_data *data)
{
	if (check_name(map_name) == 0)
	{
		data->map_fd = open(map_name, O_RDONLY);
		if (data->map_fd == -1)
			return (error("error opening map file"), 1);
		if (read_file(data) != 0)
			return (1);
	}
	else
		return (1);
	data->height = count_tab(data->map);
	if (check_map(data->map, data) != 0)
		return (2);
	return (0);
}
