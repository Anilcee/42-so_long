#ifndef SO_LONG_H
# define SO_LONG_H
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "minilibx/mlx.h"
#include "libft/get_next_line.h"

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

void load_map(t_map *map, const char *file_path, t_player *player);
void draw_map(t_game *game);
int move_player(int key, t_game *game);
void check_move(t_game *game, int new_x, int new_y);
int close_window(void *param);
#endif