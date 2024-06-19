/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:17 by gyvergni          #+#    #+#             */
/*   Updated: 2024/06/18 20:52:04 by pinkdonkeyj      ###   ########.fr       */
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
    j = 0;
    while (map_name[i])
    {
        if (map_name[i] != extension[j])
            return (error("invalid map extension"), 1);
    }
    return (0);
    
}

int check_name(char *map_name)
{
    size_t  i;

    i = 0;
    while (map_name && map_name[i])
    {
        if (!is_alnum(map_name[i]) || map_name[i] != 32)
            return (error("invalid map name"), 1);
        i++;
    }
    if (check_extension(map_name) == 1)
        return (1);
    return (0);
}

size_t	count_split(char **split)
{
	size_t n;

	n = 0;
	while (split && split[n])
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

int	handle_identifier(char *line, t_data *data)
{
	char **split;

	split = ft_split(line, ' ');
	if (count_split(split) > 2)
		return (error("too many arguments found in a single line"), 0);
	if (!split || !split[0])
		return (0);
	else if (!strncmp(split[0], ID_EA, 3))
		data->textures->E_path = split[1];
	else if (!strncmp(split[0], ID_SO, 3))
		data->textures->S_path = split[1];
	else if (!strncmp(split[0], ID_NO, 3))
		data->textures->N_path = split[1];
	else if (!strncmp(split[0], ID_WE, 3))
		data->textures->W_path = split[1];
	else if (!strncmp(split[0], ID_F, 2))
		data->textures->Floor_color = split[1];
	else if (!strncmp(split[0], ID_C, 2))
		data->textures->Ceiling_color = split[1];
	else
	{
		free_tab(split);
		return (0);
	}
	free_tab(split);
	return (1);
}

int	check_map_line(char *line)
{
	size_t	i;

	i = 0;
	while (line && line[i])
	{
		if (!is_valid_ch(line[i]) && line[i] != '1')
			return (error("invalid character found in map"), 0);
		i++;
	}
	return (1);
}

int	handle_map(char *line, t_data *data)
{
	size_t	i = 0;
	size_t	height;
	size_t	length;

	measure_map(data);
	if (!line)
		return (0);
	while (line != NULL)
	{
		check_map_line(line);
		data->map[i] = ft_strdup(line);
		if (data->map[i] == NULL)
			return (error("memory allocation problem encountered"), 0);
		line = get_next_line(data->map_fd);
	}
	return (1);
}

int	parse_line(char *line, t_data *data)
{
	if (handle_identifier(line, data) == 0)
		handle_map(line, data);
	return (1);
}

int read_file(t_data *data)
{
    char *line;

    line = get_next_line(data->map_fd);
    while (line != NULL)
    {
		parse_line(line, data);
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
            return (error("error opening map file\n"), 1);
		read_file(data);
    }
    check_walls(map_name);
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