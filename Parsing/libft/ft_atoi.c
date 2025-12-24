/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:15:35 by matahir           #+#    #+#             */
/*   Updated: 2024/11/19 22:17:29 by matahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *string)
{
	int	rslt;
	int	sign;

	rslt = 0;
	sign = 1;
	while (*string == ' ' || (*string >= 9 && *string <= 13))
		string++;
	if (*string == '-')
		sign = -1;
	if (*string == '-' || *string == '+')
		string++;
	while (*string >= '0' && *string <= '9')
	{
		rslt = rslt * 10 + *string - '0';
		string++;
	}
	return (sign * rslt);
}
