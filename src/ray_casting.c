/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:34:52 by bastalze          #+#    #+#             */
/*   Updated: 2026/10/23 14:59:01 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "stdio.h"

void	ray_casting_horizontal(t_player *player, t_storage *data)
{
	t_coordinates	r1;
	t_coordinates	r2;
	double			atan;
	int				dir;

	atan = 1/tan(player->a);
	r1.x = player->x * TILE_SIZE;
	r1.y = player->y * TILE_SIZE;
	r2.x = player->x * TILE_SIZE;
	r2.y = player->y * TILE_SIZE;
	dir = 0;
	if (player->a < PI)
	{
		dir = -1;
		r2.y = (unsigned int)player->y * TILE_SIZE;
		r2.x = ((r1.y - r2.y) * atan + player->x * TILE_SIZE);
	}
	else if (player->a > PI)
	{
		dir = 1;
		r2.y = ((unsigned int)player->y + 1) * TILE_SIZE;
		r2.x = ((r1.y - r2.y) * atan + player->x * TILE_SIZE);
	}
	while (map[r2.y / TILE_SIZE * data->img->max_w + r2.x / TILE_SIZE] != WALL)
	{
		r2.y = r2.y + dir;
		r2.x = ((r1.y - r2.y) * atan + r1.x);
	}
	printf("x:%d y:%d atan:%lf\n", r2.x, r2.y, atan);
	bresenham_algo(r1, r2, data);
}

void	ray_casting_vertical(t_player *player, t_storage *data)
{
	t_coordinates	r1;
	t_coordinates	r2;
	double			atan;

	atan = 1/tan(player->a);
	r1.x = player->x * TILE_SIZE;
	r1.y = player->y * TILE_SIZE;
	r2.x = player->x * TILE_SIZE;
	r2.y = player->y * TILE_SIZE;
	if (player->a < PI)
	{
		r2.y = (unsigned int)player->y * TILE_SIZE;
		r2.x = ((r1.y - r2.y) * atan + player->x * TILE_SIZE);
	}
	else if (player->a > PI)
	{
		r2.y = ((unsigned int)player->y + 1) * TILE_SIZE;
		r2.x = ((r1.y - r2.y) * atan + player->x * TILE_SIZE);
	}
	printf("x:%d y:%d atan:%lf\n", r2.x, r2.y, atan);
	bresenham_algo(r1, r2, data);
}