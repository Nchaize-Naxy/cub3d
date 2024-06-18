/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:17 by gyvergni          #+#    #+#             */
/*   Updated: 2024/06/17 15:22:42 by gyvergni         ###   ########.fr       */
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

int	handle_identifier(char **split, t_data *data)
{
	if (!split || !split[0])
		return (0);
	else if (!strncmp(split[0], ID_EA, 3))
		data->E_path = split[1];
	else if (!strncmp(split[0], ID_SW, 3))
		data->S_path = split[1];
	else if (!strncmp(split[0], ID_NO, 3))
		data->N_path = split[1];
	else if (!strncmp(split[0], ID_WE, 3))
		data->W_path = split[1];
	else if (!strncmp(split[0], ID_F, 2))
		data->Floor_color = split[1];
	else if (!strncmp(split[0], ID_C, 2))
		data->Ceiling_color = split[1];
	else
		return (0);
	return (1);
}

int	handle_map(char *line, t_data *data)
{
	static int	i = 0;

	if (!line)
		return (0);
	data->map[i] = ft_strdup(line);
	if (data->map[i] == NULL)
		return (error("memory allocation problem encountered"), 0);
}

char	*parse_line(char *line, t_data *data)
{
	char **line_split;

	line_split = ft_split(line);
	if (count_split(line_split) > 2)
		return (error("too many arguments found in a single line"), NULL);
	if (handle_identifier(line_split, data) == 0)
		handle_map(line, data);
}

int read_file(int fd, t_data *data)
{
    char *line;

    line = get_next_line(fd);
    while (line != NULL)
    {
		parse_line(line, data);
		line = get_next_line(fd);
    }
}

int parsing(char *map_name, int map_fd, t_data *data)
{
    int fd;
    
    if (check_name(map_name) == 0)
    {
        fd = open(map_name, O_RDONLY);
        if (fd == -1)
            return (error("error opening map file\n"), 1);
        read_file(fd);
    }
    check_walls(map_name);
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