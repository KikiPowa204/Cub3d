/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:33:28 by knajmech          #+#    #+#             */
/*   Updated: 2026/10/29 16:59:55 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_algo_vals(t_algo *algo, t_coordinates p1, t_coordinates p2)
{
	algo->dx = abs(p1.pix.x - p2.pix.x);
	algo->dy = -abs(p1.pix.y - p2.pix.y);
	if (p1.pix.x < p2.pix.x)
		algo->dirx = 1;
	else
		algo->dirx = -1;
	if (p1.pix.y < p2.pix.y)
		algo->diry = 1;
	else
		algo->diry = -1;
	algo->d_p = algo->dx + algo->dy;
}

void	bresenham_algo(t_coordinates p1, t_coordinates p2, t_storage *data)
{
	t_algo	algo;
	int		error_temp;

	init_algo_vals(&algo, p1, p2);
	while (1)
	{
		put_pixel(data->img, p1.pix.x, p1.pix.y, p1.colour);
		if (p1.pix.x == p2.pix.x && p1.pix.y == p2.pix.y)
			break ;
		error_temp = 2 * algo.d_p;
		if (error_temp >= algo.dy)
		{
			algo.d_p += algo.dy;
			p1.pix.x += algo.dirx;
		}
		if (error_temp <= algo.dx)
		{
			algo.d_p += algo.dx;
			p1.pix.y += algo.diry;
		}
	}
}


