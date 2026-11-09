/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:16:53 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/09 11:46:16 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

char	map[] =
{ 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 1, 0, 0, 0, 1, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 0, 1, 1, 1, 1,
  1, 0, 0, 1, 0, 0, 0, 0, 1,
  1, 0, 0, 0,'N',0, 0, 0, 1,
  1, 0, 1, 0, 0, 0, 1, 0, 1,
  1, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1,};

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
			if (map[y * dat->img->max_w + x] == 'N')
			{
				dat->player->x = x + 0.5;
				dat->player->y = y + 0.5;
				dat->player->dir = HALF_PI;
				dat->player->orient.map.x = 0;
				dat->player->orient.map.y = -1;
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
	dat->map = map;
	img->max_h = 9;
	img->max_w = 9;
	grab_player_coordinates(dat);
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
	img.win_ptr = mlx_new_window(img.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	img.img_mini = mlx_new_image(img.mlx_ptr, img.max_w * TILE_SIZE, TILE_SIZE * img.max_h);
	img.img_3d = mlx_new_image(img.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr_mini = mlx_get_data_addr(img.img_mini, &img.bits_per_pixel, &img.line_length_mini, &img.endian);
	img.addr_3d = mlx_get_data_addr(img.img_3d, &img.bits_per_pixel, &img.line_length_3d, &img.endian);
	setup_hooks(&dat);
	mlx_loop(img.mlx_ptr);
	mlx_destroy_image(img.mlx_ptr, img.img_mini);
	mlx_destroy_window(img.mlx_ptr, img.win_ptr);
	mlx_destroy_display(img.mlx_ptr);
	free(img.mlx_ptr);
}
