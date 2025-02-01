#include "so_long.h"

void load_map(t_map *map, const char *file_path)
{
    char *line;
    char *temp;
    int fd = open(file_path, O_RDONLY);
    if (fd < 0)
        perror("Error opening file");
    map->rows = 0;
    map->cols = 0;
    map->map = NULL;
    line = ft_strdup("");
    while ((temp = get_next_line(fd)) != NULL)
    {
        line=ft_strjoin(line,temp);
        free(temp);
    }
    map->map=ft_split(line, '\n');
    free(line);
    for (int i = 0; map->map[i]; i++)
    {
        map->rows++;
        if (map->cols == 0)
            map->cols = ft_strlen(map->map[i]);
    }
    count_collectables(map);
    close(fd);
}
void count_collectables(t_map *map)
{
    int x;
    int y;

    x = 0;
    y = 0;
    map->collectables = 0;
    while (y < map->rows)
    {
        x = 0;
        while (x < map->cols)
        {
            if (map->map[y][x] == 'C')
                map->collectables++;
            x++;
        }
        y++;
    }
}



void draw_map(t_game *game)
{
    int tile_size = 64; // 64x64 boyutları
    void *wall_img = mlx_xpm_file_to_image(game->mlx, "textures/blueblock64.xpm", &tile_size, &tile_size);
    void *player_img = mlx_xpm_file_to_image(game->mlx, "textures/pacman64.xpm", &tile_size, &tile_size);
    void *collectible_img = mlx_xpm_file_to_image(game->mlx, "textures/pacdot_food.xpm", &tile_size, &tile_size);
    void *exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit64.xpm", &tile_size, &tile_size);
    void *background_img = mlx_xpm_file_to_image(game->mlx, "textures/floor64.xpm", &tile_size, &tile_size);
    mlx_clear_window(game->mlx, game->win);
    if (!wall_img || !player_img || !collectible_img || !exit_img || !background_img)
    {
        perror("Error loading textures");
        free_images(game->mlx, wall_img, player_img, collectible_img, exit_img, background_img);
        exit(1);
    }
        
    // Haritayı çizerken, her seferinde sadece arka planı ve diğer öğeleri çiz

    for (int y = 0; y < game->map->rows; y++)
    {
        for (int x = 0; x < game->map->cols; x++)
        {
            if (game->map->map[y][x] == '0')
                continue;
            if(game->map->map[y][x] == 'P')
            {
            
                game->player->x = x;
                game->player->y = y;
                mlx_put_image_to_window(game->mlx, game->win, player_img, x * tile_size, y * tile_size);
            }
            else if (game->map->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, wall_img, x * tile_size, y * tile_size);
            else if (game->map->map[y][x] == 'C')
            {
                mlx_put_image_to_window(game->mlx, game->win, collectible_img, x * tile_size, y * tile_size);
            }
            else if (game->map->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, exit_img, x * tile_size, y * tile_size);
        }
    }

    mlx_put_image_to_window(game->mlx, game->win, background_img, game->player->x * tile_size, game->player->y * tile_size);
    // Yeni pozisyonda oyuncuyu çiz
    mlx_put_image_to_window(game->mlx, game->win, player_img, game->player->x * tile_size, game->player->y * tile_size);
    free_images(game->mlx, wall_img, player_img, collectible_img, exit_img, background_img);

}
