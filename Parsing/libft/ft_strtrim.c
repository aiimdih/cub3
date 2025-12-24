/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:31:49 by matahir           #+#    #+#             */
/*   Updated: 2024/11/27 00:30:08 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	findstart( char const *s1, char const *set)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	z = ft_strlen(set);
	while (s1[i])
	{
		j = 0 ;
		while (set[j])
		{
			if (set[j] == s1[i])
			{
				i++;
				break ;
			}
			j++;
		}
		if (j == z)
			return (i);
	}
	return (i);
}

static size_t	findend(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	z;

	i = ft_strlen(s1) - 1;
	z = ft_strlen(set);
	while (i >= 0)
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
			{
				i--;
				break ;
			}
			j++;
		}
		if (j == z)
			return (i + 1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	if (ft_strlen(s1) == 0 || findstart(s1, set) == ft_strlen(s1))
		return (ft_strdup(""));
	trimmed = ft_calloc((findend(s1, set) - findstart(s1, set)) + 1,
			sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	ft_strlcpy(trimmed, &s1[findstart(s1, set)],
		(findend(s1, set) - findstart(s1, set)) + 1);
	return (trimmed);
}
