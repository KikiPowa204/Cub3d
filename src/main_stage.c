/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:03:09 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/24 11:56:56 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(double x, double y, t_storage *dat)
{
	int	colour;
	int	xo;
	int	yo;
	int	yo_limit;
	int	xo_limit;

	colour = 0xAB1D6F;
	yo = (unsigned int)(y * TILE_SIZE - PLAYER_SIZE / 2);
	yo_limit = yo + PLAYER_SIZE;
	xo_limit = (unsigned int)(x * TILE_SIZE - PLAYER_SIZE / 2) + PLAYER_SIZE;
	while (yo < yo_limit - 1)
	{
		xo = (unsigned int)(x * TILE_SIZE - PLAYER_SIZE / 2);
		while (xo < xo_limit - 1)
		{
			put_pixel_mini(dat, xo, yo, colour);
			xo++;
		}
		yo++;
	}
}

void	draw_background(t_storage *dat)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_3d(dat, x, y, 0xffc0cb);
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_3d(dat, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	fill_map(t_storage *dat)
{
	minimap(dat);
	draw_background(dat);
	cone_casting(dat);
	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr,
		dat->img_3d->img_ptr, 0, 0);
	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr,
		dat->img_mini->img_ptr, 0, 0);
}
