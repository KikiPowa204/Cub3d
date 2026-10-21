/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:13:40 by knajmech          #+#    #+#             */
/*   Updated: 2026/10/21 15:36:56 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int normalise(t_player *player, int max_d, t_dir type)
{
	if (type == UP)
		return (unsigned int) (player->y * max_d + player->y - 0.1);
	if (type == DOWN)
		return (unsigned int) (player->y * max_d + player->y + 0.1);
	if (type == LEFT)
		return (unsigned int) (player->x * max_d + player->x - 0.1);
	if (type == RIGHT)
		return (unsigned int) (player->x * max_d + player->x + 0.1);
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
void	recalc_player_pos(t_storage *dat, t_player *player)
{
	(void)dat;
	//printf("here\n");
	if (player->up)// && no_collission(dat, UP))
		player->y -= 0.1;
	if (player->down) //&& no_collission(dat, DOWN))
		player->y += 0.1;
	if (player->left) //&& no_collission(dat, LEFT))
		player->x -= 0.1;
	if (player->right) //&& no_collission(dat, RIGHT))
		player->x += 0.1;
}
