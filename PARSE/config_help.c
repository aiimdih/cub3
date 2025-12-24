#include "../includes/cub3d.h"

char	**isolate_map(char **lines)
{
	char	**result;
	char	**map_start;
	int		total;
	int		gaps;

	total = count_lines(lines);
	gaps = 0;
	map_start = skip_config(lines, &gaps);
	result = ft_calloc(sizeof(char *), (total - 6 - gaps + 1));
	if (!result)
		return (NULL);
	copy_str(result, map_start);
	return (result);
}

char	*find_line(char **content, char *pref)
{
	int	i;
	int	j;

	i = 0;
	while (content[i])
	{
		j = 0;
		while (content[i][j] && content[i][j] == ' ')
			j++;
		if (ft_strncmp(content[i] + j, pref, ft_strlen(pref)) == 0)
			return (content[i] + j);
		i++;
	}
	return (NULL);
}

int	validate_path_chars(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (!is_valid_path_char(path[i]))
			return (0);
		i++;
	}
	return (1);
}
