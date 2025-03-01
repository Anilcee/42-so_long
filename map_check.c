/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:27:52 by ancengiz          #+#    #+#             */
/*   Updated: 2025/03/01 17:28:42 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			{
				free_map(map);
				exit_with_error("Error: Invalid object found in map");
			}
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
	{
		free_map(map);
		exit_with_error("Error: There must be exactly one exit in the map.");
	}
	if (map->player != 1)
	{
		free_map(map);
		exit_with_error("Error: There must be exactly one player in the map.");
	}
	if (map->coin == 0)
	{
		free_map(map);
		exit_with_error("Error: There must be at least one coin in the map.");
	}
	if (map->exit != map->valid_exit || map->valid_coin != map->coin)
	{
		free_map(map);
		exit_with_error("Error: Not all coins or exit are reachable");
	}
}
