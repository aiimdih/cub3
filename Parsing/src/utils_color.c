/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:29:21 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/07 15:41:42 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** helper to convert RGB int[3] to single unsigned int color
*/
#include "../includes/cub3d.h"

unsigned int	rgb_to_uint(int *rgb)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (!rgb)
		return (0);
	r = (unsigned int)rgb[0] & 0xFF;
	g = (unsigned int)rgb[1] & 0xFF;
	b = (unsigned int)rgb[2] & 0xFF;
	return ((r << 16) | (g << 8) | b);
}
