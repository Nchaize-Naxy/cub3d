/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:17 by gyvergni          #+#    #+#             */
/*   Updated: 2024/08/29 10:58:37 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_extension(char *map_name)
{
	size_t  len;
	size_t  i;
	size_t  j;
	char    *extension;
	
	extension = ".cub";
	len = ft_strlen(map_name);
	if (len > 3)
	    i = len - 4;
	else
		return (0);
	j = 0;
	while (map_name[i])
	{
		if (map_name[i++] != extension[j++])
	        return (error("invalid map extension"), 1);
	}
	return (0);
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
	if (check_extension(map_name) == 1)
		return (1);
	return (0);
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
	if (handle_identifier(line, data) == 0)
		if (handle_map(line, data) == 0)
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
    if (check_name(map_name) == 0)
    {
		data->map_fd = open(map_name, O_RDONLY);
		if (data->map_fd == -1)
            return (error("error opening map file\n"), 0);
		if (read_file(data) == 0)
			return (0);
    }
	data->height = count_tab(data->map);
	if (check_map(data->map, data) == 0)
		return (free_tab(data->map), 0);
	return (1);
}

/* char	*parse_line(char *line)
{
	size_t	i;
	char	identifier[3];

	i = 0;
	while (line && line[i] && (line[i] == ' ') || is_alnum(line[i]))
	{
		while (line[i] == ' ')
			i++;
		if (is_alnum(line[i]))
		{
			identifier[0] = line[i];
			i++;
		}
		if (is_alnum(line[i]))
			identifier[1] = line[i];
		else if (line[i] == ' ')
			identifier[1] = '\0';
		else
			error("invalid character found in file");
		i++;
		identifier[2] = '\0';
	}
	return (identifier);
} */