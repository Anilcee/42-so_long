/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:27:56 by ancengiz          #+#    #+#             */
/*   Updated: 2025/03/01 17:27:57 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_with_error(char *msg)
{
	perror (msg);
	exit (1);
}

void	is_rectungular_map(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->rows)
	{
		if (ft_strlen(map->map[y]) != ft_strlen(map->map[0]))
		{
			perror("Error: Map is not rectangular");
			free_map(map);
			exit(EXIT_FAILURE);
		}
		y++;
	}
}

void	is_surrounded_by_walls(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < map->cols)
	{
		if (map->map[0][x] != '1' || map->map[map->rows - 1][x] != '1')
		{
			exit_with_error("Error: Map borders are not surrounded by walls");
			free_map(map);
		}
		x++;
	}
	while (y < map->rows)
	{
		if (map->map[y][0] != '1' || map->map[y][map->cols - 1] != '1')
		{
			exit_with_error("Error: Map borders are not surrounded by walls");
			free_map(map);
		}
		y++;
	}
}

void	find_player_position(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->cols)
		{
			if (game->map->map[y][x] == 'P')
			{
				game->player->x = x;
				game->player->y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	is_valid_map(t_game *game)
{
	t_map		*map;
	t_player	*player;
	int			**visited_exit;
	int			**visited_coins;

	map = game->map;
	player = game->player;
	is_rectungular_map(map);
	is_surrounded_by_walls(map);
	count_map_objects(map);
	check_invalid_objects(map);
	find_player_position(game);
	visited_exit = create_visited(map);
	dfs(game, player->y, player->x, visited_exit);
	free_visited(visited_exit, map);
	visited_coins = create_visited(map);
	dfs_coin(game, player->y, player->x, visited_coins);
	free_visited(visited_coins, map);
	check_objects_in_map(map);
}
