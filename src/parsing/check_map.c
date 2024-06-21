/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:56:40 by gyvergni          #+#    #+#             */
/*   Updated: 2024/06/21 15:07:21 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_ch(char c)
{
	if (c != '0' && c != 'N' &&
		c != 'S' && c != 'W' && c != 'E' && c != ' ')
		return (0);
	return (1);
}

int	check_empty(char **map, int line, int col, t_data *data)
{
	int	x;

	x = 0;
	while ((line + x <= (int) data->height) && (is_valid_ch(map[line + x][col])))
	{
		x++;
		if (map[line + x][col] != '1' || map[line + x][col] != ' ')
			return (error("map has non-closed empty spaces"), 0);
	}
	x = 0;
	while ((line - x >= 0) && (is_valid_ch(map[line - x][col])))
	{
		x++;
		if (map[line - x][col] != '1' || map[line - x][col] != ' ')
			return (error("map has non-closed empty spaces"), 0);
	}
	x = 0;
	while ((col + x != '\0') && (is_valid_ch(map[line][col + x])))
	{
		x++;
		if (map[line][col + x] == ' ')
			continue;
		else if (map[line][col + x] == '1')
			break;
		if (map[line][col + x] != '1' || map[line][col + x] != ' ')
			return (error("map has non-closed empty spaces"), 0);
	}
	x = 0;
	while ((col - x >= 0) && (is_valid_ch(map[line][col - x])))
	{
		x++;
		if (map[line][col - x] == ' ')
			continue;
		else if (map[line][col - x] == '1')
			break;
		else
			return (error("map has non-closed empty spaces"), 0);
	}
	return (1);
}

/* int	find_wall_line(t_data *data, int line, int col)
{
	int i;
	int	count;
	
	count = 0;
	i = col;
	while (i > 0)
	{
		if (data->map[line][i--] == '1')
			count++;
	}
	i = col;
	while (data->map[line][i] <= data->height)
	{
		if (data->map[line][i++] == '1')
			count++;
	}
	if (count == 2)
		return (1);
	return (0);
}

int find_wall_column(t_data *data, int line, int col)
{
	int i;
	int	count;
	
	count = 0;
	i = line;
	while (i > 0)
	{
		if (data->map[i--][col] == '1')
			count++;
	}
	i = col;
	while (data->map[line][i] <= data->height)
	{
		if (data->map[line][col] == '1')
			count++;
	}
	if (count == 2)
		return (1);
	return (0);
}
 */

/* int	check_walls(t_data *data, char *line, int i)
{
	char 	**line_split;
	int		j;

	line_split = ft_split(line, ' ');
	if (!line_split)
		return (error("memory allocation problem"), 0);
	if (i == 0 || i == data->height)
	{
		j = 0;
		while (line[j])
		{
			if (i == 0)
				if ((line[j] != '1' && line[j] != ' ') || (line[j] == ' ' && map[i + 1]))
		}	
	}
	if (line_split[0] && line_split[0][0] != '1' || ())
} */

int	check_map(char **map, t_data *data)
{
	int line;
	int	col;

	line = 0;
	col = 0;
	while (map && map[line])
	{
		col = 0;
/* 		if (check_walls(data, map[line], line) == 0)
			return (error("map not closed by walls"), 0); */
		while (map && map[line][col])
		{
			if (!is_valid_ch(map[line][col]) && map[line][col] != '1')
				return (error("invalid character found in map"), 0);
			if (map[line][col] == ' ')
			{
				if (check_empty(map, line, col, data) == 0)
					return (0);
			}
			col++;
		}
		line++;
	}
	return (1);
}
