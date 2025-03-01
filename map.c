/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:28:00 by ancengiz          #+#    #+#             */
/*   Updated: 2025/03/01 17:28:01 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_file_extension(char *file_path)
{
	file_path = file_path + ft_strlen(file_path) - 4;
	if (ft_strncmp(file_path, ".ber", 4) != 0)
	{
		ft_printf("Error: Invalid file extension must be .ber");
		exit(EXIT_FAILURE);
	}
}

int	open_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error opening file");
	return (fd);
}

void	load_map(t_map *map, const char *file_path)
{
	char	*line;
	char	*temp;
	int		fd;
	int		i;

	fd = open_file(file_path);
	line = ft_strdup("");
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		line = ft_strjoin(line, temp);
		free(temp);
		temp = get_next_line(fd);
	}
	map->map = ft_split(line, '\n');
	free(line);
	i = 0;
	while (map->map && map->map[i])
	{
		map->rows++;
		map->cols = ft_strlen(map->map[i]);
		i++;
	}
	close(fd);
}

void	put_object(t_game *game, int x, int y, void *img)
{
	mlx_put_image_to_window(game->mlx, game->win,
		img, x * T_S, y * T_S);
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	mlx_clear_window(game->mlx, game->win);
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->cols)
		{
			if (game->map->map[y][x] == 'P')
				put_object(game, x, y, game->img->p_img);
			else if (game->map->map[y][x] == '1')
				put_object(game, x, y, game->img->wall);
			else if (game->map->map[y][x] == 'C')
				put_object(game, x, y, game->img->coin);
			else if (game->map->map[y][x] == 'E')
				put_object(game, x, y, game->img->exit);
			x++;
		}
		y++;
	}
}
