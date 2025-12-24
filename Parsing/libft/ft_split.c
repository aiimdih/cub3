/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <matahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:26:07 by matahir           #+#    #+#             */
/*   Updated: 2024/11/24 22:10:14 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_strings(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] == c && c != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			count++;
			while (str[i] == c)
				i++;
		}
		else
		{
			i++;
		}
	}
	if (str[i] == '\0' && i > 0 && str[i - 1] != c)
		count++;
	return (count);
}

static char	*str_sub(char const *str, int start, int end)
{
	int		i;
	char	*string;

	i = 0;
	string = malloc(sizeof(char) *(end - start) + 1);
	if (!string)
		return (NULL);
	while (start < end)
	{
		string[i] = str[start];
		start++;
		i++;
	}
	string[i] = '\0';
	return (string);
}

static char	**free_string(char **strings, int j)
{
	while (j > 0)
	{
		j--;
		free(strings[j]);
	}
	free(strings);
	return (NULL);
}

static char	**split_words(char const *s, char c, char **strings)
{
	int		start;
	int		end;
	int		j;

	start = 0;
	end = 0;
	j = 0;
	while (s[end] == c && c != '\0')
		end++;
	while (s[end] != '\0')
	{
		start = end;
		while (s[end] != c && s[end] != '\0')
			end++;
		strings[j] = str_sub(s, start, end);
		if (!strings[j])
			return (free_string(strings, j));
		j++;
		while (s[end] == c && c != '\0')
			end++;
	}
	strings[j] = NULL;
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;

	if (s == NULL)
		return (NULL);
	strings = malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!strings)
		return (NULL);
	return (split_words(s, c, strings));
}
