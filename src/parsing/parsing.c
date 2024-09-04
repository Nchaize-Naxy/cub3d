/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:17 by gyvergni          #+#    #+#             */
/*   Updated: 2024/09/04 11:16:53 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_extension(char *map_name, char *extension)
{
	size_t  len;
	size_t  i;
	size_t  j;

	len = ft_strlen(map_name);
	if (len > 3)
	    i = len - 4;
	else
		return (0);
	j = 0;
	while (map_name[i])
	{
		if (map_name[i++] != extension[j++])
	        return (0);
	}
	return (1);
}

int check_name(char *map_name)
{
/*	size_t  i;	
	
	i = 0;
 	while (map_name && map_name[i])
	{
	    if (!is_alnum(map_name[i]) || map_name[i] != 32)
	        return (error("invalid map name"), 1);
	    i++;
	} */
	if (check_extension(map_name, ".cub") == 0)
		return (error("Invalid map extension. Need .cub"), 0);
	return (1);
}

size_t	count_tab(char **tab)
{
	size_t n;

	n = 0;
	while (tab && tab[n])
		n++;
	return (n);
}

int		free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}


int	parse_line(char *line, t_data *data)
{
	int	check;

	check = handle_identifier(line, data);
	if (check == 2)
	{
		if (handle_map(line, data) == 0)
			return (0);
		if (check == 0)
			return (0);
		return (1);
	}
	free(line);
	if (check == 0)
		return (0);
	return (1);
}

int read_file(t_data *data)
{
    char *line;
	
    line = get_next_line(data->map_fd);
    while (line != NULL)
    {	
		if (parse_line(line, data) == 0)
			return (0);
		line = get_next_line(data->map_fd);
    }
	return (1);
}

int parsing(char *map_name, t_data *data)
{
    if (check_name(map_name) == 1)
    {
		data->map_fd = open(map_name, O_RDONLY);
		if (data->map_fd == -1)
            return (error("error opening map file\n"), 0);
		if (read_file(data) == 0)
			return (0);
    }
	data->height = count_tab(data->map);
	if (check_map(data->map, data) == 0)
		return (0);
	return (1);
}
