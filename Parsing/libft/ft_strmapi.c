/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:11:36 by matahir           #+#    #+#             */
/*   Updated: 2024/11/23 23:13:54 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len_s;
	char	*f_str;

	if (!s || !f)
		return (NULL);
	len_s = ft_strlen(s);
	f_str = ft_calloc(len_s + 1, sizeof(char));
	if (!f_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		f_str[i] = f(i, s[i]);
		i++;
	}
	return (f_str);
}
