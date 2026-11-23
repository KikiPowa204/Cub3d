/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 15:27:22 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/23 17:59:43 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_to_screen(double coordinate)
{
	return (coordinate * TILE_SIZE);
}

int	get_map_index(int rx, int ry, int max_d)
{
	return (ry / TILE_SIZE * max_d + rx / TILE_SIZE);
}

bool	check_if_wall(int x, int y, int max_d, char *map)
{
	return (map[get_map_index(x, y, max_d)] != WALL);
}


