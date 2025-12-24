#include "../includes/cub3d.h"

void	validate_map_whitespace(t_map *map, t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '\t')
				ft_error("Error\nTabs not allowed in map", mlx);
			x++;
		}
		y++;
	}
}

int	cub_extension(char *file)
{
	size_t	len;

	if (!file)
		return (1);
	len = ft_strlen(file);
	if (len < 4)
		return (1);
	if (ft_strncmp((file + len - 4), ".cub", 4))
		return (1);
	return (0);
}

int	color_syntax(char *str, char to_find)
{
	int	i;
	int	comma_count;
	int	groups;

	i = 0;
	comma_count = 0;
	groups = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		else if (ft_isdigit(str[i]))
		{
			if (i == 0 || !ft_isdigit(str[i - 1]))
				groups++;
		}
		else if (str[i] != to_find && !is_whitespace(str[i])
			&& !ft_isdigit(str[i]) && str[i] != ',')
			return (0);
		i++;
	}
	if (comma_count != 2 || groups > 3)
		return (0);
	return (1);
}
void	set_player_pos(t_map *map, int x, int y)
{
	map->player_x = x;
	map->player_y = y;
	map->player_dir = map->map[y][x];
}

void	process_player_char(int *plyr_cnt, t_mlx *mlx)
{
	(*plyr_cnt)++;
	if (*plyr_cnt > 1)
		ft_error("Multiple players found.", mlx);
}