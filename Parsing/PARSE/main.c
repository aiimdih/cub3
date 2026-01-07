/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:16:45 by aiimdih           #+#    #+#             */
/*   Updated: 2026/01/07 15:32:33 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_render.h"
#include "../includes/cub3d.h"
#include "../texture.h"

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		ft_error("There must be two arguments.", NULL);
	g = (t_game){0};
	parse_map(argv[1], &g.mlx_map);
	if (!g.mlx_map.map->map)
		return (1);
	g.mlx = mlx_init();
	if (!g.mlx)
		return (write(2, "mlx_init failed\n", 16), 1);
	g.win = mlx_new_window(g.mlx, SCREEN_W, SCREEN_H,
			"Textured Cub3D - WASD+ Arrows");
	g.screen.img = mlx_new_image(g.mlx, SCREEN_W, SCREEN_H);
	g.screen.addr = mlx_get_data_addr(g.screen.img, &g.screen.bpp,
			&g.screen.line_len, &g.screen.endian);
	init_player_from_map(&g);
	load_texture(&g);
	mlx_hook(g.win, 2, 1L << 0, key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, key_release, &g);
	mlx_hook(g.win, 17, 0, close_window, &g);
	mlx_loop_hook(g.mlx, loop_hook, &g);
	mlx_loop(g.mlx);
	return (0);
}
