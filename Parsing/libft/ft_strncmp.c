/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:23:57 by matahir           #+#    #+#             */
/*   Updated: 2024/11/19 23:26:50 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *string1, const char *string2, size_t m_tocmp)
{
	size_t	i;

	i = 0;
	while (i < m_tocmp && string1[i] != '\0' && string2[i] != '\0'
		&& (unsigned char)string1[i] == (unsigned char)string2[i])
	{
		i++;
	}
	if (i == m_tocmp)
	{
		return (0);
	}
	else
		return ((unsigned char)string1[i] - (unsigned char)string2[i]);
}
