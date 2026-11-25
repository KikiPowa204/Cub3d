/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 13:58:33 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/25 15:10:05 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir(t_storage *dat, double angle, int x, int y)
{
	dat->player->dir = angle;
	dat->player->orient.map.x = x;
	dat->player->orient.map.y = y;
}

int	add_player_dir(t_storage *dat, char dir, t_pix *inmap)
{
	if (dat->player->dir != -1)
		return (ft_error("Multiple player positions", false), 1);
	dat->player->x = inmap->x + 0.5;
	dat->player->y = inmap->y + 0.5;
	if (dir == 'N')
		set_dir(dat, HALF_PI, 0, -1);
	else if (dir == 'E')
		set_dir(dat, 0, 1, 0);
	else if (dir == 'S')
		set_dir(dat, THREE_HALF_PI, 0, 1);
	else if (dir == 'W')
		set_dir(dat, PI, -1, 0);
	return (0);
}

int	is_player(char mapi)
{
	if (mapi == 'N' || mapi == 'S' || mapi == 'E' || mapi == 'W')
		return (1);
	return (0);
}

int	check_wall(char	*map, int i, t_storage *dat, t_pix *inmap)
{
	inmap->x = i % dat->max_w;
	inmap->y = i / dat->max_w;
	if (inmap->x == 0 || inmap->y == 0 || inmap->x + 1 == dat->max_w
		|| inmap->y + 1 == dat->max_h)
		return (1);
	else if (map[i - 1] == ' ' || map[i + 1] == ' '
		|| map[i - dat->max_w] == ' '
		|| map[i + dat->max_w] == ' ')
		return (1);
	return (0);
}

int	check_map(t_storage *dat)
{
	int		i;
	char	*map;
	t_pix	inmap;

	map = dat->map;
	i = 0;
	while (dat->map[i])
	{
		if (map[i] == '0' || is_player(map[i]))
		{
			if (check_wall(map, i, dat, &inmap))
				return (ft_error("Map is not surrounded by walls", false), 1);
			if (is_player(map[i]))
				if (add_player_dir(dat, map[i], &inmap))
					return (1);
		}
		else if (map[i] != '1' && map[i] != ' ')
			return (ft_error("Unexpected character in map", false), 1);
		i++;
	}
	return (0);
}
