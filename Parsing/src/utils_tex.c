/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:29:34 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/07 15:25:39 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

static void	set_tex_id(t_render *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			r->tex_id = 2;
		else
			r->tex_id = 3;
	}
	else
	{
		if (r->ray_dir_y > 0)
			r->tex_id = 1;
		else
			r->tex_id = 0;
	}
}

static void	compute_tex_x(t_render *r, t_game *g)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = g->pos_y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = g->pos_x + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	r->tex_x = (int)(wall_x * (double)TEX_W);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->tex_x = TEX_W - r->tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		r->tex_x = TEX_W - r->tex_x - 1;
	if (r->tex_x < 0)
		r->tex_x = 0;
	if (r->tex_x >= TEX_W)
		r->tex_x = TEX_W - 1;
}

void	choose_tex(t_render *r, t_game *g)
{
	set_tex_id(r);
	compute_tex_x(r, g);
}
