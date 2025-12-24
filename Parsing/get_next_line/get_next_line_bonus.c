/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:29:48 by matahir           #+#    #+#             */
/*   Updated: 2025/01/15 03:50:48 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*save_leftovers(char *cup)
{
	int		i;
	int		j;
	char	*remaining;

	i = 0;
	j = 0;
	while (cup[i] && cup[i] != '\n')
		i++;
	if (cup[i] == '\n')
		i++;
	remaining = ft_calloc(ft_strlen(cup) - i + 1, sizeof(char));
	if (!remaining)
		return (NULL);
	while (cup[i])
	{
		remaining[j] = cup[i];
		j++;
		i++;
	}
	free(cup);
	return (remaining);
}

char	*extract_line(char *cup)
{
	int		i;
	char	*line;

	i = 0;
	while (cup[i] && cup[i] != '\n')
		i++;
	if (cup[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (cup[i] && cup[i] != '\n')
	{
		line[i] = cup[i];
		i++;
	}
	if (cup[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*append_buffer(char *cup, char *spoon)
{
	char	*new_cup;

	new_cup = ft_strjoin(cup, spoon);
	free(cup);
	return (new_cup);
}

char	*reading_fct(char *cup, int fd)
{
	char	*spoon;
	int		bytes_read;

	spoon = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!spoon)
		return (check(cup));
	while (!my_strchr(cup, '\n'))
	{
		bytes_read = read(fd, spoon, BUFFER_SIZE);
		if (bytes_read == -1)
			return (check(spoon));
		if (bytes_read == 0)
		{
			free(spoon);
			if (!*cup)
				return (check(cup));
			return (cup);
		}
		spoon[bytes_read] = '\0';
		cup = append_buffer(cup, spoon);
		if (!cup)
			return (check(spoon));
	}
	free(spoon);
	return (cup);
}

char	*get_next_line(int fd)
{
	static char	*cup[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (!cup[fd])
		cup[fd] = ft_calloc(1, sizeof(char));
	if (!cup[fd])
		return (NULL);
	if (!my_strchr(cup[fd], '\n'))
		cup[fd] = reading_fct(cup[fd], fd);
	if (!cup[fd] || !(*cup[fd]))
		return (check(cup[fd]));
	line = extract_line(cup[fd]);
	if (!line)
		return (NULL);
	cup[fd] = save_leftovers(cup[fd]);
	if (!cup[fd])
		return (NULL);
	return (line);
}
