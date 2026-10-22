#include "cub3d.h"

char	map[] =
{ 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 1, 0, 0, 0, 1, 0, 1,
  1, 0, 0, 0, 1, 1, 1, 0, 1,
  1, 0, 0, 0, 1, 1, 0, 0, 1,
  1, 0, 0, 0, 1, 1, 0, 0, 1,
  1, 0, 1, 0,'E', 0, 1, 0, 1,
  1, 0, 1, 1, 0, 0, 1, 0, 1,
  1, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1,};

void	put_pixel(t_constants *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	grab_player_coordinates(t_storage *dat)
{
	int	x;
	int	y;

	y = 0;
	while(y < dat->img->max_h)
	{
		x = 0;
		while(x < dat->img->max_w)
		{
			if (map[y * dat->img->max_w + x] == 'E')
			{
				dat->player->x = x + 0.5;
				dat->player->y = y + 0.5;
			}
			x++;
		}
		y++;
	}
}

void	init(t_player *player, t_storage *dat, t_constants *img)
{
	ft_bzero(player, sizeof(t_player));
	dat->img = img;
	dat->player = player;
	img->max_h = 9;
	img->max_w = 9;
	grab_player_coordinates(dat);
	player->p1.x = player->x;
	player->p1.y = player->y;
	player->p2.x = player->x + (player->x * cos(player->a) * 5 - player->y * sin(player->a) * 5);
	player->p2.y = player->y + (player->x * sin(player->a) * 5 + player->y * cos(player->a) * 5);
}

int main(void)
{
	t_constants	img;
	t_player	player;
	t_storage	dat;

	//validity checker part 1
	//parsing
	//validity checker part 2
	init(&player, &dat, &img);
	img.mlx_ptr = mlx_init();
	img.win_ptr = mlx_new_window(img.mlx_ptr, 1920, 1080, "cub3D");
	img.img = mlx_new_image(img.mlx_ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	setup_hooks(&dat);
	mlx_loop(img.mlx_ptr);
	mlx_destroy_image(img.mlx_ptr, img.img);
	mlx_destroy_window(img.mlx_ptr, img.win_ptr);
	mlx_destroy_display(img.mlx_ptr);
	free(img.mlx_ptr);
}
