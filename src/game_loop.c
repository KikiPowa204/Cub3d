/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:13:40 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/25 11:18:46 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_dir(t_player *player)
{
	if (player->turn_right || player->turn_left)
	{
		if (player->turn_left)
		{
			player->dir += 0.1;
			if (player->dir >= 2 * PI)
				player->dir -= 2 * PI;
		}
		if (player->turn_right)
		{
			player->dir -= 0.1;
			if (player->dir <= 0)
				player->dir += 2 * PI;
		}
		player->orient.map.x = cos(player->dir);
		player->orient.map.y = -sin(player->dir);
	}
}

void	move(t_storage *dat, t_player *player, double orient_x, double orient_y)
{
	double	dx;
	double	dy;

	dx = orient_x * (double)player->speed;
	dy = orient_y * (double)player->speed;
	if (!is_wall(player->x + dx + copysign(0.2, dx), player->y, dat))
		player->x += dx;
	if (!is_wall(player->x, player->y + dy + copysign(0.2, dy), dat))
		player->y += dy;
}

void	recalc_player_pos(t_storage *dat, t_player *player)
{
	calculate_dir(player);
	if (player->up == true)
		move(dat, player, player->orient.map.x, player->orient.map.y);
	if (player->down == true)
		move(dat, player, -player->orient.map.x, -player->orient.map.y);
	if (player->left == true)
		move(dat, player, player->orient.map.y, -player->orient.map.x);
	if (player->right == true)
		move(dat, player, -player->orient.map.y, player->orient.map.x);
}

// To move forward you add the direction vector (player->orientation)
// to move back you substract that vector
// moving sideways (transforming the vector perpendicular)
// it swaps x and y and for right you do a negative y
// and left you do a negative x
