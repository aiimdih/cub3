/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:28:56 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/07 15:32:31 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player_move.h"
#include "render.h"

void	apply_movement(t_game *g, double nx, double ny)
{
	int	map_h;

	if (g->mlx_map.map && g->mlx_map.map->map)
	{
		map_h = g->mlx_map.map->height;
		if ((int)g->pos_y >= 0 && (int)g->pos_y < map_h && (int)nx >= 0
			&& (int)nx < (int)ft_strlen(g->mlx_map.map->map[(int)g->pos_y]))
		{
			if (g->mlx_map.map->map[(int)g->pos_y][(int)nx] == '0')
				g->pos_x = nx;
		}
		if ((int)ny >= 0 && (int)ny < map_h && (int)g->pos_x >= 0
			&& (int)g->pos_x < (int)ft_strlen(g->mlx_map.map->map[(int)ny]))
		{
			if (g->mlx_map.map->map[(int)ny][(int)g->pos_x] == '0')
				g->pos_y = ny;
		}
	}
}

void	apply_rotation(t_game *g)
{
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	if (g->rot_l || g->rot_r)
	{
		if (g->rot_l)
			rot = ROT_SPEED;
		else
			rot = -ROT_SPEED;
		old_dir_x = g->dir_x;
		g->dir_x = g->dir_x * cos(rot) - g->dir_y * sin(rot);
		g->dir_y = old_dir_x * sin(rot) + g->dir_y * cos(rot);
		old_plane_x = g->plane_x;
		g->plane_x = g->plane_x * cos(rot) - g->plane_y * sin(rot);
		g->plane_y = old_plane_x * sin(rot) + g->plane_y * cos(rot);
	}
}

int	close_window(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	cleanup(g);
	exit(0);
	return (0);
}

void	cleanup(t_game *g)
{
	int	i;

	if (g->screen.img)
		mlx_destroy_image(g->mlx, g->screen.img);
	i = 0;
	while (i < TEX_COUNT)
	{
		if (g->tex[i].img)
			mlx_destroy_image(g->mlx, g->tex[i].img);
		i++;
	}
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	free_mlx(&g->mlx_map);
}
