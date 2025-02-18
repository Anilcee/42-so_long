#include "so_long.h"

void	check_move(t_game *game, int new_x, int new_y, int key)
{
	if (game->map->map[new_y][new_x] != '1')
	{
		if (game->map->map[new_y][new_x] == 'C')
			game->player->collected++;
		if (game->map->map[new_y][new_x] == 'E')
		{
			check_win(game);
			return ;
		}
		game->map->map[game->player->y][game->player->x] = '0';
		game->player->x = new_x;
		game->player->y = new_y;
		game->map->map[game->player->y][game->player->x] = 'P';
		if (key == LEFT)
			game->img->p_img = game->img->p_left;
		else if (key == DOWN)
			game->img->p_img = game->img->p_down;
		else if (key == UP)
			game->img->p_img = game->img->p_up;
		else if (key == RIGHT)
			game->img->p_img = game->img->p_right;
		game->player->moves++;
		ft_printf("Moves: %d\n", game->player->moves);
		draw_map(game);
	}
}

int	move_player(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x;
	new_y = game->player->y;
	if (key == DOWN)
		new_y++;
	else if (key == LEFT)
		new_x--;
	else if (key == UP)
		new_y--;
	else if (key == RIGHT)
		new_x++;
	else if (key == ESC)
		close_window(game);
	else
		return (0);
	check_move(game, new_x, new_y, key);
	return (0);
}

void	check_win(t_game *game)
{
	if (game->player->collected == game->map->coin)
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
