/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 09:43:52 by knajmech          #+#    #+#             */
/*   Updated: 2026/10/29 11:12:14 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

t_voh	ray_collision(t_storage *dat, t_voh voh, int x, int y)
{
	bool	vert;
	bool	hort;

	vert = false;
	hort = false;
	if (voh == ver)
		if (check_if_wall(x, y, dat->img->max_h, dat->map))
			return (ver);
	else
		if (check_if_wall(x, y, dat->img->max_w, dat->map))
			return (hor);
	return (none);
}

t_voh	ray_collision(t_storage *dat, t_voh voh, int x, int y)
{
	t_voh			voh;
	t_coordinates	ver;
	t_coordinates	hor;
}
