/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:18:15 by matahir           #+#    #+#             */
/*   Updated: 2024/11/21 17:06:46 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	lendst;
	size_t	lensrc;

	if (!destsize)
		return (ft_strlen(src) + destsize);
	i = 0;
	lendst = ft_strlen(dest);
	lensrc = ft_strlen(src);
	if (destsize <= lendst)
		return (destsize + lensrc);
	while (src[i] != '\0' && i < (destsize - lendst - 1))
	{
		dest[lendst + i] = src[i];
		i++;
	}
	dest[lendst + i] = '\0';
	return (lensrc + lendst);
}
