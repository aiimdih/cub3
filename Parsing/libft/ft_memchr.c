/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:34:22 by matahir           #+#    #+#             */
/*   Updated: 2024/11/19 22:42:44 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int x, size_t nb)
{
	const unsigned char	*string;
	size_t				i;
	unsigned char		value;

	string = (unsigned char *)s;
	value = (unsigned char)x;
	i = 0;
	while (i < nb)
	{
		if (string[i] == value)
			return ((void *) &string[i]);
		i++;
	}
	return (NULL);
}
