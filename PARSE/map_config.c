#include "../includes/cub3d.h"


static char	*finalize_path(char *new_path, char *ref)
{
	if (!new_path || !*new_path)
	{
		free(ref);
		return (NULL);
	}
	if (!validate_path_chars(new_path))
	{
		free(ref);
		free(new_path);
		return (NULL);
	}
	free(ref);
	return (new_path);
}

char	*clean_path(char *path, char *prefix)
{
	char	*new_path;
	char	*helper;
	char	*ref;

	if (!path)
		return (NULL);
	while (is_whitespace(*path))
		path++;
	ref = ft_strtrim(path, "\n");
	helper = ref;
	while (*helper == *prefix)
	{
		helper++;
		prefix++;
	}
	while (is_whitespace(*helper))
		helper++;
	new_path = ft_strtrim(helper, " ");
	return (finalize_path(new_path, ref));
}

static int	extract_number(char **line)
{
	char	*temp;
	int		len;
	int		val;

	while (**line && (**line < '0' || **line > '9'))
		(*line)++;
	len = 0;
	while ((*line)[len] >= '0' && (*line)[len] <= '9')
		len++;
	temp = ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(temp, *line, len + 1);
	val = ft_atoi(temp);
	if (is_blank(temp) || val < 0 || val > 255)
		val = -1;
	free(temp);
	*line += len;
	return (val);
}

int	*string_to_rgb(char *line)
{
	int		*rgb;
	int		idx;

	rgb = ft_calloc(sizeof(int), 3);
	if (!rgb)
		return (NULL);
	idx = 0;
	while (idx < 3)
	{
		rgb[idx] = extract_number(&line);
		if (rgb[idx] == -1)
		{
			free(rgb);
			return (NULL);
		}
		idx++;
	}
	return (rgb);
}

int	*load_color(char **content, char *key)
{
	int		i;
	int		j;

	i = 0;
	while (content[i])
	{
		j = 0;
		while (content[i][j] && content[i][j] == ' ')
			j++;
		if (ft_strncmp(content[i] + j, key, ft_strlen(key)) == 0
			&& color_syntax(content[i] + j, key[0]))
			return (string_to_rgb(content[i] + j));
		i++;
	}
	return (NULL);
}
