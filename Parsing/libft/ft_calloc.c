/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:20:56 by matahir           #+#    #+#             */
/*   Updated: 2024/11/27 00:32:25 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t lenn, size_t size)
{
	void	*tmp;

	if (size && lenn > SIZE_MAX / size)
		return (NULL);
	tmp = malloc(lenn * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, (lenn * size));
	return (tmp);
}
