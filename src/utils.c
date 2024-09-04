/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:53:54 by gyvergni          #+#    #+#             */
/*   Updated: 2024/09/04 11:06:31 by nchaize-         ###   ########.fr       */
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

char	*ft_strjoin_update(char *buffer, char *buffer_read)
{
	char	*res;
	size_t	i;
	size_t	buf_size;
	size_t	buffer_read_size;

	i = -1;
	if (!buffer || !buffer_read)
		return (NULL);
	buf_size = ft_sstrlen(buffer);
	buffer_read_size = ft_sstrlen(buffer_read);
	res = malloc(sizeof(char) * (buf_size + buffer_read_size) + 1);
	if (!res)
		return (free(buffer), free(buffer_read), NULL);
	while (buffer[++i])
		res[i] = buffer[i];
	i = 0;
	free(buffer);
	while (buffer_read[i])
	{
		res[i + buf_size] = buffer_read[i];
		i++;
	}
	res[i + buf_size] = '\0';
	return (free(buffer_read), res);
}
