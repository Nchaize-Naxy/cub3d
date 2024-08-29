/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:03:37 by nchaize-          #+#    #+#             */
/*   Updated: 2024/08/29 15:04:19 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strndup(const char *s, size_t n)
{
	char		*dup;
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen((char *)s);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strdup(const char *s)
{
	char		*dup;
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen((char *)s);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*dup_map_row(const char *s)
{
	char		*dup;
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen((char *)s);
	if (s[len] == '\n')
		len--;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len && s[i] != '\n')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long long	num;
	size_t		i;
	int			signe;

	num = 0;
	i = 0;
	signe = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 43 || str [i] == 45)
	{
		if (str[i] == 45)
			signe = -1;
		i++;
	}
	while (str[i] && is_num(str[i]) == 1)
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	return ((int)(num * signe));
}
