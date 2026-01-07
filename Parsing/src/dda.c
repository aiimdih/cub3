/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:28:49 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/06 20:58:26 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dda.h"

void	dda_step(t_render *r)
{
	if (r->side_dist_x < r->side_dist_y)
	{
		r->side_dist_x += r->delta_dist_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_dist_y += r->delta_dist_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
}

void	dda_loop(t_render *r, t_game *g)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		dda_step(r);
		if (r->map_y < 0 || r->map_y >= g->mlx_map.map->height)
		{
			hit = 1;
			break ;
		}
		if (r->map_x < 0
			|| r->map_x >= (int)ft_strlen(g->mlx_map.map->map[r->map_y]))
		{
			hit = 1;
			break ;
		}
		if (g->mlx_map.map->map[r->map_y][r->map_x] > '0')
			hit = 1;
	}
}
