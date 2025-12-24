#include "../includes/cub3d.h"

void	verify_floor(char **map, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || is_dir(map[i][j]))
			{
				if (i == 0 || !map[i + 1])
					ft_error("Map is not enclosed.", mlx);
				if ((int)ft_strlen(map[i - 1]) <= j
					|| (int)ft_strlen(map[i + 1]) <= j
					|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
					ft_error("Map is not enclosed.", mlx);
				if ((j > 0 && map[i][j - 1] == ' ')
					|| (map[i][j + 1] && map[i][j + 1] == ' '))
					ft_error("Map is not enclosed.", mlx);
			}
			j++;
		}
		i++;
	}
}
/*
void	verify_floor(char **map, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' && map[i - 1]
			&& map[i + 1])
			{
				if (!map[i - 1][j] || !map[i + 1][j]
					|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
					ft_error("Map is not enclosed.", mlx);
			}
			j++;
		}
		i++;
	}
}*/

int	horizontal_enclosure(char *line, t_pos pos, int inc, char **map)
{
	t_pos	check;
	int		vert_inc;

	pos.col += inc;
	while (line[pos.col] && line[pos.col] == ' ')
	{
		vert_inc = 1;
		while (vert_inc >= -1)
		{
			check = pos;
			check.row += vert_inc;
			while (map[check.row] && (int)ft_strlen(map[check.row]) > check.col
				&& map[check.row][check.col] == ' ')
				check.row += vert_inc;
			if (map[check.row] && (int)ft_strlen(map[check.row]) > check.col
				&& map[check.row][check.col] != '1')
				return (1);
			vert_inc -= 2;
		}
		pos.col += inc;
	}
	if (line[pos.col] && line[pos.col] != '1')
		return (1);
	return (0);
}
/*
int	horizontal_enclosure(char *line, t_pos pos, int inc, char **map)
{
	t_pos	check;
	int		vert_inc;
	int		len;

	pos.col += inc;
	len = ft_strlen(line);
	while (pos.col >= 0 && pos.col < len && line[pos.col] == ' ')
	{
		vert_inc = 1;
		while (vert_inc >= -1)
		{
			check = pos;
			check.row += vert_inc;
			while (map[check.row] && check.col >= 0
				&& check.col < (int)ft_strlen(map[check.row])
				&& map[check.row][check.col] == ' ')
				check.row += vert_inc;
			if (map[check.row] && check.col >= 0
				&& check.col < (int)ft_strlen(map[check.row])
				&& map[check.row][check.col] != '1')
				return (1);
			vert_inc -= 2;
		}
		pos.col += inc;
	}
	if (pos.col < 0 || pos.col >= len)
		return (1);
	if (line[pos.col] && line[pos.col] != '1')
		return (1);
	return (0);
}*/

static int	scan_row_neighbors(char **map, int row, int dy, int col)
{
	t_pos	pos;

	pos.row = row + dy;
	pos.col = col;
	if (horizontal_enclosure(map[pos.row], pos, -1, map))
		return (1);
	else if (horizontal_enclosure(map[pos.row], pos, 1, map))
		return (1);
	return (0);
}

static int	check_vertical_space(char **map, int row, int col, int dy)
{
	int	step;

	step = dy;
	while (map[row + dy] && (int)ft_strlen(map[row + dy]) > col
		&& map[row + dy][col] == ' ')
	{
		if (scan_row_neighbors(map, row, dy, col))
			return (1);
		dy += step;
	}
	if (map[row + dy] && (int)ft_strlen(map[row + dy]) > col
		&& map[row + dy][col] != '1')
		return (1);
	return (0);
}

int	edge_closure(char **map, int row, int col)
{
	int	dy;

	while (map[row][++col])
	{
		if (map[row][col] == '0')
			return (1);
		if (map[row][col] != ' ')
			continue;
		if (row == 0)
			dy = 1;
		else
			dy = -1;
		if (check_vertical_space(map, row, col, dy))
			return (1);
	}
	return (0);
}
/*
int	edge_closure(char **map, int row, int col)
{
	int	dy;
	int	step;

	       while (map[row][++col])
	       {
		       if (map[row][col] == '0' || is_dir(map[row][col]))
			       return (1);
		       if (map[row][col] != ' ')
			       continue;
		       if (row == 0)
			       dy = 1;
		       else
			       dy = -1;
		       step = dy;
		       while (map[row + dy] && col < (int)ft_strlen(map[row + dy]) && map[row + dy][col] == ' ')
		       {
			       if (scan_row_neighbors(map, row, dy, col))
				       return (1);
			       dy += step;
		       }
		       if (map[row + dy] && col < (int)ft_strlen(map[row + dy]) && map[row + dy][col] != '1')
			       return (1);
	       }
	       return (0);
}*/

/*
int edge_closure(char **map, int row, int col)
{
    int dy;
    int step;

    while (map[row][col] && map[row][col] == ' ')
        col++;
    while (map[row][col])
    {
        if (map[row][col] == '0')
            return (1);
        
        if (map[row][col] != ' ')
        {
            col++;
            continue;
        }
        if (row == 0)
            dy = 1;
        else
            dy = -1;
        step = dy;
        while (map[row + dy] && map[row + dy][col]
            && map[row + dy][col] == ' ')
        {
            if (scan_row_neighbors(map, row, dy, col))
                return (1);
            dy += step;
        }
        if (map[row + dy] && map[row + dy][col] 
            && map[row + dy][col] != '1')
            return (1);
        col++;
    }
    return (0);
}*/
