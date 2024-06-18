/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:56:40 by gyvergni          #+#    #+#             */
/*   Updated: 2024/06/18 20:00:39 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_ch(char c)
{
	if (c != '0' && c != 'N' &&
		c != 'S' && c != 'W' && c != 'E')
		return (0);
	return (1);
}

int	check_empty(char **map, size_t line, size_t col, t_data *data)
{
	size_t	x;

	x = 0;
	while ((line + x <= data->height) && (is_valid_ch(map[line + x][col])))
	{
		x++;
		if (map[line + x][col] == '\0')
			return (error("map has non-closed empty spaces"), 0);
	}
	x = 0;
	while ((line - x >= 0) && (is_valid_ch(map[line - x][col])))
	{
		x++;
		if (map[line - x][col] == '\0')
			return (error("map has non-closed empty spaces"), 0);
	}
	while ((col + x <= data->length) && (is_valid_ch(map[line][col + x])))
	{
		x++;
		if (map[line][col + x] == '\0')
			return (error("map has non-closed empty spaces"), 0);
	}
	while ((col - x >= 0) && (is_valid_ch(map[line][col - x])))
	{
		x++;
		if (map[line][col - x] == '\0')
			return (error("map has non-closed empty spaces"), 0);
	}
}

int	check_map(char **map, t_data *data)
{
	size_t line;
	size_t	col;

	line = 0;
	col = 0;
	while (map[line])
	{
		while (map[line][col])
		{
			if (!is_valid_ch(map[line][col]) && map[line][col] != '1')
				return (error("invalid character found in map"), 0);
			if (map[line][col] != '1')
			{
				check_empty(map, line, col, data);
			}
		}
	}
}
