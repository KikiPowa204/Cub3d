/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_quadrants.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 10:44:27 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/24 11:53:43 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	top_right(t_player *player, t_storage *data, t_coordinates ray_h,
		t_coordinates ray_v)
{
	double			tan_a;
	double			cot;

	ray_h.length = INFINITY;
	cot = 1 / tan(player->a);
	tan_a = tan(player->a);
	if (player->a > 0.000001)
		while (collide_horizontal(&ray_h, player, data, UP) == false)
			alter_values(cot, &ray_h.map.x, -1, &ray_h.map.y);
	while (collide_vertical(&ray_v, player, data, RIGHT) == false)
		alter_values(tan_a, &ray_v.map.y, 1, &ray_v.map.x);
	if (ray_v.length > ray_h.length)
	{
		ray_h.tex = NORTH;
		model3d(ray_h, data);
		bresenham_algo(bres_transform(player->x, player->y, data->mini),
			bres_transform(ray_h.map.x, ray_h.map.y, data->mini), data);
	}
	else
	{
		ray_v.tex = WEST;
		model3d(ray_v, data);
		bresenham_algo(bres_transform(player->x, player->y, data->mini),
			bres_transform(ray_v.map.x, ray_v.map.y, data->mini), data);
	}
}

void	top_left(t_player *player, t_storage *data, t_coordinates ray_h,
		t_coordinates ray_v)
{
	double			tan_a;
	double			cot;

	ray_h.length = INFINITY;
	cot = 1 / tan(player->a);
	tan_a = tan(player->a);
	while (collide_horizontal(&ray_h, player, data, UP) == false)
		alter_values(cot, &ray_h.map.x, -1, &ray_h.map.y);
	while (collide_vertical(&ray_v, player, data, LEFT) == false)
		alter_values(tan_a, &ray_v.map.y, -1, &ray_v.map.x);
	if (ray_v.length > ray_h.length)
	{
		ray_h.tex = NORTH;
		model3d(ray_h, data);
		bresenham_algo(bres_transform(player->x, player->y, data->mini),
			bres_transform(ray_h.map.x, ray_h.map.y, data->mini), data);
	}
	else
	{
		ray_v.tex = EAST;
		model3d(ray_v, data);
		bresenham_algo(bres_transform(player->x, player->y, data->mini),
			bres_transform(ray_v.map.x, ray_v.map.y, data->mini), data);
	}
}

void	bottom_left(t_player *player, t_storage *data, t_coordinates ray_h,
		t_coordinates ray_v)
{
	double			tan_a;
	double			cot;

	ray_h.length = INFINITY;
	cot = 1 / tan(player->a);
	tan_a = tan(player->a);
	while (collide_horizontal(&ray_h, player, data, DOWN) == false)
		alter_values(cot, &ray_h.map.x, 1, &ray_h.map.y);
	while (collide_vertical(&ray_v, player, data, LEFT) == false)
		alter_values(tan_a, &ray_v.map.y, -1, &ray_v.map.x);
	if (ray_v.length > ray_h.length)
	{
		ray_h.tex = SOUTH;
		model3d(ray_h, data);
		bresenham_algo(bres_transform(player->x, player->y, data->mini),
			bres_transform(ray_h.map.x, ray_h.map.y, data->mini), data);
	}
	else
	{
		ray_v.tex = EAST;
		model3d(ray_v, data);
		bresenham_algo(bres_transform(player->x, player->y, data->mini),
			bres_transform(ray_v.map.x, ray_v.map.y, data->mini), data);
	}
}

void	bottom_right(t_player *player, t_storage *data, t_coordinates ray_h,
		t_coordinates ray_v)
{
	double			tan_a;
	double			cot;

	ray_h.length = INFINITY;
	cot = 1 / tan(player->a);
	tan_a = tan(player->a);
	while (collide_horizontal(&ray_h, player, data, DOWN) == false)
		alter_values(cot, &ray_h.map.x, 1, &ray_h.map.y);
	while (collide_vertical(&ray_v, player, data, RIGHT) == false)
		alter_values(tan_a, &ray_v.map.y, 1, &ray_v.map.x);
	if (ray_v.length > ray_h.length)
	{
		ray_h.tex = SOUTH;
		model3d(ray_h, data);
		bresenham_algo(bres_transform(player->x, player->y, data->mini),
			bres_transform(ray_h.map.x, ray_h.map.y, data->mini), data);
	}
	else
	{
		ray_v.tex = WEST;
		model3d(ray_v, data);
		bresenham_algo(bres_transform(player->x, player->y, data->mini),
			bres_transform(ray_v.map.x, ray_v.map.y, data->mini), data);
	}
}
