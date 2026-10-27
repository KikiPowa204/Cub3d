/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:33:28 by knajmech          #+#    #+#             */
/*   Updated: 2026/10/22 15:19:27 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_algo_vals(t_algo *algo, t_coordinates p1, t_coordinates p2)
{
	algo->dx = abs(p1.x - p2.x);
	algo->dy = -abs(p1.y - p2.y);
	if (p1.x < p2.x)
		algo->dirx = 1;
	else
		algo->dirx = -1;
	if (p1.y < p2.y)
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
		put_pixel(data->img, p1.x, p1.y, 0xAB1D6F);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		error_temp = 2 * algo.d_p;
		if (error_temp >= algo.dy)
		{
			algo.d_p += algo.dy;
			p1.x += algo.dirx;
		}
		if (error_temp <= algo.dx)
		{
			algo.d_p += algo.dx;
			p1.y += algo.diry;
		}
	}
}


