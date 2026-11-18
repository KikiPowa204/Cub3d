/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 10:45:44 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/18 14:10:24 by knajmech         ###   ########.fr       */
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
			if (map[y * dat->max_w + x] == 'N')
				fill_player_values(dat->player, x, y, NORTH);
			if (map[y * dat->max_w + x] == 'S')
				fill_player_values(dat->player, x, y, SOUTH);
			if (map[y * dat->max_w + x] == 'W')
				fill_player_values(dat->player, x, y, WEST);
			if (map[y * dat->max_w + x] == 'E')
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
	fill_map(dat);
	return (0);
}

void	put_pixel_3d(t_constants *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_pixel_mini(t_constants *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
