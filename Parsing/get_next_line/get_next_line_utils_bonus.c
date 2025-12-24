/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:04:35 by matahir           #+#    #+#             */
/*   Updated: 2025/01/11 18:07:49 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*check(char *t)
{
	free(t);
	t = NULL;
	return (NULL);
}

void	*ft_calloc(size_t lenn, size_t size)
{
	void	*tmp;
	size_t	total_size;
	size_t	i;

	total_size = lenn * size;
	tmp = malloc(total_size);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		((unsigned char *)tmp)[i] = 0;
		i++;
	}
	return (tmp);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *cup, char *spoon)
{
	char	*new_cup;
	size_t	len_total;
	int		i;
	int		j;

	if (!cup || !spoon)
		return (NULL);
	len_total = ft_strlen(cup) + ft_strlen(spoon);
	new_cup = ft_calloc(len_total + 1, sizeof(char));
	if (!new_cup)
		return (NULL);
	i = 0;
	while (cup[i] != '\0')
	{
		new_cup[i] = cup[i];
		i++;
	}
	j = 0;
	while (spoon[j] != '\0')
	{
		new_cup[i + j] = spoon[j];
		j++;
	}
	return (new_cup);
}

char	*my_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
