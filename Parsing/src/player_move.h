/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:56:20 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/07 15:41:41 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_MOVE_H
# define PLAYER_MOVE_H

# include "../includes/cub3d_render.h"

void	apply_movement(t_game *g, double nx, double ny);
void	apply_rotation(t_game *g);
int		close_window(void *param);
void	cleanup(t_game *g);

#endif
