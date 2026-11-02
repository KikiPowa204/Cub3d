/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:41:12 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/02 18:10:24 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "stdio.h"

void	top_right(t_player *player, t_storage *data)
{
	double			cot;
	double			tan_a;
	t_coordinates	rh;
	t_coordinates	rv;
	bool			hor;
	bool			vert;
	
	hor = false;
	cot = 0;
	if (player->a > 0.01)
	{
		cot = 1/tan(player->a);
		rh.map.y = (int)player->y;
		rh.map.x = ((player->y - rh.map.y) * cot + player->x);
		hor = true;
		//rh.length = distance(player->x, player->y, rh.map.x, rh.map.y);
	}
	else
		ft_bzero(&rh, sizeof(t_coordinates));
	tan_a = tan(player->a);
	rv.map.x = (int)player->x + 1;
	rv.map.y = ((player->x - rv.map.x) * tan_a + player->y);
	
	//rv.length = distance(player->x, player->y, rv.map.x, rv.map.y);
	// if (rh.length < rv.length && rh.length != 0)
	// 	return (bresenham_algo(bres_transform(player->x, player->y),
	// 		bres_transform(rh.map.x, rh.map.y), data));
	// else
	// 	return (bresenham_algo(bres_transform(player->x, player->y),
	// 		bres_transform(rv.map.x, rv.map.y), data));
	
}

void	ray_casting(t_player *player, t_storage *data)
{
	if (player->a >= 0 && player->a < HALF_PI)
		top_right(player, data);
}
