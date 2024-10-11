/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:37:49 by gyvergni          #+#    #+#             */
/*   Updated: 2024/10/11 12:17:43 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_right(char **map, int line, int col, t_data *data, char space)
{
	int	x;

	x = 0;
	while ((line + x < (int) data->height) && (is_valid_ch(map[line + x][col])))
	{
		if (map[line + x][col] == space)
		{
			x++;
			continue ;
		}
		else if (map[line + x][col] == '1')
			break ;
		if (map[line + x][col] != '1' || map[line + x][col] != space)
			return (error("map has non-closed empty spaces"), 1);
		x++;
	}
	return (0);
}

int	check_left(char **map, int line, int col, char space)
{
	int	x;

	x = 0;
	while ((line - x >= 0) && (is_valid_ch(map[line - x][col])))
	{
		if (map[line - x][col] == space)
		{
			x++;
			continue ;
		}
		else if (map[line - x][col] == '1')
			break ;
		if (map[line - x][col] != '1' || map[line - x][col] != space)
			return (error("map has non-closed empty spaces"), 1);
		x++;
	}
	return (0);
}

int	check_up(char **map, int line, int col, char space)
{
	int	x;

	x = 0;
	while ((col - x >= 0) && (is_valid_ch(map[line][col - x])))
	{
		if (map[line][col - x] == space)
		{
			x++;
			continue ;
		}
		else if (map[line][col - x] == '1')
			break ;
		else
			return (error("map has non-closed empty spaces"), 1);
		x++;
	}
	return (0);
}

int	check_down(char **map, int line, int col, char space)
{
	int	x;

	x = 0;
	while ((col + x != '\0') && (is_valid_ch(map[line][col + x])))
	{
		if (map[line][col + x] == space)
		{
			x++;
			continue ;
		}
		else if (map[line][col + x] == '1')
			break ;
		if (map[line][col + x] != '1' || map[line][col + x] != space)
			return (error("map has non-closed empty spaces"), 1);
		x++;
	}
	return (0);
}

int	check_empty(char **map, int line, int col, t_data *data, char space)
{
	if (check_right(map, line, col, data, space) != 0)
		return (1);
	if (check_left(map, line, col, space) != 0)
		return (1);
	if (check_up(map, line, col, space) != 0)
		return (1);
	if (check_down(map, line, col, space) != 0)
		return (1);
	return (0);
}
