#include "cub3d.h"

#define TILE_SIZE 90
#define PLAYER_SIZE 8

void	put_pixel(t_constants *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_player(int x, int y, t_constants *img)
{
	int	colour;
	int	xo;
	int	yo;
	int	yo_limit;
	int	xo_limit;

	colour = 0xFFFF00;
	yo = y * TILE_SIZE + TILE_SIZE / 2 - PLAYER_SIZE / 2;
	yo_limit = yo + PLAYER_SIZE;
	xo_limit = (x * TILE_SIZE + TILE_SIZE / 2 - PLAYER_SIZE / 2)+ PLAYER_SIZE;
	while(yo < yo_limit - 1)
	{
		xo = x * TILE_SIZE - PLAYER_SIZE / 2 + TILE_SIZE / 2;
		while(xo < xo_limit - 1)
		{
			put_pixel(img, xo, yo, colour);
			xo++;
		}
		yo++;
	}
}

void	fill_tile(int x, int y, int colour, t_constants *img)
{
	int	xo;
	int	yo;
	int	yo_limit;
	int	xo_limit;

	yo = y * TILE_SIZE ;
	yo_limit = yo + TILE_SIZE;
	xo_limit = x * TILE_SIZE + TILE_SIZE;
	while(yo < yo_limit - 1)
	{
		xo = x * TILE_SIZE;
		while(xo < xo_limit - 1)
		{
			put_pixel(img, xo, yo, colour);
			xo++;
		}
		yo++;
	}
}

void	fill_map(t_constants *img)
{
	int	x;
	int	y;

	y = 0;
	while(y < 9)
	{
		x = 0;
		while(x < 9)
		{
			if (map[y * 9 + x] == 1)
				fill_tile(x, y, 0x00FFFFFF, img);
			//else if (map[y * 9 + x] == 'N')
			//	draw_player(x, y, img);
			else
			{
				fill_tile(x, y, 0x0000FFFF, img);
				if (map[y * 9 + x] == 'N')
					draw_player(x, y, img);
			}
			x++;
		}
		y++;
	}
}

int main(void)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_constants	img;
	int			offset;
	//validity checker part 1
	//parsing
	//validity checker part 2
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "cub3D");
	img.img = mlx_new_image(mlx_ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	fill_map(&img);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr);
	mlx_destroy_image(mlx_ptr, img.img);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}
