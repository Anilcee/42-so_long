#include "so_long.h"

int close_window(t_game *game)
{
    free_map(game->map);
    if (game->mlx)
    {
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }

    exit(0);
    return (0);
}

void free_images(void *mlx, void *wall_img, void *player_img, void *collectible_img, void *exit_img, void *background_img)
{
    if (wall_img)
        mlx_destroy_image(mlx, wall_img);
    if (player_img)
        mlx_destroy_image(mlx, player_img);
    if (collectible_img)
        mlx_destroy_image(mlx, collectible_img);
    if (exit_img)
        mlx_destroy_image(mlx, exit_img);
    if (background_img)
        mlx_destroy_image(mlx, background_img);
}
void free_map(t_map *map)
{
    if (map && map->map)
    {
        for (int i = 0; i < map->rows; i++)
        {
            free(map->map[i]);
        }
        free(map->map);
    }
}
