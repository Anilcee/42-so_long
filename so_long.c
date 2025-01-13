#include "so_long.h"

int close_window(void *param)
{
    (void)param;
    exit(0);
    return (0);
}
int move_player(int key, t_game *game)
{
    int new_x = game->player->x;
    int new_y = game->player->y;

    if (key == 65361) // Sol ok tuşu
        new_x--;
    else if (key == 65362) // Yukarı ok tuşu
        new_y--;
    else if (key == 65363) // Sağ ok tuşu
        new_x++;
    else if (key == 65364) // Aşağı ok tuşu
        new_y++;

    // Yeni pozisyonun harita sınırları içinde ve engel olmayan bir yer olup olmadığını kontrol et
    if (game->map->map[new_y][new_x] != '1')  // Eğer duvar (1) değilse
    {
        // Eski pozisyonu temizle
        mlx_clear_window(game->mlx, game->win);

        // Oyuncuyu yeni pozisyona yerleştir
        game->player->x = new_x;
        game->player->y = new_y;

        // Haritayı ve yeni oyuncu pozisyonunu yeniden çiz
        draw_map(game);
    }

    return (0);
}



int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./game map.ber\n");
        return (1);
    }

    t_game game;
    t_map map;
    t_player player;

    game.map = &map;
    game.player = &player;

    // Harita dosyasını yükle ve oyuncu pozisyonunu bul
    load_map(game.map, argv[1], game.player);

    // Pencere boyutlarını hesapla
    game.size_x = map.cols * 32; // Her bir hücre için 32 piksel genişlik
    game.size_y = map.rows * 32; // Her bir hücre için 32 piksel yükseklik

    // Minilibx başlatma
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, game.size_x, game.size_y, "so_long");

    // Haritayı çiz
    draw_map(&game);

    // Klavye tuşlarını dinle
    mlx_key_hook(game.win, move_player, &game);

    // Pencereyi kapatma olayını bağla
    mlx_hook(game.win, 17, 0, close_window, NULL);

    // Minilibx döngüsü
    mlx_loop(game.mlx);

    return (0);
}
