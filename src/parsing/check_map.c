/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:56:40 by gyvergni          #+#    #+#             */
/*   Updated: 2024/07/30 11:09:24 by nchaize-         ###   ########.fr       */
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
	while ((line + x < (int) data->height) && (is_valid_ch(map[line + x][col])))
	{
		if (map[line + x][col] == ' ')
		{
			x++;
			continue;
		}
		else if (map[line + x][col] == '1')
			break;
		if (map[line + x][col] != '1' || map[line + x][col] != ' ')
			return (error("map has non-closed empty spaces"), 0);
		x++;
	}
	x = 0;
	while ((line - x >= 0) && (is_valid_ch(map[line - x][col])))
	{
		if (map[line - x][col] == ' ')
		{
			x++;
			continue;
		}
		else if (map[line - x][col] == '1')
			break;
		if (map[line - x][col] != '1' || map[line - x][col] != ' ')
			return (error("map has non-closed empty spaces"), 0);
		x++;
	}
	x = 0;
	while ((col + x != '\0') && (is_valid_ch(map[line][col + x])))
	{
		if (map[line][col + x] == ' ')
		{
			x++;
			continue;
		}
		else if (map[line][col + x] == '1')
			break;
		if (map[line][col + x] != '1' || map[line][col + x] != ' ')
			return (error("map has non-closed empty spaces"), 0);
		x++;
	}
	x = 0;
	while ((col - x >= 0) && (is_valid_ch(map[line][col - x])))
	{
		if (map[line][col - x] == ' ')
		{
			x++;
			continue;
		}
		else if (map[line][col - x] == '1')
			break;
		else
			return (error("map has non-closed empty spaces"), 0);
		x++;
	}
	return (1);
}

int	is_player_position(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	handle_player_pos(size_t line, size_t col, char dir, t_data *data)
{
	data->player->pos_x = ((int) col) + 0.5;
	data->player->pos_y = ((int) line) + 0.5;
	if (dir == 'N')
		data->player->a = (3 * M_PI) / 2;;
	if (dir == 'E')
		data->player->a = 0;
	if (dir == 'W')
		data->player->a = M_PI;
	if (dir == 'S')
		data->player->a = M_PI / 2;
	data->player->dir_x = cos(data->player->a);
	data->player->dir_y = sin(data->player->a);
	data->ray.x1 = data->player->pos_x;
	data->ray.y1 = data->player->pos_y;
	data->ray.x2 = data->player->pos_x;
	data->ray.y2 = data->player->pos_y;
	data->ray.pos_x = data->player->pos_x;
	data->ray.pos_y = data->player->pos_y;
	return (1);
}

int	check_map(char **map, t_data *data)
{
	size_t line;
	size_t	col;

	line = 0;
	col = 0;
	while (map && map[line])
	{
		col = 0;
		while (map && map[line][col])
		{
			if (!is_valid_ch(map[line][col]) && map[line][col] != '1')
				return (error("invalid character found in map"), 0);
			else if (map[line][col] == ' ')
			{
				if (check_empty(map, line, col, data) == 0)
					return (0);
			}
			else if (is_player_position(map[line][col]))
				handle_player_pos(line, col, map[line][col], data);
			else if (map[line][col] != '1'
				&& (line == 0 || col == 0 || col == ft_strlen(map[line]) - 1 || line == data->height
				|| col >= ft_strlen(map[line - 1]) || col >= ft_strlen(map[line + 1])))
				return (error("map not closed by walls"), 0);
			col++;
		}
		line++;
	}
	return (1);
}
