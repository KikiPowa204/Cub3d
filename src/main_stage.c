/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:03:09 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/16 10:55:52 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(double x, double y, t_constants *img)
{
	int	colour;
	int	xo;
	int	yo;
	int	yo_limit;
	int	xo_limit;

	colour = 0xAB1D6F;
	yo = (unsigned int)(y * TILE_SIZE - PLAYER_SIZE / 2);
	yo_limit = yo + PLAYER_SIZE;
	xo_limit = (unsigned int)(x * TILE_SIZE - PLAYER_SIZE / 2)+ PLAYER_SIZE;
	while(yo < yo_limit - 1)
	{
		xo = (unsigned int)(x * TILE_SIZE - PLAYER_SIZE / 2);
		while(xo < xo_limit - 1)
		{
			put_pixel_mini(img, xo, yo, colour);
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
			put_pixel_mini(img, xo, yo, colour);
			xo++;
		}
		yo++;
	}
}

void	draw_background(t_storage *dat)
{
	int x;
	int y;
	
	y = 0;
	while(y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while(x < WINDOW_WIDTH)
		{
			put_pixel_3d(dat->img, x, y, 0xffc0cb);
			x++;
		}
		y++;	
	}
	while(y < WINDOW_HEIGHT)
	{
		x = 0;
		while(x < WINDOW_WIDTH)
		{
			put_pixel_3d(dat->img, x, y, 0x000000);
			x++;
		}
		y++;	
	}
}

void	fill_map(t_storage *dat)
{
	int	x;
	int	y;

	y = 0;
	while(y < 9)
	{
		x = 0;
		while(x < 9)
		{
			if (map[y * 9 + x] == WALL)
				fill_tile(x, y, 0x00FFFFFF, dat->img);
			else
				fill_tile(x, y, 0x0000FFFF, dat->img);
			x++;
		}
		y++;
	}
	draw_player(dat->player->x, dat->player->y, dat->img);
	draw_background(dat);
	cone_casting(dat);
	mlx_put_image_to_window(dat->img->mlx_ptr, dat->img->win_ptr,
			dat->img->img_3d, 0, 0);
	mlx_put_image_to_window(dat->img->mlx_ptr, dat->img->win_ptr,
			dat->img->img_mini, 0, 0);
}

