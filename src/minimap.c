/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 10:31:52 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/25 10:07:38 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tile_colour(t_storage *dat, int tx, int ty)
{
	char	c;

	if (tx < 0 || tx >= dat->max_w || ty < 0 || ty >= dat->max_h)
		return (-1);
	c = dat->map[ty * dat->max_w + tx];
	if (c == WALL)
		return (0x00FFFFFF);
	if (c == ' ')
		return (-1);
	return (0x0000FFFF);
}

void	draw_map(t_storage *dat, t_minimap mini)
{
	int	tx;
	int	ty;
	int	c;

	ty = (int)floor(mini.y_start);
	while (ty <= (int)floor(mini.y_start) + MINI_VIEW)
	{
		tx = (int)floor(mini.x_start);
		while (tx <= (int)floor(mini.x_start) + MINI_VIEW)
		{
			c = tile_colour(dat, tx, ty);
			if (c != -1)
				fill_tile(dat,
					(int)floor((tx - mini.x_start) * TILE_SIZE),
					(int)floor((ty - mini.y_start) * TILE_SIZE), c);
			tx++;
		}
		ty++;
	}
}

void	clean_canvas(t_storage *dat, t_minimap mini)
{
	int	x;
	int	y;
	int	x_limit;
	int	y_limit;

	x_limit = mini.mini_w * TILE_SIZE;
	y_limit = mini.mini_h * TILE_SIZE;
	y = 0;
	while (y < y_limit)
	{
		x = 0;
		while (x < x_limit)
		{
			put_pixel_mini(dat, x, y, 0x0);
			x++;
		}
		y++;
	}
}

static double	mini_start(double player_pos, int map_dim)
{
	double	start;

	if (map_dim <= MINI_VIEW)
		return (0);
	start = player_pos - MINI_VIEW / 2.0;
	return (start);
}

void	minimap(t_storage *dat)
{
	clean_canvas(dat, dat->mini);
	dat->mini.x_start = mini_start(dat->player->x, dat->max_w);
	dat->mini.y_start = mini_start(dat->player->y, dat->max_h);
	draw_map(dat, dat->mini);
}
