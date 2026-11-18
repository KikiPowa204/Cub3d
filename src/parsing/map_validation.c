/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 13:58:33 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/18 17:30:46 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_wall(char	*map, int i, size_t width, size_t height)
{
	size_t	x;
	size_t	y;
	
	x = i % width;
	y = i / width;
	if (x == 0 || y == 0 || x + 1 == width || y + 1 == height)
		return (1);
	else if (map[i - 1] == ' ' || map[i + 1] == ' ' || map[i - width] == ' '
		|| map[i + width] == ' ')
		return (1);
	return (0);
}

int	add_player_dir(t_storage *dat, char	dir)
{
	if (dat->player->dir != -1)
		return (error("Multiple player positions", false), 1);
	if (dir == 'N')
		dat->player->dir = HALF_PI;
	else if (dir == 'E')
		dat->player->dir = 0;
	else if (dir == 'S')
		dat->player->dir = THREE_HALF_PI;
	else if (dir == 'W')
		dat->player->dir = PI;
	return (0);
}
int	is_player(char mapi)
{
	if (mapi == 'N' || mapi == 'S' || mapi == 'E' || mapi == 'W')
		return (1);
	return (0);
}

int	check_map(t_storage *dat, size_t max_width, size_t height)
{
	int		i;
	char	*map;
	
	map = dat->map;
	i = 0;
	while(dat->map[i])
	{
		if (map[i] == '0' || is_player(map[i]))
		{
			if (check_wall(map, i, max_width, height))
				return (error("Map is not surrounded by walls", false), 1);
			if (is_player(map[i]))
				if (add_player_dir(dat, map[i]))
					return (1);
		}
		else if (map[i] != '1' && map[i] != ' ')
			return (error("Unexpected character in map", false), 1);
		i++;
	}
	return (0);
}
