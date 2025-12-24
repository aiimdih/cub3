/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:29:30 by matahir           #+#    #+#             */
/*   Updated: 2024/11/21 17:07:56 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *string, int c_find)
{
	char	value;
	int		s_len;

	value = (char)c_find;
	s_len = ft_strlen(string) - 1;
	if (value == '\0')
		return ((char *)&string[ft_strlen(string)]);
	while (s_len >= 0)
	{
		if (string[s_len] == value)
			return ((char *) &string[s_len]);
		s_len--;
	}
	return (NULL);
}
