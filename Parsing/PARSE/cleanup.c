#include "../includes/cub3d.h"

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->we_path)
		free(map->we_path);
	if (map->floor_color)
		free(map->floor_color);
	if (map->ceiling_color)
		free(map->ceiling_color);
	if (map->map)
		free_arr(map->map);
	free(map);
}

int	free_mlx(t_mlx *mlx)
{
	if (!mlx)
		return (0);
	if (mlx->map)
		free_map(mlx->map);
	//You can free here other mlx things
	return (0);
}

int	ft_error(char *errormsg, t_mlx *mlx)
{
	printf("%s\n", errormsg);
	if (mlx)
		free_mlx(mlx);
	exit(1);
}

void	copy_str(char **dst, char **src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
}

char	**grow_array(char **map, char *line)
{
	char	**new_map;
	int		curr_size;
	int		new_size;

	curr_size = count_lines(map);
	new_size = curr_size + 2;
	new_map = ft_calloc(sizeof(char *), new_size);
	if (!new_map)
		exit(1);
	if (curr_size != 0)
		copy_str(new_map, map);
	new_map[curr_size] = ft_strdup(line);
	new_map[curr_size + 1] = NULL;
	free_arr(map);
	return (new_map);
}
