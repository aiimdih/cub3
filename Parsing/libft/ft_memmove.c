/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:53:43 by matahir           #+#    #+#             */
/*   Updated: 2024/11/27 00:17:25 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*tmp2;
	unsigned char		*tmp;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	tmp2 = (const unsigned char *)src ;
	tmp = (unsigned char *)dest ;
	if (dest > src)
	{
		while (n-- > 0)
			tmp[n] = tmp2[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			tmp[i] = tmp2[i];
			i++;
		}
	}
	return (dest);
}
