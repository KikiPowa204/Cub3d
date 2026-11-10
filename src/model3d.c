/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:34:42 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/10 10:17:28 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

double	remove_distortion(double length, t_player *player)
{
	double	alpha;
	
	if (player->a < player->dir)
		alpha = player->dir - player->a;
	else
		alpha = player->a - player->dir;
	if (alpha >= 2 * PI)
		alpha -= 2 * PI;
	if (alpha < 0)
		alpha += 2 * PI;
	return (length * cos(alpha));
}

void	model3d(t_coordinates ray, t_storage *data)
{
	double	height;
	int			x;
	int			y;
	double		norm_dist;

	norm_dist = remove_distortion(ray.length, data->player);
	height = WINDOW_HEIGHT / norm_dist;
	if (height > WINDOW_HEIGHT)
		height = WINDOW_HEIGHT;
	y = WINDOW_HEIGHT / 2 - height / 2;
	x = ray.pos;
	while (y < (WINDOW_HEIGHT / 2 - height / 2) + height)
	{
		put_pixel_3d(data->img, x, y, 0x00FFFF);
		y++;
	}
}
