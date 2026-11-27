/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 10:45:44 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/27 12:08:38 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_player_values(t_player *player, int x, int y, t_dir dir)
{
	player->x = x + 0.5;
	player->y = y + 0.5;
	if (dir == NORTH)
	{
		player->dir = HALF_PI;
		player->orient.map.y = -1;
	}
	if (dir == SOUTH)
	{
		player->dir = THREE_HALF_PI;
		player->orient.map.y = 1;
	}
	if (dir == WEST)
	{
		player->dir = PI;
		player->orient.map.x = -1;
	}
	if (dir == EAST)
	{
		player->dir = 0;
		player->orient.map.x = 1;
	}
}

void	grab_player_coordinates(t_storage *dat)
{
	int	x;
	int	y;

	y = 0;
	dat->player->orient.map.x = 0;
	dat->player->orient.map.y = 0;
	while (y < dat->max_h)
	{
		x = 0;
		while (x < dat->max_w)
		{
			if (dat->map[y * dat->max_w + x] == 'N')
				fill_player_values(dat->player, x, y, NORTH);
			if (dat->map[y * dat->max_w + x] == 'S')
				fill_player_values(dat->player, x, y, SOUTH);
			if (dat->map[y * dat->max_w + x] == 'W')
				fill_player_values(dat->player, x, y, WEST);
			if (dat->map[y * dat->max_w + x] == 'E')
				fill_player_values(dat->player, x, y, EAST);
			x++;
		}
		y++;
	}
}

int	frame_per_second(t_storage *dat)
{
	struct timeval	tv;
	time_t			milliseconds;
	time_t			limit;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_usec / 1000 + tv.tv_sec * 1000);
	limit = milliseconds + 16;
	while ((tv.tv_usec / 1000 + tv.tv_sec * 1000) < limit)
	{
		usleep(200);
		gettimeofday(&tv, NULL);
	}
	recalc_player_pos(dat, dat->player);
	fill_map(dat);
	return (0);
}

void	put_pixel_3d(t_storage *dat, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = dat->img_3d->addr
		+ (y * dat->img_3d->line_length + x
			* (dat->img_3d->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_pixel_mini(t_storage *dat, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0
		|| x >= dat->mini.mini_w * TILE_SIZE
		|| y >= dat->mini.mini_h * TILE_SIZE)
		return ;
	dst = dat->img_mini->addr
		+ (y * dat->img_mini->line_length + x
			* (dat->img_mini->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
