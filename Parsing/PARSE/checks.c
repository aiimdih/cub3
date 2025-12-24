#include "../includes/cub3d.h"

int	allowed_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

int	is_dir(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
int	is_whitespace(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	return (0);
}
int	is_valid_path_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_' || c == '-' || c == '.' || c == '/')
		return (1);
	return (0);
}

void	validate_tex_ext(t_map *data, t_mlx *mlx)
{
	if (!has_xpm_ext(data->no_path)
		|| !has_xpm_ext(data->so_path)
		|| !has_xpm_ext(data->we_path)
		|| !has_xpm_ext(data->ea_path))
		ft_error("Texture files must have .xpm extension", mlx);
}
