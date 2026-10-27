/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:34:52 by bastalze          #+#    #+#             */
/*   Updated: 2026/10/27 16:16:38 by knajmech         ###   ########.fr       */
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
	int				dof;

	atan = 1/tan(player->a);
	printf("tan a: %lf\n", tan(player->a));
	if (tan(player->a) < 0.001 && tan(player->a) > -0.001)
		return;
	r1.x = player->x * TILE_SIZE;
	r1.y = player->y * TILE_SIZE;
	r2.x = player->x * TILE_SIZE;
	r2.y = player->y * TILE_SIZE;
	dir = 0;
	dof = 0;
	if (player->a < PI)
	{
		dir = -1;
		r2.y = (unsigned int)player->y * TILE_SIZE;
		r2.x = ((r1.y - r2.y) * atan + player->x * TILE_SIZE);
		puts("one");
	}
	else if (player->a > PI)
	{
		dir = 1;
		r2.y = ((unsigned int)player->y + 1) * TILE_SIZE;
		r2.x = ((r1.y - r2.y) * atan + player->x * TILE_SIZE);
		puts("two");
	}
	if (player->a == 0 || player->a == PI)
		return ;
	while (dir && map[get_map_index(r2.x, r2.y, data->img->max_w)] != WALL)
	{
		
		r2.y = r2.y + dir;
		r2.x = ((r1.y - r2.y) * atan + r1.x);
		if (r2.x < 0 || r2.y < 0 || r2.x >= data->img->max_w * TILE_SIZE || r2.y >= data->img->max_h * TILE_SIZE)
			return ;
		printf("r1.y: %d, r1.x: %d, r2.y: %d, r2.x: %d\n", r1.y, r1.x, r2.y, r2.x);

	}
	r1.colour = 0xffff00;
	r2.colour = 0xffff00;
	bresenham_algo(r1, r2, data);
}
/*
void	ray_casting_vertical(t_player *p, t_storage *data)
{
	
}
*/

void	ray_casting_vertical(t_player *player, t_storage *data)
{
	t_coordinates	r1;
	t_coordinates	r2;
	double			atan;
	int				dir;
	int				dof;

	atan = tan(player->a);
	r1.x = player->x * TILE_SIZE;
	r1.y = player->y * TILE_SIZE;
	r2.x = player->x * TILE_SIZE;
	r2.y = player->y * TILE_SIZE;
	dir = 0;
	dof = 0;
	if (player->a < TWOPI || player->a > THREEPI)
	{
		dir = 1;
		r2.x = ((unsigned int)player->x + 1) * TILE_SIZE;
		r2.y = ((r1.x - r2.x) * atan + player->y * TILE_SIZE);
	}
	else if (player->a > TWOPI && player->a < THREEPI)
	{
		dir = -1;
		r2.x = ((unsigned int)player->x) * TILE_SIZE;
		r2.y = ((r1.x - r2.x) * atan + player->y * TILE_SIZE);
	}
	if (player->a == TWOPI || player->a == TWOPI + PI)
		return ;
	while (dof < 9 && dir && map[get_map_index(r2.x, r2.y, data->img->max_h)] != WALL)
	{
		if (r2.x < TILE_SIZE || r2.y < TILE_SIZE || r2.x >= data->img->max_w * TILE_SIZE || r2.y >= data->img->max_h * TILE_SIZE)
			return ;
		r2.x = r2.x + dir * TILE_SIZE;
		r2.y = ((r1.x - r2.x) * atan + r1.y);
		dof++;
		printf("ver: a:%lf x:%d y:%d atan:%lf\n", player->a, r2.x, r2.y, atan);
	}
	if (r2.x < 0 || r2.y < 0 || r2.x >= data->img->max_w * TILE_SIZE || r2.y >= data->img->max_h * TILE_SIZE)
		return ;
	r1.colour = 0x0000ff;
	r2.colour = 0x0000ff;
	bresenham_algo(r1, r2, data);
}
