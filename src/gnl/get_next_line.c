/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <nchaize-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:49:10 by nchaize-          #+#    #+#             */
/*   Updated: 2023/12/14 13:56:37 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_static_buf(char *buffer, char *line, char *buf)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	if (!line)
		return (free(buffer), NULL);
	while (buffer[j] != '\n' && buffer[j] != '\0')
		j++;
	if (buffer[j] == '\0' || (buffer[j] == '\n' && buffer[j + 1] == '\0'))
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		free(buffer);
		return (buf);
	}
	j++;
	while (buffer[j] != '\0')
		buf[i++] = buffer[j++];
	free(buffer);
	buf[i] = '\0';
	return (buf);
}

char	*ft_get_line(char *buf)
{
	char	*new_line;
	size_t	i;

	i = 0;
	if (!buf[0])
		return (NULL);
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\n')
		i++;
	new_line = ft_calloc(i + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
	{
		new_line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

char	*ft_clear_old_buf(char *buffer, char *buffer_read)
{
	char	*new_buf;

	if (buffer[0] == '\0' && buffer_read[0] == '\0')
	{
		free(buffer_read);
		free(buffer);
		return (NULL);
	}
	new_buf = ft_strjoin(buffer, buffer_read);
	if (!new_buf)
	{
		free(buffer);
		free(buffer_read);
		return (NULL);
	}
	free(buffer);
	return (new_buf);
}

char	*ft_get_buf(int fd, char *buffer, char *buf, ssize_t i)
{
	char	*buffer_read;
	ssize_t	index;

	index = -1;
	buffer_read = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer_read)
		return (free(buffer), NULL);
	while (++index < ft_sstrlen(buf))
		buffer[index] = buf[index];
	buffer[index] = '\0';
	if (ft_ncheck(buffer, '\n') >= 0)
		return (free(buffer_read), buffer);
	while (i > 0 && !(ft_ncheck(buffer, '\n') >= 0))
	{
		i = read(fd, buffer_read, BUFFER_SIZE);
		if (i == -1)
			return (free(buffer), NULL);
		buffer_read[i] = '\0';
		buffer = ft_clear_old_buf(buffer, buffer_read);
		if (!buffer)
			return (NULL);
	}
	return (free(buffer_read), buffer);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		ft_bzero(buf, ft_sstrlen(buf));
		return (NULL);
	}
	if (!buf[0])
		buf[0] = '\0';
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	buffer = ft_get_buf(fd, buffer, buf, 1);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	if (!ft_static_buf(buffer, line, buf))
		return (NULL);
	return (line);
}
