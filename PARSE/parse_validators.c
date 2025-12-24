#include "../includes/cub3d.h"

void	validate_player(t_map *map, t_mlx *mlx)
{
	int		y;
	int		x;
	int		plyr_cnt;

	y = 0;
	plyr_cnt = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] != '0' && map->map[y][x] != '1'
				&& map->map[y][x] != '\n' && map->map[y][x] != ' ')
			{
				if (!is_dir(map->map[y][x]))
					ft_error("Invalid character.", mlx);
				process_player_char(&plyr_cnt, mlx);
				set_player_pos(map, x, y);
			}
			x++;
		}
		y++;
	}
	if (plyr_cnt != 1)
		ft_error("No player found.", mlx);
}

static void get_first_token(char *line, char **start, int *len)
{
    int i;

    i = 0;
    while (line[i] && is_whitespace(line[i]))
        i++;
    if (!line[i])
    {
        *start = NULL;
        *len = 0;
        return;
    }
    *start = &line[i];
    *len = 0;
    while (line[i] && !is_whitespace(line[i]))
    {
        (*len)++;
        i++;
    }
}

static int count_key_occurrences(char **content, char *key)
{
    int i;
    int count;
    int namelen;
    char *start;
    int tlen;

    i = 0;
    count = 0;
    namelen = ft_strlen(key);
    if (namelen > 0 && key[namelen - 1] == ' ')
        namelen--;
    while (content[i])
    {
        get_first_token(content[i], &start, &tlen);
        if (start && tlen == namelen 
            && ft_strncmp(start, key, namelen) == 0)
            count++;
        i++;
    }
    return (count);
}

static void	free_and_error(char **content, char *msg, t_mlx *mlx)
{
	free_arr(content);
	ft_error(msg, mlx);
}

void	check_duplicate_config(char **content, t_mlx *mlx)
{
	if (count_key_occurrences(content, "NO ") != 1)
		free_and_error(content, "Duplicate or missing NO texture", mlx);
	if (count_key_occurrences(content, "SO ") != 1)
		free_and_error(content, "Duplicate or missing SO texture", mlx);
	if (count_key_occurrences(content, "WE ") != 1)
		free_and_error(content, "Duplicate or missing WE texture", mlx);
	if (count_key_occurrences(content, "EA ") != 1)
		free_and_error(content, "Duplicate or missing EA texture", mlx);
	if (count_key_occurrences(content, "F ") != 1)
		free_and_error(content, "Duplicate or missing F color", mlx);
	if (count_key_occurrences(content, "C ") != 1)
		free_and_error(content, "Duplicate or missing C color", mlx);
}
/*
static void	get_first_token(const char *line, const char **start, int *len)
{
	int j;

	j = 0;
	while (line[j] && is_whitespace(line[j]))
		j++;
	if (!line[j])
	{
		*start = NULL;
		*len = 0;
		return;
	}
	*start = line + j;
	*len = 0;
	while ((*start)[*len] && !is_whitespace((*start)[*len]))
		(*len)++;
}

static int	count_key_occurrences(char **content, char *key)
{
	int i;
	int count;
	size_t keylen;
	size_t namelen;
	char *keyname;
	const char *start;
	int tlen;

	i = 0;
	count = 0;
	keylen = ft_strlen(key);
	if (keylen > 0 && key[keylen - 1] == ' ')
		namelen = keylen - 1;
	else
		namelen = keylen;
	keyname = (char *)key;
	while (content[i])
	{
		get_first_token(content[i], &start, &tlen);
		if (start && (size_t)tlen == namelen
			&& ft_strncmp(start, keyname, namelen) == 0)
			count++;
		i++;
	}
	return (count);
}*/


