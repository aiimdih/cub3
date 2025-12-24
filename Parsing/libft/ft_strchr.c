/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:09:55 by matahir           #+#    #+#             */
/*   Updated: 2024/11/19 23:13:12 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *string, int c_find)
{
	size_t	i;
	char	value;

	value = (char)c_find;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == value)
			return ((char *) &string[i]);
		i++;
	}
	if (string[i] == value)
		return ((char *)&string[i]);
	return (NULL);
}
