#ifndef SO_LONG_H
# define SO_LONG_H
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "minilibx/mlx.h"
#include "libft/get_next_line.h"

#define TILE_SIZE 64

#define W 119
#define A 97
#define S 115
#define D 100
#define ESC 65307

typedef struct s_map
{
    void *background;
    char **map;
    int rows;
    int cols;
    int collectables;
    int valid_collectables;
    int valid_exit;
    int **visited;
} t_map;

typedef struct s_player
{
    void *image;
    int x;
    int y;
    int collected;
    int moves;
} t_player;

typedef struct s_game
{
    void *mlx;
    void *win;
    int size_x;
    int size_y;
    t_map *map;
    t_player *player;
} t_game;

void load_map(t_map *map, const char *file_path);
void draw_map(t_game *game);
void init_player(t_player *player);
void init_game(t_game *game);
void check_file_extension(char *file_path);
int check_valid_path(t_map *map, char **visited, int x, int y);
void dfs(t_game *game, int row, int col, int **visited);
void is_rectungular_map(t_map *map);
void is_surronded_by_walls(t_map *map);
void is_valid_map(t_game *game);
void find_player_position(t_map *map, t_player *player);
void count_collectables(t_map *map);
int move_player(int key, t_game *game);
void check_move(t_game *game, int new_x, int new_y);
int close_window(t_game *game);
void free_map(t_map *map);
void free_images(void *mlx, void *wall_img, void *player_img, void *collectible_img, void *exit_img, void *background_img);
#endif