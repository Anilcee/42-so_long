#include "so_long.h"

void init_player(t_player *player)
{
    player->collected = 0;
    player->moves = 0;
    player->x = 0;  // Başlangıç koordinatları
    player->y = 0;
    player->image = NULL;  // İmaj başlatma
}

void init_game(t_game *game)
{
    if (!game)
        return;

    game->size_x = 0;
    game->size_y = 0;
    game->mlx = NULL;
    game->win = NULL;

    init_player(game->player);

    game->map->rows = 0;
    game->map->cols = 0;
    game->map->collectables = 0;
    game->map->map = NULL;
}

