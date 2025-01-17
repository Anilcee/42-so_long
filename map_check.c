#include "so_long.h"

void is_rectungular_map(t_map *map)
{
    int y;

    y = 0;

    while (y < map->rows)
    {
        if (ft_strlen(map->map[y]) != ft_strlen(map->map[0]))
        {
            printf("Row %d: %s  length:%ld \n", y, map->map[y], ft_strlen(map->map[y]));
            printf("Row 0: %s  length:%ld \n", map->map[0], ft_strlen(map->map[0]));
            perror("Error: Map is not rectangular");
            exit(EXIT_FAILURE);
        }
        y++;
    }
}

void is_surrounded_by_walls(t_map *map)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < map->cols)
    {
        if (map->map[0][x] != '1' || map->map[map->rows - 1][x] != '1')
        {
            perror("Error: Map borders are not surrounded by walls");
            exit(EXIT_FAILURE);
        }
        x++;
    }
    while (y < map->rows)
    {
        if (map->map[y][0] != '1' || map->map[y][map->cols - 1] != '1')
        {
            perror("Error: Map borders are not surrounded by walls");
            exit(EXIT_FAILURE);
        }
        y++;
    }
}

void check_file_extension(char *file_path)
{
    file_path = file_path + ft_strlen(file_path) - 4;
    if (ft_strncmp(file_path, ".ber", 4) != 0)
    {
        ft_putstr_fd("Error\nInvalid file extension must be .ber\n", 2);
        exit(EXIT_FAILURE);
    }
}


void find_player_position(t_map *map, t_player *player)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < map->rows)
    {
        x = 0;
        while (x < map->cols)
        {
            if (map->map[y][x] == 'P')
            {
                player->x = x;
                player->y = y;
                return;
            }
            x++;
        }
        y++;
    }
}


void is_valid_map(t_game *game)
{
    t_map *map = game->map;
    t_player *player = game->player;

    // Harita dosyasını kontrol et.
    if (!map->map)
    {
        perror("Error: Map is empty");
        exit(EXIT_FAILURE);
    }

    find_player_position(map, player);

    if (player->x == -1 || player->y == -1)
    {
        perror("Error: Player not found");
        exit(EXIT_FAILURE);
    }

    count_collectables(map);
    is_rectungular_map(map);
    is_surrounded_by_walls(map);
}
