#include "minilibx/mlx.h"
#include <stdlib.h>

typedef struct s_game {
    void *mlx;
    void *win;
    void *img;
    int img_width;
    int img_height;
    int x;
    int y;
} t_game;

int close_window(void *param)
{
    (void)param;
    exit(0);
}

int key_press(int keycode, t_game *game)
{
    if (keycode == 65361)
        game->x -= 10;
    else if (keycode == 65363)
        game->x += 10;
    else if (keycode == 65362)
        game->y -= 10;
    else if (keycode == 65364)
        game->y += 10;
    else if (keycode == 65307)
        exit(0);

    mlx_clear_window(game->mlx, game->win);
    mlx_put_image_to_window(game->mlx, game->win, game->img, game->x, game->y);

    return (0);
}

int main()
{
    t_game game;

    game.mlx = mlx_init();
    if (!game.mlx)
        return (EXIT_FAILURE);

    game.win = mlx_new_window(game.mlx, 800, 600, "So Long");
    if (!game.win)
        return (EXIT_FAILURE);

    game.img = mlx_xpm_file_to_image(game.mlx, "player.xpm", &game.img_width, &game.img_height);
    if (!game.img)
    {
        //printf("Resim yüklenemedi!\n");
        return (EXIT_FAILURE);
    }

    // Başlangıç pozisyonu
    game.x = 300;
    game.y = 300;

    // Resmi başlangıçta çiz
    mlx_put_image_to_window(game.mlx, game.win, game.img, game.x, game.y);

    // Klavye ve çıkış olaylarını tanımla
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_hook(game.win, 17, 0, close_window, NULL);

    mlx_loop(game.mlx);

    return (EXIT_SUCCESS);
}
