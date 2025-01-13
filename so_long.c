#include "so_long.h"

int	close_window(void *param)
{
	(void)param;
	exit (0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_player	player;

	if (argc != 2)
	{
		printf("Usage: ./game map.ber\n");
		return (1);
	}
	game.map = &map;
	game.player = &player;
	load_map(game.map, argv[1], game.player);
	game.size_x = map.cols * 64; // Her bir hücre için 64 piksel genişlik
	game.size_y = map.rows * 64; // Her bir hücre için 64 piksel yükseklik
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.size_x, game.size_y, "so_long");
	draw_map(&game);
	mlx_key_hook(game.win, move_player, &game);
	mlx_hook(game.win, 17, 0, close_window, NULL);
	mlx_loop(game.mlx);
	return (0);
}
