#include "so_long.h"

void load_map(t_map *map, const char *file_path, t_player *player)
{
    int fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        exit(1);
    }

    map->rows = 0;
    map->cols = 0;
    map->map = NULL;

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (map->rows == 0)
            map->cols = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n' ? 1 : 0);

        char **temp = realloc(map->map, sizeof(char *) * (map->rows + 1));
        if (!temp)
        {
            perror("Error allocating memory for map");
            exit(1);
        }
        map->map = temp;
        map->map[map->rows] = line;

        // Oyuncu pozisyonunu harita üzerinde bulalım
        for (int x = 0; x < map->cols; x++)
        {
            if (line[x] == 'P')
            {
                player->x = x;
                player->y = map->rows;
            }
        }

        map->rows++;
    }

    close(fd);
}


void draw_map(t_game *game)
{
    int tile_size = 32;
    void *wall_img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &tile_size, &tile_size);
    void *player_img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &tile_size, &tile_size);
    void *collectible_img = mlx_xpm_file_to_image(game->mlx, "textures/collectable.xpm", &tile_size, &tile_size);
    void *exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &tile_size, &tile_size);

    if (!wall_img || !player_img || !collectible_img || !exit_img)
    {
        fprintf(stderr, "Error: Could not load images\n");
        exit(1);
    }

    // Haritayı ve diğer öğeleri çiz
    for (int y = 0; y < game->map->rows; y++)
    {
        for (int x = 0; x < game->map->cols; x++)
        {
            if (game->map->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, wall_img, x * tile_size, y * tile_size);
            else if (game->map->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, collectible_img, x * tile_size, y * tile_size);
            else if (game->map->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, exit_img, x * tile_size, y * tile_size);
        }
    }

    // Oyuncuyu çiz
    mlx_put_image_to_window(game->mlx, game->win, player_img, game->player->x * tile_size, game->player->y * tile_size);
}

