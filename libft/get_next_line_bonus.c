/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:36:01 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/06/09 15:08:42 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	joined = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(*joined));
	if (!joined)
		return (NULL);
	i = 0;
	j = -1;
	if (s1)
	{
		while (s1[i])
		{
			joined[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[++j])
		joined[i++] = s2[j];
	return (joined);
}

static char	*ft_get_line(char *remember)
{
	char	*line;
	int		len;
	int		i;

	if (!remember)
		return (NULL);
	len = 0;
	while (remember[len] != 10 && remember[len])
		len++;
	if (remember[len] == 10)
		len++;
	line = ft_calloc(len + 1, sizeof(*line));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = remember [i];
		i++;
	}
	if (i == 0)
		return (free(line), NULL);
	return (line);
}

static char	*ft_tail_remember(char *remember)
{
	char	*tail_rmb;
	int		len;
	int		pos;
	int		i;

	if (!remember)
		return (NULL);
	pos = 0;
	while (remember[pos] != 10 && remember[pos])
		pos++;
	if (remember[pos] == 10)
		pos += 1;
	len = ft_strlen(remember) - pos + 1;
	tail_rmb = ft_calloc(len + 1, sizeof(*tail_rmb));
	if (!tail_rmb)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tail_rmb[i] = remember[pos];
		i++;
		pos++;
	}
	return (free(remember), tail_rmb);
}

static char	*ft_read_file(int fd, char *remember)
{
	int		n_bytes;
	char	*reader;

	reader = ft_calloc(BUFFER_SIZE + 1, sizeof(*reader));
	if (!reader)
		return (NULL);
	n_bytes = 1;
	while (n_bytes > 0 && ft_strchr(remember, 10) == NULL)
	{
		n_bytes = read(fd, reader, BUFFER_SIZE);
		if (n_bytes == -1)
			return (free(reader), free(remember), NULL);
		reader[n_bytes] = '\0';
		remember = ft_join(remember, reader);
	}
	free(reader);
	return (remember);
}

char	*get_next_line(int fd)
{
	static char	*remember[4096];
	char		*line;

	if (!remember[fd])
		remember[fd] = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	remember[fd] = ft_read_file(fd, remember[fd]);
	line = ft_get_line(remember[fd]);
	if (!line)
	{
		free(remember[fd]);
		remember[fd] = NULL;
		return (NULL);
	}
	remember[fd] = ft_tail_remember(remember[fd]);
	return (line);
}
