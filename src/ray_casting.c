/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:34:52 by bastalze          #+#    #+#             */
/*   Updated: 2026/10/28 10:43:43 by knajmech         ###   ########.fr       */
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
	r1.x = map_to_screen(player->x);
	r1.y = map_to_screen(player->y);
	r2.x = map_to_screen(player->x);
	r2.y = map_to_screen(player->y);
	dir = 0;
	dof = 0;
	if (player->a < PI)
	{
		dir = -1;
		r2.y = (int)player->y * TILE_SIZE;
		r2.x = ((r1.y - r2.y) * atan + player->x * TILE_SIZE);
		puts("one");
	}
	else if (player->a > PI)
	{
		dir = 1;
		r2.y = map_to_screen((int)player->y + 1);
		r2.x = ((r1.y - r2.y) * atan + player->x * TILE_SIZE);
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
	r1.colour = 0xD11515;
	bresenham_algo(r1, r2, data);
	// ugly way of making line thicker
	r1.x++;
	r2.x++;
	bresenham_algo(r1, r2, data);
	r1.x++;
	r2.x++;
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
	r1.x = map_to_screen(player->x);
	r1.y = map_to_screen(player->y);
	r2.x = map_to_screen(player->x);
	r2.y = map_to_screen(player->y);
	dir = 0;
	dof = 0;
	if (player->a < HALF_PI || player->a > THREE_HALF_PI)
	{
		dir = 1;
		r2.x = ((unsigned int)player->x + 1) * TILE_SIZE;
		r2.y = ((r1.x - r2.x) * atan + player->y * TILE_SIZE);
	}
	else if (player->a > HALF_PI && player->a < THREE_HALF_PI)
	{
		dir = -1;
		r2.x = ((unsigned int)player->x) * TILE_SIZE;
		r2.y = ((r1.x - r2.x) * atan + player->y * TILE_SIZE);
	}
	if (player->a == HALF_PI || player->a == HALF_PI + PI)
		return ;
	while (dir && check_if_wall(r2.x, r2.y, data->img->max_h, map))
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
	r1.colour = 0x2F7A2A;
	bresenham_algo(r1, r2, data);
}
