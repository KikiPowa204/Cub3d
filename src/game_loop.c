/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:13:40 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/03 17:30:32 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int normalise(t_player *player, int max_d, t_dir type)
{
	if (type == UP)
		return ((unsigned int)(player->y - 0.2) * max_d + (unsigned int)player->x);
	if (type == DOWN)
		return ((unsigned int)(player->y + 0.2) * max_d + (unsigned int)player->x);
	if (type == LEFT)
		return ((unsigned int)player->y * max_d + (unsigned int)(player->x - 0.2));
	if (type == RIGHT)
		return ((unsigned int)player->y * max_d + (unsigned int)(player->x + 0.2));
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

void	calculate_ray(t_player *player)
{
	if (player->turn_right || player->turn_left)
	{
		if (player->turn_right)
		{
			player->dir -= 0.1;
			if (player->dir <= 0)
				player->dir += 2*PI;
		}
		if (player->turn_left)
		{
			player->dir += 0.1;
			if (player->dir >= 2*PI)
				player->dir -= 2*PI;
		}
	}
	player->p1.pix.x = player->x * TILE_SIZE;
	player->p1.pix.y = player->y * TILE_SIZE;
	player->p2.pix.x = player->x * TILE_SIZE + cos(player->a) * 20;
	player->p2.pix.y = player->y * TILE_SIZE + sin(player->a) * -20;
}

void	recalc_player_pos(t_storage *dat, t_player *player)
{
	if (player->up && no_collission(dat, UP))
		player->y -= 0.05;
	if (player->down && no_collission(dat, DOWN))
		player->y += 0.05;
	if (player->left && no_collission(dat, LEFT))
		player->x -= 0.05;
	if (player->right && no_collission(dat, RIGHT))
		player->x += 0.05;
	calculate_ray(player);
}
