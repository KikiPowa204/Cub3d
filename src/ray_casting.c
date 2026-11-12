/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:41:12 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/11 10:58:29 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "stdio.h"

t_map	get_horizontal();
t_map	get_vertical();

void	top_right(t_player *player, t_storage *data, t_coordinates ray_h,
		t_coordinates ray_v)
{
	double			tan_a;
	double			cot;

	ray_h.length = INFINITY;
	cot = 1/tan(player->a);
	tan_a = tan(player->a);
	if (player->a > 0.000001)
		while (collide_horizontal(&ray_h, player, data, UP) == false)
		{
			ray_h.map.y -= 1;
			ray_h.map.x += cot;
		}
	while (collide_vertical(&ray_v, player, data, RIGHT) == false)
	{
		ray_v.map.x += 1;
		ray_v.map.y -= tan_a;
	}
	if (ray_v.length > ray_h.length)
	{
		ray_h.tex = NORTH;
		model3d(ray_h, data);
		bresenham_algo(bres_transform(player->x, player->y),
				bres_transform(ray_h.map.x, ray_h.map.y), data);
	}
	else
	{
		ray_v.tex = WEST;
		model3d(ray_v, data);
		bresenham_algo(bres_transform(player->x, player->y),
				bres_transform(ray_v.map.x, ray_v.map.y), data);
	}
}

void	top_left(t_player *player, t_storage *data, t_coordinates ray_h,
		t_coordinates ray_v)
{
	double			tan_a;
	double			cot;

	ray_h.length = INFINITY;
	cot = 1/tan(player->a);
	tan_a = tan(player->a);
	while (collide_horizontal(&ray_h, player, data, UP) == false)
	{
		ray_h.map.y -= 1;
		ray_h.map.x += cot;
	}
	while (collide_vertical(&ray_v, player, data, LEFT) == false)
	{
		ray_v.map.x -= 1;
		ray_v.map.y += tan_a;
	}
	if (ray_v.length > ray_h.length)
	{
		ray_h.tex = NORTH;
		model3d(ray_h, data);
		bresenham_algo(bres_transform(player->x, player->y),
				bres_transform(ray_h.map.x, ray_h.map.y), data);
	}
	else
	{
		ray_v.tex = EAST;
		model3d(ray_v, data);
		bresenham_algo(bres_transform(player->x, player->y),
				bres_transform(ray_v.map.x, ray_v.map.y), data);
	}
}

void	bottom_left(t_player *player, t_storage *data, t_coordinates ray_h,
		t_coordinates ray_v)
{
	double			tan_a;
	double			cot;

	ray_h.length = INFINITY;
	cot = 1/tan(player->a);
	tan_a = tan(player->a);
	while (collide_horizontal(&ray_h, player, data, DOWN) == false)
	{
		ray_h.map.y += 1;
		ray_h.map.x -= cot;
	}
	while (collide_vertical(&ray_v, player, data, LEFT) == false)
	{
		ray_v.map.x -= 1;
		ray_v.map.y += tan_a;
	}
	if (ray_v.length > ray_h.length)
	{
		ray_h.tex = SOUTH;
		model3d(ray_h, data);
		bresenham_algo(bres_transform(player->x, player->y),
				bres_transform(ray_h.map.x, ray_h.map.y), data);
	}
	else
	{
		ray_v.tex = EAST;
		model3d(ray_v, data);
		bresenham_algo(bres_transform(player->x, player->y),
				bres_transform(ray_v.map.x, ray_v.map.y), data);
	}
}

void	bottom_right(t_player *player, t_storage *data, t_coordinates ray_h,
		t_coordinates ray_v)
{
	double			tan_a;
	double			cot;

	ray_h.length = INFINITY;
	cot = 1/tan(player->a);
	tan_a = tan(player->a);
	while (collide_horizontal(&ray_h, player, data, DOWN) == false)
	{
		ray_h.map.y += 1;
		ray_h.map.x -= cot;
	}
	while (collide_vertical(&ray_v, player, data, RIGHT) == false)
	{
		ray_v.map.x += 1;
		ray_v.map.y -= tan_a;
	}
	if (ray_v.length > ray_h.length)
	{
		ray_h.tex = SOUTH;
		model3d(ray_h, data);
		bresenham_algo(bres_transform(player->x, player->y),
				bres_transform(ray_h.map.x, ray_h.map.y), data);
	}
	else
	{
		ray_v.tex = WEST;
		model3d(ray_v, data);
		bresenham_algo(bres_transform(player->x, player->y),
				bres_transform(ray_v.map.x, ray_v.map.y), data);
	}
}

void	ray_casting(t_player *player, t_storage *data, int pos)
{
	t_coordinates	ray_h;
	t_coordinates	ray_v;

	ray_h.pos = pos;
	ray_v.pos = pos;
	if (player->a >= 0 && player->a < HALF_PI)
	{
		ray_h.map.y = floor(player->y);
		ray_h.map.x = ((player->y - ray_h.map.y) * 1/tan(player->a) + player->x);
		ray_v.map.x = floor(player->x) + 1;
		ray_v.map.y = ((player->x - ray_v.map.x) * tan(player->a) + player->y);
		top_right(player, data, ray_h, ray_v);
	}
	else if (player->a >= HALF_PI && player->a < PI)
	{
		ray_h.map.y = floor(player->y);
		ray_h.map.x = ((player->y - ray_h.map.y) * 1/tan(player->a) + player->x);
		ray_v.map.x = floor(player->x);
		ray_v.map.y = ((player->x - ray_v.map.x) * tan(player->a) + player->y);
		top_left(player, data, ray_h, ray_v);
	}
	else if (player->a >= PI && player->a < THREE_HALF_PI)
	{
		ray_h.map.y = floor(player->y) + 1;
		ray_h.map.x = ((player->y - ray_h.map.y) * 1/tan(player->a) + player->x);
		ray_v.map.x = floor(player->x);
		ray_v.map.y = ((player->x - ray_v.map.x) * tan(player->a) + player->y);
		bottom_left(player, data, ray_h, ray_v);
	}
	else if (player->a >= THREE_HALF_PI && player->a < PI * 2)
	{
		ray_h.map.y = floor(player->y) + 1;
		ray_h.map.x = ((player->y - ray_h.map.y) * 1/tan(player->a) + player->x);
		ray_v.map.x = floor(player->x) + 1;
		ray_v.map.y = ((player->x - ray_v.map.x) * tan(player->a) + player->y);
		bottom_right(player, data, ray_h, ray_v);
	}
}

/*
#define FOV		(PI / 3)		// 60 degrees
#define NUM_RAYS	60

static double	norm_angle(double a)
{
	while (a < 0)
		a += 2 * PI;
	while (a >= 2 * PI)
		a -= 2 * PI;
	return (a);
}

void	cast_cone(t_player *player, t_storage *data)
{
	double	center;
	double	start;
	double	step;
	int		i;

	center = player->a;
	start = center - FOV / 2;
	step = FOV / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		player->a = norm_angle(start + i * step);
		ray_casting(player, data);
		i++;
	}
	player->a = center;
}*/
