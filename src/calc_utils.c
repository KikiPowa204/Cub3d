/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 15:27:22 by knajmech          #+#    #+#             */
/*   Updated: 2026/10/28 12:01:11 by knajmech         ###   ########.fr       */
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

