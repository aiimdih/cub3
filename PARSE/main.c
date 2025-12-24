#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx		mlx;

	if (argc != 2)
		ft_error("There must be two arguments.", NULL);

	parse_map(argv[1], &mlx);

	if (!mlx.map)
		return (1);

	printf("NO: %s\n", mlx.map->no_path);
	printf("SO: %s\n", mlx.map->so_path);
	printf("WE: %s\n", mlx.map->we_path);
	printf("EA: %s\n", mlx.map->ea_path);
	if (mlx.map->floor_color)
		printf("F: %d,%d,%d\n", mlx.map->floor_color[0], mlx.map->floor_color[1], mlx.map->floor_color[2]);
	if (mlx.map->ceiling_color)
		printf("C: %d,%d,%d\n", mlx.map->ceiling_color[0], mlx.map->ceiling_color[1], mlx.map->ceiling_color[2]);
	printf("Map size: %d x %d\n", mlx.map->width, mlx.map->height);
	printf("Player: (%d, %d) facing %c\n", mlx.map->player_y, mlx.map->player_x, mlx.map->player_dir);

	printf("Map:\n");
	{
		int i = 0;
		while (mlx.map->map && mlx.map->map[i])
		{
			printf("%s", mlx.map->map[i]);
			i++;
		}
	}
    printf("\n");
	free_mlx(&mlx);
	return (0);
}
