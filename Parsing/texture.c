/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:29:15 by aiimdih          #+#    #+#             */
/*   Updated: 2026/01/07 15:19:57 by aiimdih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

static void	set_texture_files(t_game *g, const char **files)
{
	if (g->mlx_map.map && g->mlx_map.map->no_path)
		files[0] = g->mlx_map.map->no_path;
	else
		files[0] = "./assets/redbrick.xpm";
	if (g->mlx_map.map && g->mlx_map.map->so_path)
		files[1] = g->mlx_map.map->so_path;
	else
		files[1] = "./assets/greystone.xpm";
	if (g->mlx_map.map && g->mlx_map.map->we_path)
		files[2] = g->mlx_map.map->we_path;
	else
		files[2] = "./assets/bluestone.xpm";
	if (g->mlx_map.map && g->mlx_map.map->ea_path)
		files[3] = g->mlx_map.map->ea_path;
	else
		files[3] = "./assets/eagle.xpm";
	files[4] = "./assets/Wall.xpm";
}

void	pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (!img->addr)
		return ;
	if (x < 0 || y < 0 || x >= SCREEN_W || y >= SCREEN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	tex_pixel(t_img *tex, int x, int y)
{
	char	*src;

	if (!tex->addr)
		return (0);
	if (x < 0)
		x = 0;
	if (x >= TEX_W)
		x = TEX_W - 1;
	if (y < 0)
		y = 0;
	if (y >= TEX_H)
		y = TEX_H - 1;
	src = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)src);
}

/* choose_tex moved to utils_tex.c */

void	draw_textured_column(t_render *r, t_game *g, int x)
{
	t_tex	t;
	int		y;

	t.step = 1.0 * (double)TEX_H / (double)r->line_height;
	t.tex_pos = (r->draw_start - SCREEN_H / 2 + r->line_height / 2) * t.step;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		t.tex_y = (int)t.tex_pos & (TEX_H - 1);
		t.tex_pos += t.step;
		t.color = tex_pixel(&g->tex[r->tex_id], r->tex_x, t.tex_y);
		t.shade = 1.0 / (1.0 + r->perp_wall_dist * 0.08);
		if (t.shade < 0.25)
			t.shade = 0.25;
		t.r = (unsigned int)(((t.color >> 16) & 0xFF) * t.shade);
		t.g = (unsigned int)(((t.color >> 8) & 0xFF) * t.shade);
		t.b = (unsigned int)((t.color & 0xFF) * t.shade);
		t.shaded = (t.r << 16) | (t.g << 8) | t.b;
		pixel_put(&g->screen, x, y, t.shaded);
		y++;
	}
}

void	load_texture(t_game *g)
{
	int			w;
	int			h;
	const char	*files[TEX_COUNT];
	int			i;

	w = TEX_W;
	h = TEX_H;
	set_texture_files(g, files);
	i = 0;
	while (i < TEX_COUNT)
	{
		g->tex[i].img = mlx_xpm_file_to_image(g->mlx, (char *)files[i], &w, &h);
		if (!g->tex[i].img)
		{
			fprintf(stderr, "Failed to load texture: %s\n", files[i]);
			exit(1);
		}
		g->tex[i].addr = mlx_get_data_addr(g->tex[i].img, &g->tex[i].bpp,
				&g->tex[i].line_len, &g->tex[i].endian);
		i++;
	}
}
