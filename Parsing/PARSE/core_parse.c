#include "../includes/cub3d.h"

void	check_no_gaps(char **map, t_mlx *mlx)
{
	int	i;
	int	has_gap;

	i = 0;
	has_gap = 0;
	while (map[i])
	{
		if (is_blank(map[i]))
			has_gap = 1;
		if (!is_blank(map[i]) && has_gap)
			ft_error("Map is not together.", mlx);
		i++;
	}
}

char	**load_lines(int fd)
{
	char	**map;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	map = ft_calloc(sizeof(char *), 1);
	map[0] = NULL;
	while (line)
	{
		map = grow_array(map, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (map);
}

void	run_checks(t_map *map, t_mlx *mlx)
{
	validate_map_whitespace(map, mlx);
	ensure_walls(map, mlx);
	verify_floor(map->map, mlx);
	check_no_gaps(map->map, mlx);
}

t_map	*build_map(t_mlx *mlx, char **content)
{
	t_map	*data;

	data = ft_calloc(sizeof(t_map), 1);
	mlx->map = data;
	check_duplicate_config(content, mlx);
	load_textures(data, content);
	data->floor_color = load_color(content, "F ");
	data->ceiling_color = load_color(content, "C ");
	data->map = isolate_map(content);
	free_arr(content);
	if (!data->no_path || !data->so_path
		|| !data->ea_path || !data->we_path)
		ft_error("Error\nInvalid texture path", mlx);
	validate_tex_ext(data, mlx);
	if (!data->floor_color || !data->ceiling_color)
		ft_error("Error\nInvalid RGB color format or values", mlx);
	return (data);
}

void	parse_map(char *file, t_mlx *mlx)
{
	int		fd;
	char	**f_content;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file\n");
		exit(1);
	}
	if (cub_extension(file))
	{
		printf("Error\nInvalid file extension (must be .cub)\n");
		exit(1);
	}
	f_content = load_lines(fd);
	if (!f_content)
	{
		printf("Error\nEmpty or unreadable file\n");
		exit(1);
	}
	mlx->map = build_map(mlx, f_content);
	run_checks(mlx->map, mlx);
	validate_player(mlx->map, mlx);
}
