/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:13:36 by matahir           #+#    #+#             */
/*   Updated: 2024/11/19 23:15:06 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *string)
{
	int		i;
	int		lensrc;
	char	*dup;

	i = 0;
	lensrc = 0;
	while (string[lensrc] != '\0')
		lensrc++;
	dup = malloc(sizeof(char) * (lensrc + 1));
	if (dup == NULL)
		return (NULL);
	while (string[i] != '\0')
	{
		dup[i] = string[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
