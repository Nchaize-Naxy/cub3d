/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:01:55 by nchaize-          #+#    #+#             */
/*   Updated: 2024/09/04 11:06:38 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_sstrlen(char *str)
{
	ssize_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

ssize_t	ft_ncheck(char *str, char c)
{
	ssize_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;

	if (size != 0 && nmemb != 0)
	{
		if (SIZE_MAX / nmemb < size)
			return (NULL);
		memory = malloc(size * nmemb);
		if (!memory)
			return (NULL);
		ft_bzero(memory, nmemb * size);
		return (memory);
	}
	else
		return (malloc(0));
}

char	*ft_strjoin(char *buffer, char *buffer_read)
{
	char	*res;
	size_t	i;
	size_t	buf_size;
	size_t	buffer_read_size;

	i = 0;
	buf_size = ft_sstrlen(buffer);
	buffer_read_size = ft_sstrlen(buffer_read);
	res = malloc(sizeof(char) * (buf_size + buffer_read_size) + 1);
	if (!res)
		return (NULL);
	while (buffer[i])
	{
		res[i] = buffer[i];
		i++;
	}
	i = 0;
	while (buffer_read[i])
	{
		res[i + buf_size] = buffer_read[i];
		i++;
	}
	res[i + buf_size] = '\0';
	return (res);
}
