/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:16:53 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/24 10:32:42 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	map[] =
{ 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,
  1, 0, 1, 0, 0, 0, 1, 0, 0,0,0,1,
  1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,1,
  1, 0, 1, 0, 0, 1, 1, 1, 0,1,1,1,
  1, 0, 0, 1, 0, 0, 0, 0, 0,0,0,1,
  1, 0, 0, 0, 0, 0,'N',0, 0,0,0,1,
  1, 0, 1, 0, 0, 0, 1, 0, 0,0,0,1,
  1, 0, 0, 0, 1, 0, 0, 0, 0,0,0,1,
  1, 0, 0, 0, 1, 0, 0, 0, 0,0,0,1,
  1, 0, 1, 1, 1, 0, 1, 0, 0,0,0,1,
  1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,};

int	init(t_player *player, t_storage *dat, t_constants *img_mini,
		t_constants *img3d)
{
	ft_bzero(player, sizeof(t_player));
	ft_bzero(dat, sizeof(t_storage));
	dat->mlx_ptr = mlx_init();
	if (!dat->mlx_ptr)
		return (0);
	dat->img_mini = img_mini;
	dat->img_3d = img3d;
	dat->player = player;
	dat->map = map;
	dat->max_h = 11;
	dat->max_w = 12;
	dat->mini.mini_w = dat->max_w;
	if (dat->mini.mini_w > MINI_VIEW)
		dat->mini.mini_w = MINI_VIEW;
	dat->mini.mini_h = dat->max_h;
	if (dat->mini.mini_h > MINI_VIEW)
		dat->mini.mini_h = MINI_VIEW;
	grab_player_coordinates(dat);
	return (1);
}

void	store_texture_addresses(t_storage *dat)
{
	dat->walls.north.txt_addr = mlx_get_data_addr(dat->walls.north.txt_ptr,
			&dat->walls.north.bits_per_pixel, &dat->walls.north.line_length,
			&dat->walls.north.endian);
	dat->walls.south.txt_addr = mlx_get_data_addr(dat->walls.south.txt_ptr,
			&dat->walls.south.bits_per_pixel, &dat->walls.south.line_length,
			&dat->walls.south.endian);
	dat->walls.east.txt_addr = mlx_get_data_addr(dat->walls.east.txt_ptr,
			&dat->walls.east.bits_per_pixel, &dat->walls.east.line_length,
			&dat->walls.east.endian);
	dat->walls.west.txt_addr = mlx_get_data_addr(dat->walls.west.txt_ptr,
			&dat->walls.west.bits_per_pixel, &dat->walls.west.line_length,
			&dat->walls.west.endian);
}

int	init_textures(t_storage	*dat)
{
	dat->walls.north.txt_ptr = mlx_xpm_file_to_image(dat->mlx_ptr,
			"textures/horror1.xpm", &dat->walls.north.width,
			&dat->walls.north.height);
	dat->walls.south.txt_ptr = mlx_xpm_file_to_image(dat->mlx_ptr,
			"textures/horror2.xpm", &dat->walls.south.width,
			&dat->walls.south.height);
	dat->walls.west.txt_ptr = mlx_xpm_file_to_image(dat->mlx_ptr,
			"textures/horror3.xpm", &dat->walls.west.width,
			&dat->walls.west.height);
	dat->walls.east.txt_ptr = mlx_xpm_file_to_image(dat->mlx_ptr,
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

int	mlx_setup(t_constants *img_mini, t_constants *img_3d, t_storage *dat)
{
	dat->win_ptr = mlx_new_window(dat->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	if (!dat->win_ptr)
		return (0);
	dat->img_mini->img_ptr = mlx_new_image(dat->mlx_ptr,
			dat->mini.mini_w * TILE_SIZE, TILE_SIZE * dat->mini.mini_h);
	if (!img_mini->img_ptr)
		return (0);
	img_3d->img_ptr = mlx_new_image(dat->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img_3d->img_ptr)
		return (0);
	img_mini->addr = mlx_get_data_addr(img_mini->img_ptr, &img_mini->bits_per_pixel,
			&img_mini->line_length, &img_mini->endian);
	if (!img_mini->addr)
		return (0);
	img_3d->addr = mlx_get_data_addr(img_3d->img_ptr, &img_3d->bits_per_pixel,
			&img_3d->line_length, &img_3d->endian);
	if (!img_3d->addr)
		return (0);
	return (1);
}

int	main(void)
{
	t_constants	img_mini;
	t_constants	img_3d;
	t_player	player;
	t_storage	dat;

	if (!init(&player, &dat, &img_mini, &img_3d) || !init_textures(&dat)
			|| !mlx_setup(&img_mini, &img_3d, &dat))
		return (cleanup(&dat), 1);
	setup_hooks(&dat);
	mlx_loop(dat.mlx_ptr);
	mlx_destroy_image(dat.mlx_ptr, dat.img_mini);
	mlx_destroy_window(dat.mlx_ptr, dat.win_ptr);
	mlx_destroy_display(dat.mlx_ptr);
	free(dat.mlx_ptr);
}
