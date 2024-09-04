/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_base_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:41:15 by pinkdonkeyj       #+#    #+#             */
/*   Updated: 2024/09/04 14:46:27 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	power(unsigned int nbr, size_t len)
{
	unsigned int			i;
	size_t					pow;

	pow = len;
	i = 0;
	while (pow <= nbr)
	{
		pow = pow * len;
		i++;
	}
	return (i + 1);
}

int	base_check(char *str, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (len <= 1)
		return (0);
	while (str[i])
	{
		if (str[i] == 43 || str[i] == 45
			|| (str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			return (0);
		j = i + 1;
		while (str[j])
		{
			if (str[j] == str[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	decodage(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (9);
}

int	is_base(char p, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == p)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	unsigned int	len;
	unsigned int	i;
	int				num;
	int				signe;

	len = ft_strlen(base);
	signe = 1;
	i = 0;
	num = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13)
			|| str[i] == 32))
		i++;
	while (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			signe = signe * (-1);
		i++;
	}
	while (str[i] != '\0' && is_base(str[i], base) == 1)
		num = num * len + decodage(str[i++], base);
	return (num * signe);
}
