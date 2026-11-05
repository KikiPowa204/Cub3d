/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:34:42 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/05 10:39:20 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	model3d(t_coordinates ray, t_storage *data)
{
	double	height;
	int			x;
	int			y;

	height = WINDOW_HEIGHT / ray.length;
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
