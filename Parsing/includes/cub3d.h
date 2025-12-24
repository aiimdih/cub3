#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct s_pos
{
	int	row;
	int	col;
}				t_pos;

typedef struct s_map
{
	char	**map;             
	char	*no_path;         
	char	*so_path;           
	char	*we_path;          
	char	*ea_path;          
	int		*floor_color;        
	int		*ceiling_color;     
	int		width;               
	int		height;	              
	int		player_x;             
	int		player_y;          
	char	player_dir;        
}				t_map;

typedef struct s_mlx
{

	t_map		*map;	
	//void		*mlx;	
	//void		*win;	
	//You could add mlx thing that u need 

}			t_mlx;



void	parse_map(char *file, t_mlx *mlx);
void	verify_floor(char **map, t_mlx *mlx);
void	check_no_gaps(char **map, t_mlx *mlx);
void	validate_player(t_map *map, t_mlx *mlx);
void	validate_map_whitespace(t_map *map, t_mlx *mlx);
void	load_textures(t_map *data, char **content);
void	validate_tex_ext(t_map *data, t_mlx *mlx);
void	free_arr(char **arr);
void	copy_str(char **dst, char **src);
void	free_map(t_map *map);
void	ensure_walls(t_map *map, t_mlx *mlx);
void	check_duplicate_config(char **content, t_mlx *mlx);
void	set_player_pos(t_map *map, int x, int y);
void	process_player_char(int *plyr_cnt, t_mlx *mlx);

int		side_walls(char *line);
int		cub_extension(char *file);
int		is_blank(char *line);
int		allowed_char(char c);
int		color_syntax(char *str, char to_find);
int		is_whitespace(char c);
int		edge_closure(char **map, int row, int i);
int		count_lines(char **map);
int		*string_to_rgb(char *line);
int		*load_color(char **read, char *to_find);
int		max_width(char **map);
int		has_xpm_ext(char *path);
int		is_dir(char c);
int		free_mlx(t_mlx *mlx);
int		validate_path_chars(char *path);
int		is_valid_path_char(char c);
int		ft_error(char *errormsg, t_mlx *mlx);
int		horizontal_enclosure(char *line,
				t_pos pos, int inc, char **map);

char	**skip_config(char **lines, int *gaps);
char	*find_line(char **read, char *to_find);
char	**grow_array(char **map, char *buf);
char	**isolate_map(char **lines);
char	*clean_path(char *path, char *prefix);

#endif