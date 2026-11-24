/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 10:31:52 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/23 13:01:41 by knajmech         ###   ########.fr       */
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

void	fill_tile(t_storage *data, int px, int py, int colour)
{
	int	x;
	int	y;

	y = 0;
	while (y < TILE_SIZE - 1)
	{
		x = 0;
		while (x < TILE_SIZE - 1)
		{

			put_pixel_mini(data, px + x, py + y, colour);
			x++;
		}
		y++;
	}
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
			c = tile_colour(dat, tx, ty);   // -1 for void
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
	/*if (x_limit > MINI_VIEW)
		x_limit = MINI_VIEW;
	if (y_limit > MINI_VIEW)
		y_limit = MINI_VIEW;*/
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
	if (start < 0)
		start = 0;
	if (start > map_dim - MINI_VIEW)
		start = map_dim - MINI_VIEW;
	return (start);
}

void	minimap(t_storage *dat)
{
	clean_canvas(dat, dat->mini);
	dat->mini.x_start = mini_start(dat->player->x, dat->max_w);
	dat->mini.y_start = mini_start(dat->player->y, dat->max_h);
	draw_map(dat, dat->mini);
	// player dot at ((player.x - x_start) * TILE_SIZE, (player.y - y_start) * TILE_SIZE)
}

/*
void	fill_tile(double x, double y, int colour, t_constants *img)
{
	int	xo;
	int	yo;
	int	yo_limit;
	int	xo_limit;

	yo = (unsigned int)(y * TILE_SIZE - TILE_SIZE / 2);
	yo_limit = yo + TILE_SIZE;
	xo_limit = (unsigned int)(x * TILE_SIZE - TILE_SIZE / 2);
	while (yo < yo_limit - 1)
	{
		xo = x * TILE_SIZE;
		while (xo < xo_limit - 1)
		{
			put_pixel_mini(img, xo, yo, colour);
			xo++;
		}
		yo++;
	}
}

void	draw_map(t_storage *dat, t_minimap mini)
{
	double	x_end;
	double	x_start;
	double	y_end;

	x_end = mini.x_start + MINI_VIEW;
	y_end = mini.y_start + MINI_VIEW;
	while (mini.y_start < y_end)
	{
		x_start = mini.x_start;
		while (x_start < x_end)
		{
			if (is_wall(x_start, mini.y_start, dat))
				fill_tile(x_start, mini.y_start, 0X0FFFFFF, dat->img_mini);
			else
				fill_tile(x_start, mini.y_start, 0x0000FFFF, dat->img_mini);
			x_start++;
		}
		mini.y_start++;
	}
}*/
/*
void	minimap(t_storage *dat)
{
	clean_canvas(dat, dat->mini);
	dat->mini.x_start = dat->player->x - 5;
	dat->mini.y_start = dat->player->y - 5;
	draw_map(dat, dat->mini);
}*/

//first determine player coordinates.
/*
void	find_widest_wall(t_storage *dat, double *x, double *y)
{
	int	dist_x;
	int	dist_y;
	int	furthest_x;
	int	furthest_y;

	dist_y = 0;
	while (dist_y < 10)
	{
		dist_x = 0;
		while (dist_x < 10)
		{
			if (is_wall(*x + dist_x, *y + dist_y, dat))
				fill_tile(x, y, 0x00FFFFFF, data->img_mini);
			else
				fill_tile(x, y, 0x0000FFFF, data->img_mini);
				
		}
		dist_y++;
	}
	*x = furthest_x;
	*y = furthest_y;
}

void	shifting_minimap(t_storage *data)
{
	double	norm_x;
	double	norm_y;

	norm_x = data->player->x - 5;
	norm_y = data->player->y - 5;
	if (norm_x < 0)
		norm_x = 0;
	if (norm_y < 0)
		norm_y = 0;
	find_widest_wall(data, &norm_x, &norm_y);
	fix_window();
}

void	static_minimap(t_storage *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->max_h)
	{
		x = 0;
		while (x < data->max_w)
		{
			if (map[y * data->max_w + x] == WALL)
				fill_tile(x, y, 0x00FFFFFF, data->img_mini);
			else
				fill_tile(x, y, 0x0000FFFF, data->img_mini);
			x++;
		}
		y++;
	}
	draw_player(data->player->x, data->player->y, data->img_mini);
}

void	minimap(t_storage *dat, int *x, int *y)
{
	if (dat->max_h > 10 || dat->max_w > 10)
		shifting_minimap(dat);
	else
		static_minimap(dat);
}*/
