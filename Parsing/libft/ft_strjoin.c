/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:15:39 by matahir           #+#    #+#             */
/*   Updated: 2024/11/27 00:24:27 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_result;
	size_t	len_total;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len_total = ft_strlen(s1) + ft_strlen(s2);
	str_result = malloc(len_total + 1);
	if (str_result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str_result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str_result[i + j] = s2[j];
		j++;
	}
	str_result[i + j] = '\0';
	return (str_result);
}
