#include "so_long.h"

int	close_window(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game)
		free_images(game);
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map && map->map)
	{
		while (i < map->rows)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
}

void	free_visited(int **visited, t_map *map)
{
	int	i;

	i = 0;
	while (i < map-> rows)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	free_images(t_game *game)
{
	if (!game || !game->img || !game->mlx)
		return ;
	if (game->img->p_left)
		mlx_destroy_image(game->mlx, game->img->p_left);
	if (game->img->p_right)
		mlx_destroy_image(game->mlx, game->img->p_right);
	if (game->img->p_down)
		mlx_destroy_image(game->mlx, game->img->p_down);
	if (game->img->p_up)
		mlx_destroy_image(game->mlx, game->img->p_up);
	if (game->img->wall)
		mlx_destroy_image(game->mlx, game->img->wall);
	if (game->img->coin)
		mlx_destroy_image(game->mlx, game->img->coin);
	if (game->img->exit)
		mlx_destroy_image(game->mlx, game->img->exit);
}
