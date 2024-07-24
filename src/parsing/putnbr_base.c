/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:01:36 by gyvergni          #+#    #+#             */
/*   Updated: 2024/07/24 16:01:49 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	base_check(char *str, int len)
{
	int		i;
	int		j;

	i = 0;
	if (len <= 1)
		return (0);
	while (str[i])
	{
		if (str[i] == 43 || str[i] == 45)
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

void	ft_putnbr_base(int nbr, char *base)
{
	unsigned int	len;
	unsigned int	n;

	len = str_len(base);
	if (base_check(base, len) == 1)
	{
		if (nbr < 0)
		{
			ft_putchar('-');
			nbr = -nbr;
		}
		n = nbr;
		if (base_check(base, len) == 1)
		{
			while (n >= len)
			{
				ft_putnbr_base(n / len, base);
				n %= len;
			}
			ft_putchar(base[n]);
		}
	}
}
