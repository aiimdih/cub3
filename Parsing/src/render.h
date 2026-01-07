/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:56:27 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/07 15:41:44 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../includes/cub3d_render.h"

typedef struct s_render
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		tex_id;
	int		tex_x;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		step_x;
	int		step_y;
	int		side;
	int		map_x;
	int		map_y;
}			t_render;

void		render(t_game *g);
#endif
