/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>              		+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:33:22 by matahir           #+#    #+#             */
/*   Updated: 2025/12/24 20:06:12 by matahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_leftovers(char	*cup)
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
	remaining = gnl_calloc(gnl_strlen(cup) - i + 1, sizeof(char));
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

char	*extract_line(char	*cup)
{
	int		i;
	char	*line;

	i = 0;
	while (cup[i] && cup[i] != '\n')
		i++;
	if (cup[i] == '\n')
		i++;
	line = gnl_calloc(i + 1, sizeof(char));
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

char	*append_buffer(char	*cup, char	*spoon)
{
	char	*new_cup;

	new_cup = gnl_strjoin(cup, spoon);
	free(cup);
	return (new_cup);
}

char	*reading_fct(char	*cup, int fd)
{
	char	*spoon;
	int		bytes_read;

	spoon = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!spoon)
		return (check(cup));
	while (! my_strchr(cup, '\n'))
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
	static char	*cup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!cup)
		cup = gnl_calloc(1, sizeof(char));
	if (!cup)
		return (NULL);
	if (!my_strchr(cup, '\n'))
		cup = reading_fct(cup, fd);
	if (!cup || !(*cup))
		return (check(cup));
	line = extract_line(cup);
	if (!line)
		return (NULL);
	cup = save_leftovers(cup);
	if (!cup)
		return (NULL);
	return (line);
}
