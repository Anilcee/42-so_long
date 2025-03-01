/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:28:12 by ancengiz          #+#    #+#             */
/*   Updated: 2025/03/01 17:28:13 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define T_S 64

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

typedef struct s_images
{
	void	*p_img;
	void	*p_left;
	void	*p_right;
	void	*p_up;
	void	*p_down;
	void	*wall;
	void	*exit;
	void	*coin;
}	t_images;

typedef struct s_map
{
	void	*background;
	char	**map;
	int		rows;
	int		cols;
	int		coin;
	int		exit;
	int		player;
	int		valid_coin;
	int		valid_exit;
}	t_map;

typedef struct s_player
{
	void	*image;
	int		x;
	int		y;
	int		collected;
	int		moves;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			size_x;
	int			size_y;
	t_map		*map;
	t_player	*player;
	t_images	*img;
}	t_game;

void	load_map(t_map *map, const char *file_path);
void	draw_map(t_game *game);
void	init_player(t_player *player);
void	init_game(t_game *game);
int		**create_visited(t_map *map);
void	check_file_extension(char *file_path);
int		check_valid_path(t_map *map, char **visited, int x, int y);
void	check_invalid_objects(t_map *map);
void	check_objects_in_map(t_map *map);
void	dfs(t_game *game, int row, int col, int **visited);
void	dfs_coin(t_game *game, int row, int col, int **visited);
void	check_counters(t_map *map);
void	is_rectungular_map(t_map *map);
void	is_surronded_by_walls(t_map *map);
void	is_valid_map(t_game *game);
void	find_player_position(t_game *game);
void	count_map_objects(t_map *map);
int		move_player(int key, t_game *game);
void	check_move(t_game *game, int new_x, int new_y, int key);
int		close_window(t_game *game);
void	free_map(t_map *map);
void	free_images(t_game *game);
void	free_visited(int **array, t_map *map);
void	check_win(t_game *game);
void	exit_with_error(char *msg);
void	*convert_image(t_game *game, char *relative_path);
void	init_images(t_game *game);
#endif