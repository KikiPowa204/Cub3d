/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:13:40 by knajmech          #+#    #+#             */
/*   Updated: 2026/10/22 15:15:52 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int normalise(t_player *player, int max_d, t_dir type)
{
	if (type == UP)
		return ((unsigned int)(player->y - 0.1) * max_d + (unsigned int)player->x);
	if (type == DOWN)
		return ((unsigned int)(player->y + 0.1) * max_d + (unsigned int)player->x);
	if (type == LEFT)
		return ((unsigned int)player->y * max_d + (unsigned int)(player->x - 0.1));
	if (type == RIGHT)
		return ((unsigned int)player->y * max_d + (unsigned int)(player->x + 0.1));
	return (0);
}

bool	no_collission(t_storage *dat, t_dir dir)
{
	if (dir == UP)
		if (map[normalise(dat->player, dat->img->max_w, UP)] == WALL)
			return (false);
	if (dir == DOWN)
		if (map[normalise(dat->player, dat->img->max_w, DOWN)] == WALL)
			return (false);
	if (dir == LEFT)
		if (map[normalise(dat->player, dat->img->max_h, LEFT)] == WALL)
			return (false);
	if (dir == RIGHT)
		if (map[normalise(dat->player, dat->img->max_h, RIGHT)] == WALL)
			return (false);
	return (true);
}
#include <stdio.h>
void	calculate_rotation(t_player *player)
{
	if (player->turn_right)
	{
		player->a -= 0.1;
		if (player->a < 0)
			player->a += 2*PI;
	}
	if (player->turn_left)
	{
		player->a += 0.1;
		if (player->a > 2*PI)
			player->a -= 2*PI;
	}
	player->p1.x = player->x;
	player->p1.y = player->y;
	player->p2.x = player->x + cos(player->a) * 20;
	player->p2.y = player->y + sin(player->a) * 20;
	printf("x: %d, %d\n y:%d, %d\n", player->p1.x, player->p2.x, player->p1.y, player->p2.y);
}

void	recalc_player_pos(t_storage *dat, t_player *player)
{
	if (player->up && !player->down && no_collission(dat, UP))
		player->y -= 0.05;
	if (player->down && !player->up && no_collission(dat, DOWN))
		player->y += 0.05;
	if (player->left && !player->right &&no_collission(dat, LEFT))
		player->x -= 0.05;
	if (player->right && !player->left && no_collission(dat, RIGHT))
		player->x += 0.05;
	if (player->turn_right || player->turn_left)
		calculate_rotation(player);
}
