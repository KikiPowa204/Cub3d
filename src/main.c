/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:16:53 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/17 15:21:55 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	init(t_player *player, t_storage *dat, t_constants *img)
{
	ft_bzero(player, sizeof(t_player));
	ft_bzero(dat, sizeof(t_storage));
	img->mlx_ptr = mlx_init();
	if (!img->mlx_ptr)
		return (0);
	dat->img = img;
	dat->player = player;
	dat->map = map;
	img->max_h = 9;
	img->max_w = 9;
	grab_player_coordinates(dat);
	return (1);
}

void	store_texture_addresses(t_storage *dat)
{
	dat->walls.north.txt_addr = mlx_get_data_addr(dat->walls.north.txt_ptr,
			&dat->walls.north.bits_per_pixel, &dat->walls.north.line_length,
			&dat->img->endian);
	dat->walls.south.txt_addr = mlx_get_data_addr(dat->walls.south.txt_ptr,
			&dat->walls.south.bits_per_pixel, &dat->walls.south.line_length,
			&dat->img->endian);
	dat->walls.east.txt_addr = mlx_get_data_addr(dat->walls.east.txt_ptr,
			&dat->walls.east.bits_per_pixel, &dat->walls.east.line_length,
			&dat->img->endian);
	dat->walls.west.txt_addr = mlx_get_data_addr(dat->walls.west.txt_ptr,
			&dat->walls.west.bits_per_pixel, &dat->walls.west.line_length,
			&dat->img->endian);
}

int	init_textures(t_storage	*dat)
{
	dat->walls.north.txt_ptr = mlx_xpm_file_to_image(dat->img->mlx_ptr,
			"textures/horror1.xpm", &dat->walls.north.width,
			&dat->walls.north.height);
	dat->walls.south.txt_ptr = mlx_xpm_file_to_image(dat->img->mlx_ptr,
			"textures/horror2.xpm", &dat->walls.south.width,
			&dat->walls.south.height);
	dat->walls.west.txt_ptr = mlx_xpm_file_to_image(dat->img->mlx_ptr,
			"textures/horror3.xpm", &dat->walls.west.width,
			&dat->walls.west.height);
	dat->walls.east.txt_ptr = mlx_xpm_file_to_image(dat->img->mlx_ptr,
			"textures/horror4.xpm", &dat->walls.east.width,
			&dat->walls.east.height);
	if (dat->walls.north.txt_ptr && dat->walls.south.txt_ptr
		&& dat->walls.west.txt_ptr && dat->walls.east.txt_ptr)
	{
		store_texture_addresses(dat);
		return (1);
	}
	else
		return (0);
}

int	mlx_setup(t_constants *img)
{
	img->win_ptr = mlx_new_window(img->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	if (!img->win_ptr)
		return (0);
	img->img_mini = mlx_new_image(img->mlx_ptr,
			img->max_w * TILE_SIZE, TILE_SIZE * img->max_h);
	if (!img->img_mini)
		return (0);
	img->img_3d = mlx_new_image(img->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img->img_3d)
		return (0);
	img->addr_mini = mlx_get_data_addr(img->img_mini, &img->bits_per_pixel,
			&img->line_length_mini, &img->endian);
	if (!img->addr_mini)
		return (0);
	img->addr_3d = mlx_get_data_addr(img->img_3d, &img->bits_per_pixel,
			&img->line_length_3d, &img->endian);
	if (!img->addr_3d)
		return (0);
	return (1);
}

int	main(void)
{
	t_constants	img;
	t_player	player;
	t_storage	dat;

	if (!init(&player, &dat, &img) || !init_textures(&dat) || !mlx_setup(&img))
		return (cleanup(&dat), 1);
	setup_hooks(&dat);
	mlx_loop(img.mlx_ptr);
	mlx_destroy_image(img.mlx_ptr, img.img_mini);
	mlx_destroy_window(img.mlx_ptr, img.win_ptr);
	mlx_destroy_display(img.mlx_ptr);
	free(img.mlx_ptr);
}
