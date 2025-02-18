#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game		game;
	t_images	images;
	t_map		map;
	t_player	player;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./so_long <map_file.ber>\n", 2);
		return (1);
	}
	game.img = &images;
	game.map = &map;
	game.player = &player;
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		perror("Failed to initialize MLX");
		close_window(&game);
	}
	init_game(&game);
	load_map(game.map, argv[1]);
	is_valid_map(&game);
	game.size_x = game.map->cols * T_S;
	game.size_y = game.map->rows * T_S;
	game.win = mlx_new_window(game.mlx, game.size_x, game.size_y, "so_long");
	if (!game.win)
	{
		perror("Failed to create window");
		close_window(&game);
	}
	draw_map(&game);
	mlx_key_hook(game.win, move_player, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
