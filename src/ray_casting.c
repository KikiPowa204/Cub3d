/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:34:52 by bastalze          #+#    #+#             */
/*   Updated: 2026/10/28 17:27:00 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "stdio.h"

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
/*
void	send_to_bresenham();

void	start_horizontal(double cot, u_cotype *rh, int *dir_h)
{
	
}
*/

bool	both_collide(u_cotype rh, u_cotype rv, t_player *player)
{
	if (rh.t_map.x >= data->img->max_w || rh.t_map.y >= data->img->max_h
		|| rh.t_map.x < 0 || rh.t_map.y < 0
		|| rv.t_map.x >= data->img->max_w || rv.t_map.y >= data->img->max_h
		|| rv.t_map.x < 0 || rv.t_map.y < 0)
		return (0);
	if (ray_collision(rv.t_map.x, rv.t_map.y, player->a, map)
			&& ray_collision(rv->t_map.x, rv.t_map.y, player->a, map))
		return (1);
	return (0);
}
bool	collide_horizontal(u_cotype rh, t_player *player)
{
	if (!(rh.t_map.x >= data->img->max_w || rh.t_map.x < 0)
		&& ray_collision(rh.t_map.x, rh.t_map.y, player->a, map))
		return (1);
	return (0);
}

bool	collide_vertical(u_cotype rv, t_player *player)
{
	if (!(rv.t_map.y >= data->img->max_h || rv.t_map.y < 0)
		&& ray_collision(rv.t_map.x, rv.t_map.y, player->a, map))
		return (1);
	return (0);
}

void	ray_casting(t_player *player)
{
	double		cot;
	double		tan;
	u_cotype	rh;
	u_cotype	rv;
	int			dir_h;
	int			dir_v;
	
	// rh.t_map.x = player->x;
	// rh.t_map.y = player->y;
	// rv.t_map.x = player->x;
	// rv.t_map.y = player->y;
	if (tan(player->a) < 0.001 && tan(player->a) > -0.001)
		return;
	cot = 1/tan(player->a);
	tan = tan(player->a);
	if (player->a < PI)
	{
		dir_h = -1;
		rh.t_map.y = (int)player->y;
	}
	else if (player->a > PI)
	{
		dir_v = 1;
		rh.t_map.y = (int)player->y + 1;
	}
	rh.t_map.x = ((player->y - rh.t_map.y) * cot + player->x);
	rh.length = distance(player->x, player->y, rh.t_map.x, rh.t_map.y);
	if (player->a < HALF_PI || player->a > THREE_HALF_PI)
	{
		dir_v = 1;
		rv.t_map.x = (int)player->x + 1;
	}
	else if (player->a > HALF_PI && player->a < THREE_HALF_PI)
	{
		dir_v = -1;
		rv.t_mapx = (int)player->x;
	}
	rv.t_map.y = ((player->x - rv.x) * tan + player->y);
	rh.length = distance(player->x, player->y, rv.t_map.x, rv.t_map.y);
	if (both_collide(rh, rv, player))
	{
		if (rh.length > rh.length)
			return (bresenham_algo(rh));
		else
			return (bresenham_algo(rv));
	}
	while (42)
	{
		if (collide_horizontal(rh, player))
			return (bresenham_algo(rh));
		if (collide_vertical(rv, player))
			return (bresenham_algo(rv));
		if (rh.length > rv.length)
		{
			rv.t_map.x += dir_rv;
			rv.t_map.y = ((player->x - rv.t_map.x) * tan + player->y);
		}
		else
		{
			rh.t_map.x += dir_hv;
			rh.t_map.y = ((player->x - rh.t_map.x) * cot + player->y);
		}
	}
}

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
