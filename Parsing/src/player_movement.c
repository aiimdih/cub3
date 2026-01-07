/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:29:03 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/07 15:41:41 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_render.h"
#include "render.h"
#include "player_move.h"

void	compute_next_position(t_game *g, double *nx, double *ny)
{
	if (g->move_w)
	{
		*nx = g->pos_x + g->dir_x * MOVE_SPEED;
		*ny = g->pos_y + g->dir_y * MOVE_SPEED;
	}
	if (g->move_s)
	{
		*nx = g->pos_x - g->dir_x * MOVE_SPEED;
		*ny = g->pos_y - g->dir_y * MOVE_SPEED;
	}
	if (g->move_a)
	{
		*nx = g->pos_x - g->dir_y * MOVE_SPEED;
		*ny = g->pos_y + g->dir_x * MOVE_SPEED;
	}
	if (g->move_d)
	{
		*nx = g->pos_x + g->dir_y * MOVE_SPEED;
		*ny = g->pos_y - g->dir_x * MOVE_SPEED;
	}
}

void	update_player(t_game *g)
{
	double	nx;
	double	ny;

	nx = g->pos_x;
	ny = g->pos_y;
	compute_next_position(g, &nx, &ny);
	apply_movement(g, nx, ny);
	apply_rotation(g);
}

int	key_press(int keycode, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	printf("key_press: %d\n", keycode);
	if (keycode == KEY_ESC)
	{
		cleanup(g);
		exit(0);
	}
	if (keycode == KEY_W)
		g->move_w = 1;
	if (keycode == KEY_S)
		g->move_s = 1;
	if (keycode == KEY_A)
		g->move_a = 1;
	if (keycode == KEY_D)
		g->move_d = 1;
	if (keycode == KEY_LEFT)
		g->rot_l = 1;
	if (keycode == KEY_RIGHT)
		g->rot_r = 1;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	printf("key_release: %d\n", keycode);
	if (keycode == KEY_W)
		g->move_w = 0;
	if (keycode == KEY_S)
		g->move_s = 0;
	if (keycode == KEY_A)
		g->move_a = 0;
	if (keycode == KEY_D)
		g->move_d = 0;
	if (keycode == KEY_LEFT)
		g->rot_l = 0;
	if (keycode == KEY_RIGHT)
		g->rot_r = 0;
	return (0);
}

int	loop_hook(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	update_player(g);
	render(g);
	return (0);
}
