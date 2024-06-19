/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <nchaize-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:50:29 by nchaize-          #+#    #+#             */
/*   Updated: 2023/12/14 13:37:41 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char *buf, char *buffer_read);
char	*ft_calloc(size_t nmemb, size_t size);
ssize_t	ft_ncheck(char *str, char c);
void	ft_bzero(void *s, size_t n);
ssize_t	ft_sstrlen(char *str);

#endif
