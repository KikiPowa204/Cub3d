/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 10:16:53 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/25 08:15:04 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init(t_player *player, t_storage *dat, t_constants *img_mini,
		t_constants *img3d)
{
	ft_bzero(player, sizeof(t_player));
	ft_bzero(dat, sizeof(t_storage));
	ft_bzero(img_mini, sizeof(t_constants));
	dat->img_mini = img_mini;
	dat->img_3d = img3d;
	dat->floor_c = -1;
	dat->ceiling_c = -1;
	dat->player = player;
	player->dir = -1;
}

int	init_textures(t_storage	*dat, char **texture_paths)
{
	dat->walls.north.txt_ptr = mlx_xpm_file_to_image(dat->mlx_ptr, texture_paths[NO], &dat->walls.north.width, &dat->walls.north.height);
	dat->walls.south.txt_ptr = mlx_xpm_file_to_image(dat->mlx_ptr, texture_paths[SO], &dat->walls.south.width, &dat->walls.south.height);
	dat->walls.west.txt_ptr = mlx_xpm_file_to_image(dat->mlx_ptr, texture_paths[WE], &dat->walls.west.width, &dat->walls.west.height);
	dat->walls.east.txt_ptr = mlx_xpm_file_to_image(dat->mlx_ptr, texture_paths[EA], &dat->walls.east.width, &dat->walls.east.height);
	if (dat->walls.north.txt_ptr && dat->walls.south.txt_ptr && dat->walls.west.txt_ptr && dat->walls.east.txt_ptr)
		return (1);
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

int main(int ac, char **av)
{
	t_constants	img_mini;
	t_constants	img_3d;
	t_player	player;
	t_storage	dat;
	char		*texture_paths[4];

	//validity checker part 1
	//parsing
	//validity checker part 2
	if (ac != 2)
		return (error("Incorrect amount of arguments", false), 1);
	if (!init(&player, &dat, &img_mini, &img_3d)
			|| parse_description_file(av[1], &dat, texture_paths)
			|| !init_textures(&dat, texture_paths)
			|| !mlx_setup(&img_mini, &img_3d, &dat))
		return (cleanup(&dat), 1);
	/*img.mlx_ptr = mlx_init();
	if (!init_textures(&dat, texture_paths))
		return (1);*/
	setup_hooks(&dat);
	mlx_loop(dat.mlx_ptr);
}
/*
	mlx_destroy_image(dat.mlx_ptr, dat.img_mini);
	mlx_destroy_window(dat.mlx_ptr, dat.win_ptr);
	mlx_destroy_display(dat.mlx_ptr);
	free(dat.mlx_ptr);
}*/
