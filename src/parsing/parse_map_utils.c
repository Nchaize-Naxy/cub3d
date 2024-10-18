/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:29:44 by gyvergni          #+#    #+#             */
/*   Updated: 2024/10/18 15:02:17 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*no_back_n(char **split)
{
	size_t	i;
	char	*new_string;
	char	*string;

	i = 0;
	new_string = malloc(sizeof(char));
	new_string[0] = '\0';
	if (count_tab(split) == 2)
		string = split[1];
	else
		return (new_string);
	while (string && string[i])
	{
		if (string[i] == '\n')
		{
			free(new_string);
			new_string = ft_strndup(string, i);
			if (!new_string || new_string == NULL)
				return (error("Memory allocation failure"), NULL);
		}
		i++;
	}
	return (new_string);
}

void	destroy(t_data *data)
{
	if (data->textures->ea->i_create != -1)
		mlx_destroy_image(data->mlx, data->textures->ea->img);
	if (data->textures->no->i_create != -1)
		mlx_destroy_image(data->mlx, data->textures->no->img);
	if (data->textures->so->i_create != -1)
		mlx_destroy_image(data->mlx, data->textures->so->img);
	if (data->textures->we->i_create != -1)
		mlx_destroy_image(data->mlx, data->textures->we->img);
}

int	conv_rgb(char *rgb, char *hexbase)
{
	char	**rgb_split;
	char	*hex_nbr;
	int		int_value;
	char	*temp;

	rgb_split = ft_split(rgb, ',');
	if (!rgb_split)
		return (0);
	if (count_tab(rgb_split) != 3)
		return (error("need 3 colors in int format"), free_tab(rgb_split), 0);
	hex_nbr = ft_convert_base(rgb_split[0], "0123456789", hexbase);
	if (!hex_nbr)
		return (free_tab(rgb_split), 0);
	hex_nbr = ft_strjoin_update(hex_nbr, \
		ft_convert_base(rgb_split[1], "0123456789", hexbase));
	if (!hex_nbr)
		return (free_tab(rgb_split), 0);
	hex_nbr = ft_strjoin_update(hex_nbr, \
		ft_convert_base(rgb_split[2], "0123456789", hexbase));
	if (!hex_nbr)
		return (free_tab(rgb_split), 0);
	temp = ft_convert_base(hex_nbr, hexbase, "0123456789");
	int_value = atoi(temp);
	return (free_tab(rgb_split), free(temp), free(hex_nbr), int_value);
}

int	check_map_line(char *line)
{
	if (!line || line[0] == '\0' || line[0] == '\n')
		return (error("empty line"), 1);
	return (0);
}
