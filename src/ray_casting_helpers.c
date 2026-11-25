/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:34:52 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/25 08:22:48 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	alter_values(double vector, double *map_coordi, int dir, double *count)
{
	*count += dir;
	if (dir < 0)
		*map_coordi += vector;
	else
		*map_coordi -= vector;
}

bool	is_wall(double x, double y, t_storage *d)
{
	if (x < 0 || y < 0 || x >= d->max_w || y >= d->max_h)
		return (true);
	return (d->map[(int)y * d->max_w + (int)x] == WALL);
}

bool	collide_horizontal(t_coordinates *rh, t_player *player,
		t_storage *data, t_dir dir)
{
	if (dir == UP && is_wall(rh->map.x, rh->map.y - 1, data))
	{
		rh->length = distance(player->x, player->y, rh->map.x, rh->map.y);
		return (true);
	}
	if (dir == DOWN && is_wall(rh->map.x, rh->map.y, data))
	{
		rh->length = distance(player->x, player->y, rh->map.x, rh->map.y);
		return (true);
	}
	return (false);
}

bool	collide_vertical(t_coordinates *rv, t_player *player,
		t_storage *data, t_dir dir)
{
	if (dir == RIGHT && is_wall(rv->map.x, rv->map.y, data))
	{
		rv->length = distance(player->x, player->y, rv->map.x, rv->map.y);
		return (true);
	}
	if (dir == LEFT && is_wall(rv->map.x - 1, rv->map.y, data))
	{
		rv->length = distance(player->x, player->y, rv->map.x, rv->map.y);
		return (true);
	}
	return (false);
}
