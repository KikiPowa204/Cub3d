/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:41:12 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/18 11:00:09 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	prep_top_right(t_coordinates *ray_h, t_coordinates *ray_v,
		t_player *player)
{
	ray_h->map.y = floor(player->y);
	ray_h->map.x = ((player->y - ray_h->map.y)
			* 1 / tan(player->a) + player->x);
	ray_v->map.x = floor(player->x) + 1;
	ray_v->map.y = ((player->x - ray_v->map.x) * tan(player->a) + player->y);
}

void	prep_top_left(t_coordinates *ray_h, t_coordinates *ray_v,
		t_player *player)
{
	ray_h->map.y = floor(player->y);
	ray_h->map.x = ((player->y - ray_h->map.y)
			* 1 / tan(player->a) + player->x);
	ray_v->map.x = floor(player->x);
	ray_v->map.y = ((player->x - ray_v->map.x) * tan(player->a) + player->y);
}

void	prep_bottom_left(t_coordinates *ray_h, t_coordinates *ray_v,
		t_player *player)
{
	ray_h->map.y = floor(player->y) + 1;
	ray_h->map.x = ((player->y - ray_h->map.y)
			* 1 / tan(player->a) + player->x);
	ray_v->map.x = floor(player->x);
	ray_v->map.y = ((player->x - ray_v->map.x) * tan(player->a) + player->y);
}

void	prep_bottom_right(t_coordinates *ray_h, t_coordinates *ray_v,
		t_player *player)
{
	ray_h->map.y = floor(player->y) + 1;
	ray_h->map.x = ((player->y - ray_h->map.y)
			* 1 / tan(player->a) + player->x);
	ray_v->map.x = floor(player->x) + 1;
	ray_v->map.y = ((player->x - ray_v->map.x) * tan(player->a) + player->y);
}

void	ray_casting(t_player *player, t_storage *data, int pos)
{
	t_coordinates	ray_h;
	t_coordinates	ray_v;

	ray_h.pos = pos;
	ray_v.pos = pos;
	if (player->a >= 0 && player->a < HALF_PI)
	{
		prep_top_right(&ray_h, &ray_v, player);
		top_right(player, data, ray_h, ray_v);
	}
	else if (player->a >= HALF_PI && player->a < PI)
	{
		prep_top_left(&ray_h, &ray_v, player);
		top_left(player, data, ray_h, ray_v);
	}
	else if (player->a >= PI && player->a < THREE_HALF_PI)
	{
		prep_bottom_left(&ray_h, &ray_v, player);
		bottom_left(player, data, ray_h, ray_v);
	}
	else if (player->a >= THREE_HALF_PI && player->a < PI * 2)
	{
		prep_bottom_right(&ray_h, &ray_v, player);
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
