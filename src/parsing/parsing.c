/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:17 by gyvergni          #+#    #+#             */
/*   Updated: 2024/06/20 18:08:40 by pinkdonkeyj      ###   ########.fr       */
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
		data->textures->Floor_color = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], ID_C, 2))
		data->textures->Ceiling_color = ft_strdup(split[1]);
	else if (is_valid_ch(split[0][0]) || split[0][0] == ' ' || split[0][0] == '1')
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
		check_map_line(new_map[i]);
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
	size_t i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	handle_map(char *line, t_data *data)
{
	size_t	i;

	i = 0;
	if (!line)
		return (0);
	while (line != NULL)
	{
		printf("Line is %s\n", line);
		data->map = append_line(data->map, line, data);
		line = get_next_line(data->map_fd);
		i++;
	}
	print_map(data->map);
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
        printf("map fd: %d\n", data->map_fd);
		printf("map name : %s\n", map_name);
		if (data->map_fd == -1)
            return (error("error opening map file\n"), 0);
		read_file(data);
    }
	data->height = count_tab(data->map);
	if (check_map(data->map, data) == 0)
	{
		write(1, "bono\n", 5);
		free_tab(data->map);
		return (0);
	}
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