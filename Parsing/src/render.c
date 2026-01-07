/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:28:24 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/07 15:25:39 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "texture.h"
#include "dda.h"

void	draw_background(t_game *g)
{
	unsigned int	ceil_color;
	unsigned int	flr_color;
	int				y;
	int				x;
	unsigned int	color;

	ceil_color = rgb_to_uint(g->mlx_map.map->ceiling_color);
	flr_color = rgb_to_uint(g->mlx_map.map->floor_color);
	y = 0;
	while (y < SCREEN_H)
	{
		if (y < SCREEN_H / 2)
			color = ceil_color;
		else
			color = flr_color;
		x = 0;
		while (x < SCREEN_W)
		{
			pixel_put(&g->screen, x, y, color);
			x++;
		}
		y++;
	}
}

void	count_delta(t_render *r, t_game *g)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->pos_x - (int)g->pos_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = ((int)g->pos_x + 1.0 - g->pos_x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->pos_y - (int)g->pos_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = ((int)g->pos_y + 1.0 - g->pos_y) * r->delta_dist_y;
	}
}

static void	set_delta_dist(t_render *r)
{
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->ray_dir_y);
}

/* DDA logic moved to dda.c: use dda_loop(r, g) */

void	compute_perp_wall_dist(t_render *r)
{
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	if (r->perp_wall_dist < 0.000001)
		r->perp_wall_dist = 0.000001;
	r->line_height = (int)(SCREEN_H / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + SCREEN_H / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + SCREEN_H / 2;
	if (r->draw_end >= SCREEN_H)
		r->draw_end = SCREEN_H - 1;
}

void	render(t_game *g)
{
	t_render	r;
	int			x;

	draw_background(g);
	x = 0;
	while (x < SCREEN_W)
	{
		r.camera_x = 2.0 * x / (double)SCREEN_W - 1.0;
		r.ray_dir_x = g->dir_x + g->plane_x * r.camera_x;
		r.ray_dir_y = g->dir_y + g->plane_y * r.camera_x;
		set_delta_dist(&r);
		r.map_x = (int)g->pos_x;
		r.map_y = (int)g->pos_y;
		count_delta(&r, g);
		dda_loop(&r, g);
		compute_perp_wall_dist(&r);
		choose_tex(&r, g);
		draw_textured_column(&r, g, x);
		x++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);
}
