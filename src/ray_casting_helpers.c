/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:34:52 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/09 14:22:45 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
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

bool	is_wall(double x, double y, t_storage *d)
{
	if (x < 0 || y < 0 || x >= d->img->max_w || y >= d->img->max_h)
		return (true);               // outside the map ends the ray
	return (map[(int)y * d->img->max_w + (int)x] == WALL);
}

bool	ray_collision(t_map ray, t_player *player, t_dir dir, t_storage *data)
{
	if (dir == HORI && player->a < PI)
	{
		if (map[(((int)ray.y - 1) * data->img->max_w + (int)ray.x)] == WALL)
			return (1);
	}
	else if (dir == HORI && player->a > PI)
	{
		if (map[((int)ray.y * data->img->max_w + (int)ray.x)] == WALL)
			return (1);
	}
	else if (dir == VERT && (player->a < HALF_PI || player->a > THREE_HALF_PI))
	{
		if (map[((int)ray.y * data->img->max_w + (int)ray.x + 1)] == WALL)
			return (1);
	}
	else 
	{
		if (map[((int)ray.y * data->img->max_w + ((int)ray.x - 1))] == WALL)
			return (1);
	}
	return (0);
}

bool	both_collide(t_coordinates rh, t_coordinates rv, t_player *player, t_storage *data)
{
	if (rh.map.x >= data->img->max_w || rh.map.y >= data->img->max_h
		|| rh.map.x < 0 || rh.map.y < 0
		|| rv.map.x >= data->img->max_w || rv.map.y >= data->img->max_h
		|| rv.map.x < 0 || rv.map.y < 0)
		return (false);
	if (ray_collision(rv.map, player, VERT, data)
			&& ray_collision(rh.map, player, HORI, data))
		return (true);
	return (false);
}

bool	collide_horizontal(t_coordinates *rh, t_player *player, t_storage *data, t_dir dir)
{
	if (dir == UP && is_wall(rh->map.x, rh->map.y - 1, data)) //ray_collision(rh->map, player, HORI, data))
	{
		rh->length = distance(player->x, player->y, rh->map.x, rh->map.y);
		return (true);
	}
	if (dir == DOWN && is_wall(rh->map.x, rh->map.y, data)) //ray_collision(rh->map, player, HORI, data))
	{
		rh->length = distance(player->x, player->y, rh->map.x, rh->map.y);
		return (true);
	}
	return (false);
}

bool	collide_vertical(t_coordinates *rv, t_player *player, t_storage *data, t_dir dir)
{
	if (dir == RIGHT && is_wall(rv->map.x, rv->map.y, data)) //&& ray_collision(rv->map, player, VERT, data))
	{
		rv->length = distance(player->x, player->y, rv->map.x, rv->map.y);
		return (true);
	}
	if (dir == LEFT && is_wall(rv->map.x - 1, rv->map.y, data)) //&& ray_collision(rv->map, player, VERT, data))
	{
		rv->length = distance(player->x, player->y, rv->map.x, rv->map.y);
		return (true);
	}
	return (false);
}

t_coordinates	bres_transform(double x, double y)
{
	t_coordinates	p;

	p.pix.x = map_to_screen(x);
	p.pix.y = map_to_screen(y);
	p.pix.z = 0;
	p.colour = 0xff59fe;
	return (p);
}

/*
void	ray_casting(t_player *player, t_storage *data)
{
	double		cot;
	double		tan_a;
	t_coordinates	rh;
	t_coordinates	rv;
	int			dir_h;
	int			dir_v;
	
	rh.map.x = player->x;
	rh.map.y = player->y;
	rv.map.x = player->x;
	rv.map.y = player->y;
	if (tan(player->a) > 0.001 || tan(player->a) < -0.001)
	{
		cot = 1/tan(player->a);
		if (player->a < PI)
		{
			dir_h = -1;
			rh.map.y = (int)player->y;
		}
		else if (player->a > PI)
		{
			dir_v = 1;
			rh.map.y = (int)player->y + 1;
		}
		rh.map.x = ((player->y - rh.map.y) * cot + player->x);
		rh.length = distance(player->x, player->y, rh.map.x, rh.map.y);
	}
	else
		ft_bzero(&rh, sizeof(t_coordinates));
	tan_a = tan(player->a);
	if (player->a <= HALF_PI || player->a >= THREE_HALF_PI)
	{
		dir_v = 1;
		rv.map.x = (int)player->x + 1;
	}
	else if (player->a > HALF_PI && player->a < THREE_HALF_PI)
	{
		dir_v = -1;
		rv.map.x = (int)player->x;
	}
	rv.map.y = ((player->x - rv.map.x) * tan_a + player->y);
	rv.length = distance(player->x, player->y, rv.map.x, rv.map.y);
	if (both_collide(rh, rv, player, data))
	{
		if (rh.length < rv.length)
			return (bresenham_algo(bres_transform(player->x, player->y), bres_transform(rh.map.x, rh.map.y), data));
		else
			return (bresenham_algo(bres_transform(player->x, player->y), bres_transform(rv.map.x, rv.map.y), data));
	}
	while (42)
	{
		if (collide_horizontal(rh, player, data))
			return (bresenham_algo(bres_transform(player->x, player->y), bres_transform(rh.map.x, rh.map.y), data));	
		if (collide_vertical(rv, player, data))
			return (bresenham_algo(bres_transform(player->x, player->y), bres_transform(rv.map.x, rv.map.y), data));
		if (rh.length > rv.length)
		{
			rv.map.x += dir_v;
			rv.map.y = ((player->x - rv.map.x) * tan_a + player->y);
		}
		else
		{
			rh.map.x += dir_h;
			rh.map.y = ((player->x - rh.map.x) * cot + player->y);
		}
	}
}
*/

/*
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
*/
