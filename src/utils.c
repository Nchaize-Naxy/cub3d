/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:53:54 by gyvergni          #+#    #+#             */
/*   Updated: 2024/08/29 15:05:20 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *err_msg)
{
	printf("%s\n", err_msg);
}

size_t	ft_strlen(const char *str)
{
	size_t	c;

	c = 0;
	while (str[c] != '\0')
	{
		c++;
	}
	return (c);
}

int	is_alnum(int c)
{
	if ((c >= 48 && c <= 57) || ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
	{
		return (1);
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
