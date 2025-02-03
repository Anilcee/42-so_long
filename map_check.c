#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// map_check.c içinde
void dfs(t_game *game, int row, int col, int **visited) { // visited parametresi eklendi
    if (row < 0 || row >= game->map->rows || col < 0 || col >= game->map->cols) 
        return;
    
    if (visited[row][col] || game->map->map[row][col] == '1') 
        return;
    
    if (game->map->map[row][col] == 'C')
        game->map->valid_collectables++;
    if (game->map->map[row][col] == 'E')
        game->map->valid_exit=1;
    visited[row][col] = 1;
    
    // Tüm çağrılara visited parametresini ekleyin
    dfs(game, row - 1, col, visited);
    dfs(game, row + 1, col, visited);
    dfs(game, row, col - 1, visited);
    dfs(game, row, col + 1, visited);
}


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


void is_valid_map(t_game *game) {
    t_map *map = game->map;
    t_player *player = game->player;

    if (!map->map) {
        perror("Error: Map is empty");
        exit(EXIT_FAILURE);
    }

    find_player_position(map, player);

    if (player->x == -1 || player->y == -1) {
        perror("Error: Player not found");
        exit(EXIT_FAILURE);
    }

    int **visited = malloc(map->rows * sizeof(int *));
    for (int i = 0; i < map->rows; i++) {
        visited[i] = malloc(map->cols * sizeof(int));
        memset(visited[i], 0, map->cols * sizeof(int));
    }

    // DFS'i başlat (visited parametresi eklendi)
    dfs(game, player->y, player->x, visited); // Dikkat: y satır, x sütun!
    printf("Collectables: %d\n", map->collectables);
    printf("Valid Collectables: %d\n", map->valid_collectables);

    // Belleği temizle
    for (int i = 0; i < map->rows; i++) {
        free(visited[i]);
    }
    free(visited);
    if (map->collectables != map->valid_collectables)
    {
        perror("Error: Invalid collectables");
        exit(EXIT_FAILURE);
    }
    if (!map->valid_exit)
    {
        perror("Error: Exit not found");
        exit(EXIT_FAILURE);
    }
    is_rectungular_map(map);
    is_surrounded_by_walls(map);
}
