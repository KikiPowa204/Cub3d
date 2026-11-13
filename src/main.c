/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:16:53 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/13 13:16:27 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
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
	ft_bzero(dat, sizeof(t_storage));
	dat->img = img;
	dat->player = player;
	dat->map = map;
	img->max_h = 9;
	img->max_w = 9;
	grab_player_coordinates(dat);
}

int	init_textures(t_storage	*dat)
{
	dat->walls.north.txt_ptr = mlx_xpm_file_to_image(dat->img->mlx_ptr, "textures/horror1.xpm", &dat->walls.north.width, &dat->walls.north.height);
	dat->walls.south.txt_ptr = mlx_xpm_file_to_image(dat->img->mlx_ptr, "textures/horror2.xpm", &dat->walls.south.width, &dat->walls.south.height);
	dat->walls.west.txt_ptr = mlx_xpm_file_to_image(dat->img->mlx_ptr, "textures/horror3.xpm", &dat->walls.west.width, &dat->walls.west.height);
	dat->walls.east.txt_ptr = mlx_xpm_file_to_image(dat->img->mlx_ptr, "textures/horror4.xpm", &dat->walls.east.width, &dat->walls.east.height);
	if (dat->walls.north.txt_ptr && dat->walls.south.txt_ptr && dat->walls.west.txt_ptr && dat->walls.east.txt_ptr)
		return (1);
	else
		return (0);//(cleanup(dat), 0);
}

int main(int ac, char **av)
{
	t_constants	img;
	t_player	player;
	t_storage	dat;
	char		*texture_paths[4];

	//validity checker part 1
	//parsing
	//validity checker part 2
	if (ac != 2)
		return (error("Incorrect amount of arguments", false), 1);
	init(&player, &dat, &img);
	if (!parse_description_file(av[1], &dat, texture_paths))
		return (1);
	img.mlx_ptr = mlx_init();
	if (!init_textures(&dat))
		return (1);
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
