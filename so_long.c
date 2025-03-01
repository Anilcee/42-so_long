/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:28:08 by ancengiz          #+#    #+#             */
/*   Updated: 2025/03/01 17:28:09 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_game(t_game *game, char *map_file)
{
	game->img = (t_images *)malloc(sizeof(t_images));
	game->map = (t_map *)malloc(sizeof(t_map));
	game->player = (t_player *)malloc(sizeof(t_player));
	init_game(game);
	load_map(game->map, map_file);
	is_valid_map(game);
}

void	setup_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_with_error("Failed to initialize MLX");
	game->size_x = game->map->cols * T_S;
	game->size_y = game->map->rows * T_S;
	game->win = mlx_new_window(game->mlx, game->size_x,
			game->size_y, "so_long");
	if (!game->win)
		exit_with_error("Failed to create window");
	init_images(game);
	draw_map(game);
}

void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->win, move_player, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_with_error("Usage: ./so_long <map_file.ber>");
	check_file_extension(argv[1]);
	initialize_game(&game, argv[1]);
	setup_window(&game);
	setup_hooks(&game);
	return (0);
}
