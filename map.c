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

        // Haritayı tutacak geçici bir dizi oluşturuyoruz
        char **new_map = malloc(sizeof(char *) * (map->rows + 1));
        if (!new_map)
        {
            perror("Error allocating memory for map");
            exit(1);
        }

        // Önceki haritayı kopyala (bu kısım önemli)
        for (int i = 0; i < map->rows; i++)
        {
            new_map[i] = map->map[i];
        }

        // Yeni satırı ekle
        new_map[map->rows] = line;

        // Eski haritayı serbest bırak ve yeni haritayı at
        if (map->map)
            free(map->map);

        map->map = new_map;

        // Oyuncu pozisyonunu harita üzerinde bulalım
        for (int x = 0; x < map->cols; x++)
        {
            if (line[x] == 'P')
            {
                player->x = x;
                player->y = map->rows;
            }
            if (line[x] == 'C')
            {
                map->collectables++;
                printf("Collectable founds %d\n", map->collectables);
            }
        }

        map->rows++;
    }

    close(fd);
}




void draw_map(t_game *game)
{
    int tile_size = 3;
    void *wall_img = mlx_xpm_file_to_image(game->mlx, "textures/wall64.xpm", &tile_size, &tile_size);
    void *player_img = mlx_xpm_file_to_image(game->mlx, "textures/player64.xpm", &tile_size, &tile_size);
    void *collectible_img = mlx_xpm_file_to_image(game->mlx, "textures/collectable64.xpm", &tile_size, &tile_size);
    void *exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit64.xpm", &tile_size, &tile_size);
    void *background_img = mlx_xpm_file_to_image(game->mlx, "textures/floor64.xpm", &tile_size, &tile_size);

    if (!wall_img || !player_img || !collectible_img || !exit_img)
        exit(1);

    // Pencereyi temizle
    mlx_clear_window(game->mlx, game->win);

    // Arka planı önce çizelim
    for (int y = 0; y < game->map->rows; y++)
    {
        for (int x = 0; x < game->map->cols; x++)
        {
            mlx_put_image_to_window(game->mlx, game->win, background_img, x * tile_size, y * tile_size);
        }
    }

    // Diğer öğeleri ekleyelim
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

    // Oyuncuyu en son ekleyelim
    mlx_put_image_to_window(game->mlx, game->win, player_img, game->player->x * tile_size, game->player->y * tile_size);
}
