/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 12:00:00 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/07 12:46:03 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_render.h"
#include "../includes/cub3d.h"

static void	set_player_position(t_game *g)
{
	g->pos_x = (double)g->mlx_map.map->player_x + 0.5;
	g->pos_y = (double)g->mlx_map.map->player_y + 0.5;
}

static void	set_direction_vectors(t_game *g, char d)
{
	if (d == 'N')
	{
		g->dir_x = 0.0;
		g->dir_y = -1.0;
	}
	else if (d == 'S')
	{
		g->dir_x = 0.0;
		g->dir_y = 1.0;
	}
	else if (d == 'W')
	{
		g->dir_x = -1.0;
		g->dir_y = 0.0;
	}
	else if (d == 'E')
	{
		g->dir_x = 1.0;
		g->dir_y = 0.0;
	}
	else
	{
		g->dir_x = 1.0;
		g->dir_y = 0.0;
	}
}

static void	set_player_direction(t_game *g)
{
	char	d;

	d = ft_toupper((int)g->mlx_map.map->player_dir);
	set_direction_vectors(g, d);
	g->plane_x = g->dir_y * 0.66;
	g->plane_y = -g->dir_x * 0.66;
}

void	init_player_from_map(t_game *g)
{
	set_player_position(g);
	set_player_direction(g);
}
