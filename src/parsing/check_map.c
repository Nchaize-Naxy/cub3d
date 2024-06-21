/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:56:40 by gyvergni          #+#    #+#             */
/*   Updated: 2024/06/20 18:07:55 by pinkdonkeyj      ###   ########.fr       */
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
		if (map[line][col + x] != '1' || map[line][col + x] != ' ')
			return (error("map has non-closed empty spaces"), 0);
	}
	x = 0;
	while ((col - x >= 0) && (is_valid_ch(map[line][col - x])))
	{
		x++;
		if (map[line][col - x] != '1' || map[line][col - x] != ' ')
			return (error("map has non-closed empty spaces"), 0);
	}
	return (1);
}

int	check_map(char **map, t_data *data)
{
	int line;
	int	col;

	line = 0;
	col = 0;
	while (map && map[line])
	{
		col = 0;
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
