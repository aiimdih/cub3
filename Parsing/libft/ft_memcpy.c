/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:48:30 by matahir           #+#    #+#             */
/*   Updated: 2024/11/27 00:05:07 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*tmp;
	const unsigned char	*tmp2;

	if (!src && !dest)
		return (NULL);
	i = 0;
	tmp = (unsigned char *)dest;
	tmp2 = (const unsigned char *)src;
	while (i < n)
	{
		tmp[i] = tmp2[i];
		i++;
	}
	return (dest);
}
