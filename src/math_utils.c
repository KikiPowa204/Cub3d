/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 10:37:56 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/18 10:40:42 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coordinates	bres_transform(double x, double y)
{
	t_coordinates	p;

	p.pix.x = map_to_screen(x);
	p.pix.y = map_to_screen(y);
	p.pix.z = 0;
	p.colour = 0xff59fe;
	return (p);
}

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
