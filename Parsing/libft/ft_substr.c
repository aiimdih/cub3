/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:53:58 by matahir           #+#    #+#             */
/*   Updated: 2024/11/19 23:57:46 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*my_sub;
	size_t	lens;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (start >= lens)
		return (ft_strdup(""));
	if (len > lens - start)
		len = lens - start;
	my_sub = malloc(len + 1);
	if (my_sub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		my_sub[i] = s[start + i];
		i++;
	}
	my_sub[i] = '\0';
	return (my_sub);
}
