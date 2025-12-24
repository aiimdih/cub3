#include "../includes/cub3d.h"

void free_arr(char **arr)
{
    int i;
    
    if (!arr)
        return;
    
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int	is_blank(char *line)
{
	int	i;
	int	has_content;

	i = 0;
	has_content = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			has_content++;
		i++;
	}
	return (has_content == 0);
}

int	count_lines(char **map)
{
	int	i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	max_width(char **map)
{
	int	max;
	int	i;
	int	row_len;

	max = 0;
	i = 0;
	while (map[i])
	{
		row_len = ft_strlen(map[i]);
		if (row_len > max)
			max = row_len;
		i++;
	}
	return (max);
}

int	side_walls(char *line)
{
	char	last_char;

	last_char = '\0';
	while (*line && *line == ' ')
		line++;
	if (!*line || *line == '\n')
		return (0);
	if (*line && *line != '1')
		return (1);
	while (*line && *line != '\n')
	{
		if (*line != ' ')
			last_char = *line;
		line++;
	}
	if (last_char != '1')
		return (1);
	return (0);
}


