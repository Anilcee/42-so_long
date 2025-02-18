#include "so_long.h"

void	*convert_image(t_game *game, char *relative_path)
{
	int		img_width;
	int		img_height;
	void	*image;

	image = mlx_xpm_file_to_image(game->mlx, relative_path,
			&img_width, &img_height);
	if (!image)
		exit_with_error("Error image not found");
	return (image);
}

void	init_images(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	game->img->p_left = convert_image(game, "textures/pacman_left.xpm");
	game->img->p_right = convert_image(game, "textures/pacman64.xpm");
	game->img->p_down = convert_image(game, "textures/pacman_down.xpm");
	game->img->p_up = convert_image(game, "textures/pacman_up.xpm");
	game->img->p_img = game->img->p_right;
	game->img->wall = convert_image(game, "textures/blueblock64.xpm");
	game->img->coin = convert_image(game, "textures/pacdot_food.xpm");
	game->img->exit = convert_image(game, "textures/exit64.xpm");
	if (!game->img->p_img || !game->img->wall || !game->img->coin
		|| !game->img->exit)
	{
		perror("Failed to load one or more images");
		close_window(game);
	}
}

void	init_player(t_player *player)
{
	if (!player)
		return ;
	player->collected = 0;
	player->moves = 0;
	player->x = 0;
	player->y = 0;
}

void	init_game(t_game *game)
{
	if (!game)
		return ;
	init_player(game->player);
	init_images(game);
	game->map->coin = 0;
	game->map->valid_coin = 0;
	game->map->exit = 0;
	game->map->player = 0;
	game->map->rows = 0;
	game->map->cols = 0;
	game->map->map = NULL;
}

int	**create_visited(t_map *map)
{
	int	i;
	int	**visited;

	visited = malloc(map->rows * sizeof(int *));
	i = 0;
	while (i < map->rows)
	{
		visited[i] = malloc(map->cols * sizeof(int));
		ft_memset(visited[i], 0, map->cols * sizeof(int));
		i++;
	}
	return (visited);
}
