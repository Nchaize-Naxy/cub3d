/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:35:42 by gyvergni          #+#    #+#             */
/*   Updated: 2024/09/04 15:36:26 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *map_name, char *extension)
{
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(map_name);
	if (len > 3)
		i = len - 4;
	else
		return (1);
	j = 0;
	while (map_name[i])
	{
		if (map_name[i++] != extension[j++])
			return (1);
	}
	return (0);
}

int	check_name(char *map_name)
{
	if (check_extension(map_name, ".cub") != 0)
		return (error("Invalid map extension. Need .cub"), 1);
	return (0);
}