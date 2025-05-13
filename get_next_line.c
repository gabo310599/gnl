/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:45:20 by gojeda            #+#    #+#             */
/*   Updated: 2025/04/30 14:45:22 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*free_error(char **storage, char **buffer)
{
	free(*buffer);
	free(*storage);
	*storage = NULL;
	return (NULL);
}

static int	free_gnl_content(char **storage, char **buffer)
{
	free(*buffer);
	if (!*storage || !**storage)
	{
		free(*storage);
		*storage = NULL;
		return (0);
	}
	return (1);
}

static char	*get_new_line(char **storage)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while ((*storage)[i] && (*storage)[i] != '\n')
		i++;
	if ((*storage)[i] == '\n')
		line = ft_substr(*storage, 0, i + 1);
	else
		line = ft_substr(*storage, 0, i);
	if ((*storage)[i])
		temp = ft_strdup(*storage + i + 1);
	else
		temp = NULL;
	free(*storage);
	*storage = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	ssize_t		bytes_read;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_error(&storage, &buffer));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(storage, buffer);
		free(storage);
		storage = temp;
	}
	if (!free_gnl_content(&storage, &buffer))
		return (NULL);
	return (get_new_line(&storage));
}
