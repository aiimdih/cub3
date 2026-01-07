/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:29:15 by aiimdih          #+#    #+#             */
/*   Updated: 2026/01/07 15:19:57 by aiimdih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "cub3d_render.h"
# include "render.h"

typedef struct s_tex
{
	int				tex_y;
	double			step;
	double			tex_pos;
	double			shade;
	double			shaded;
	unsigned int	color;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_tex;

void				load_texture(t_game *g);
void				pixel_put(t_img *img, int x, int y, unsigned int color);
void				choose_tex(t_render *r, t_game *g);
void				draw_textured_column(t_render *r, t_game *g, int x);
#endif