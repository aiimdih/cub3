/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:58:43 by matahir           #+#    #+#             */
/*   Updated: 2024/11/23 23:11:07 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	digit_count(long long nb)
{
	size_t	count;

	count = 0;
	if (nb < 1)
		count++;
	while (nb)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*string;
	size_t		elements;
	long long	number;

	number = n;
	elements = digit_count(number);
	string = malloc((elements + 1) * sizeof(char));
	if (!string)
		return (NULL);
	string[elements] = '\0';
	if (n < 0)
		number = -number ;
	while (elements--)
	{
		string[elements] = number % 10 + '0';
		number = number / 10;
	}
	if (n < 0)
		string[0] = '-';
	return (string);
}
