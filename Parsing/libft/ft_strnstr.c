/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:27:21 by matahir           #+#    #+#             */
/*   Updated: 2024/11/27 00:27:08 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *string, const char *to_find, size_t nb)
{
	size_t	i;
	size_t	f;

	if (to_find[0] == '\0')
		return ((char *)string);
	i = 0;
	while (string[i] != '\0' && i < nb)
	{
		f = 0;
		if (string[i] == to_find[f])
		{
			while (string[i + f] == to_find[f] && (i + f) < nb)
			{
				f++;
				if (to_find[f] == '\0')
					return ((char *)&string[i]);
			}
		}
		i++;
	}
	return (0);
}
