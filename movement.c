#include "so_long.h"

void	check_move(t_game *game, int new_x, int new_y)
{
	if (game->map->map[new_y][new_x] != '1') //Duvar değilse hareket et
	{
		if (game->map->map[new_y][new_x] == 'C')
		{
			game->player->collected++;// Toplanan eşya sayısını arttır
			game->map->map[new_y][new_x] = '0';// 'C'yi haritadan kaldır
		}
		if (game->map->map[new_y][new_x] == 'E')
		{
			if (game->player->collected == game->map->collectables)
			{
				printf("You won the game!\n");
				close_window(game);
			}
			else
				printf("You need to collect all items!\n");
		}
		mlx_clear_window(game->mlx, game->win);//Oyuncunun konumunu güncelle
		game->player->x = new_x;
		game->player->y = new_y;
		draw_map(game);
	}
}

int	move_player(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x;
	new_y = game->player->y;
	if (key == S || key == A || key == W || key == D)
	{
		if (key == S)
			new_y++;
		else if (key == A)
			new_x--;
		else if (key == W)
			new_y--;
		else if (key == D)
			new_x++;
		game->player->moves++;
		printf("Moves: %d\n", game->player->moves);
	}
	if (key == ESC)
		close_window(game);
	check_move(game, new_x, new_y);
	return (0);
}
