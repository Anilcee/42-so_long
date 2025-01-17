#include "so_long.h"

void	check_move(t_game *game, int new_x, int new_y)
{
	if (game->map->map[new_y][new_x] != '1') // Duvar değilse hareket et
	{
		if (game->map->map[new_y][new_x] == 'C')
		{
			game->player->collected++;
			game->map->map[new_y][new_x] = '0'; // Altını yok et
		}
		if (game->map->map[new_y][new_x] == 'E')
		{
			if (game->player->collected == game->map->collectables)
			{
				ft_putstr_fd("You won!\n", 1);
				close_window(game);
			}
			else
			{
				ft_putstr_fd("Collect all the collectables!\n", 1);
				return ;
			}
		}
		game->map->map[game->player->y][game->player->x] = '0';
		game->player->x = new_x;
		game->player->y = new_y;
		game->player->moves++;
		printf("Moves: %d\n", game->player->moves);
		draw_map(game);
	}
}
int	move_player(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x;
	new_y = game->player->y;
	if (key == S)
		new_y++;
	else if (key == A)
		new_x--;
	else if (key == W)
		new_y--;
	else if (key == D)
		new_x++;
	else if (key == ESC)
		close_window(game);
	else
		return (0); // Geçersiz bir tuşa basıldıysa hiçbir işlem yapılmaz
	check_move(game, new_x, new_y);
	return (0);
}
