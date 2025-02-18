#include "so_long.h"

void	dfs(t_game *game, int row, int col, int **visited)
{
	if (row < 0 || row >= game->map->rows || col < 0 || col >= game->map->cols)
		return ;
	if (visited[row][col] || game->map->map[row][col] == '1')
		return ;
	if (game->map->map[row][col] == 'E')
		game->map->valid_exit = 1;
	visited[row][col] = 1;
	dfs(game, row - 1, col, visited);
	dfs(game, row + 1, col, visited);
	dfs(game, row, col - 1, visited);
	dfs(game, row, col + 1, visited);
}

void	dfs_coin(t_game *game, int row, int col, int **visited)
{
	if (row < 0 || row >= game->map->rows || col < 0 || col >= game->map->cols)
		return ;
	if (visited[row][col] || game->map->map[row][col] == '1'
		|| game->map->map[row][col] == 'E')
		return ;
	if (game->map->map[row][col] == 'C')
		game->map->valid_coin++;
	visited[row][col] = 1;
	dfs_coin(game, row - 1, col, visited);
	dfs_coin(game, row + 1, col, visited);
	dfs_coin(game, row, col - 1, visited);
	dfs_coin(game, row, col + 1, visited);
}

void	count_map_objects(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->map[y][x] == 'C')
				map->coin++;
			else if (map->map[y][x] == 'E')
				map->exit++;
			else if (map->map[y][x] == 'P')
				map->player++;
			x++;
		}
		y++;
	}
}

void	check_invalid_objects(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->map[y][x] == 'C' || map->map[y][x] == 'E' ||
				map->map[y][x] == '0' || map->map[y][x] == '1' ||
				map->map[y][x] == 'P')
				x++;
			else
				exit_with_error("Error: Invalid object found in map");
		}
		y++;
	}
	return ;
}

void	check_objects_in_map(t_map *map)
{
	if (!map->map)
		exit_with_error("Error: Map is empty");
	if (map->exit != 1)
		exit_with_error("Error: A lot of exit");
	if (map->player != 1)
		exit_with_error("Error: A lot of player");
	if (map->valid_exit != 1)
		exit_with_error("Error: A lot of exit");
	if (map->valid_coin != map->coin)
		exit_with_error("Error: Not all coins are reachable");
}
