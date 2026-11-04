/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 17:11:30 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/04 14:06:02 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cone_casting(t_storage *dat)
{
	double	angle_between_each_ray;
	double	end_point;
	int		i;

	dat->player->a = dat->player->dir - PI / 6;
	if (dat->player->a < 0)
		dat->player->a += (2 * PI);
	end_point = dat->player->a + PI / 3;
	if (end_point > 2 * PI)
		end_point -= (2 * PI);
	angle_between_each_ray = PI / 3 / WINDOW_WIDTH;
	i = 0;
	while(i < WINDOW_WIDTH)
	{
		ray_casting(dat->player, dat);
		dat->player->a += angle_between_each_ray;
		if (dat->player->a > 2 * PI)
			dat->player->a -= (2 * PI);
		i++;
	}
}