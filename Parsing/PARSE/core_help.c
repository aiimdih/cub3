#include "../includes/cub3d.h"

char	**skip_config(char **lines, int *gaps)
{
	int	up_lines;

	up_lines = 0;
	while (*lines && up_lines != 6)
	{
		if (is_blank(*lines))
			(*gaps)++;
		else
			up_lines++;
		lines++;
	}
	while (*lines && is_blank(*lines))
	{
		(*gaps)++;
		lines++;
	}
	return (lines);
}

void	load_textures(t_map *data, char **content)
{
	char	*line;

	line = find_line(content, "NO ");
	data->no_path = clean_path(line, "NO");
	line = find_line(content, "SO ");
	data->so_path = clean_path(line, "SO");
	line = find_line(content, "WE ");
	data->we_path = clean_path(line, "WE");
	line = find_line(content, "EA ");
	data->ea_path = clean_path(line, "EA");
}

int	has_xpm_ext(char *path)
{
	size_t	len;
	char	*xpm_pos;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strcmp(path + len - 4, ".xpm") != 0)
		return (0);
	xpm_pos = ft_strnstr(path, ".xpm", len);
	if (xpm_pos && xpm_pos != path + len - 4)
		return (0);
	return (1);
}

void ensure_walls(t_map *map, t_mlx *mlx)
{
    int i;
	int j;
    
    i = 0;
    map->height = count_lines(map->map);
    while (map->map[i])
    {
        if (side_walls(map->map[i]))
            ft_error("Error\nIssue reading map (side walls)", mlx); 
        j = 0;
        while (map->map[i][j] && map->map[i][j] != '\n')
        {
            if ((i == 0 || i == map->height - 1) &&      
                (map->map[i][j] != '1' && map->map[i][j] != ' ' &&              
                 edge_closure(map->map, i, -1))) 
                ft_error("Error\nMap is not enclosed.", mlx);

            else if (!allowed_char(map->map[i][j]))
                ft_error("Error\nWrong Character.", mlx);
            
            j++;
        }
        i++;
    }
    map->width = max_width(map->map);
}
