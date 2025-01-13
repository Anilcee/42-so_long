#ifndef SO_LONG_H
# define SO_LONG_H
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "minilibx/mlx.h"
#include "libft/get_next_line.h"

typedef struct s_map
{
    char **map;
    int rows;
    int cols;
} t_map;

typedef struct s_player
{
    int x;
    int y;
    void *image;
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
#endif