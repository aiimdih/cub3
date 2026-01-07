/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:48:37 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/07 15:32:32 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_RENDER_H
# define CUB3D_RENDER_H

# include "./includes/cub3d.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// #include "render.h"
//

typedef struct s_render	t_render;

# define SCREEN_W 800
# define SCREEN_H 600

# define MAP_W 14
# define MAP_H 11

# define MOVE_SPEED 0.06
# define ROT_SPEED 0.05

// Linux keycodes
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define TEX_COUNT 5
# define TEX_W 64
# define TEX_H 64

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_img;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	t_img				screen;
	t_img				tex[TEX_COUNT];

	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;

	// input flags
	int					move_w;
	int					move_s;
	int					move_a;
	int					move_d;
	int					rot_l;
	int					rot_r;

	t_mlx				mlx_map;
}						t_game;

void					compute_next_position(t_game *g, double *nx,
							double *ny);
void					update_player(t_game *g);
void					init_player_from_map(t_game *g);
unsigned int			rgb_to_uint(int *rgb);
int						key_press(int keycode, void *param);
int						key_release(int keycode, void *param);
int						loop_hook(void *param);
int						close_window(void *param);
void					cleanup(t_game *g);
#endif
