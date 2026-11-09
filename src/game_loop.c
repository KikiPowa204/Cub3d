/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:13:40 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/09 14:51:08 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdbool.h>

/*
unsigned int normalise(t_player *player, int max_d, t_dir type)
{
	if (type == UP)
		return ((unsigned int)(player->y + player->orient.map.y * 0.2) * max_d + ((unsigned int)player->x + player->orient.map.x * 0.2));
	if (type == DOWN)
		return ((unsigned int)(player->y + 0.2) * max_d + (unsigned int)player->x);
	// if (type == LEFT)
	// 	return ((unsigned int)player->y * max_d + (unsigned int)(player->x - 0.2));
	// if (type == RIGHT)
	// 	return ((unsigned int)player->y * max_d + (unsigned int)(player->x + 0.2));
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
*/

void	calculate_dir(t_player *player)
{
//	double old_orient_x;
	
	if (player->turn_right || player->turn_left)
	{
		if (player->turn_right)
		{
			player->dir += 0.1;
			if (player->dir >= 2*PI)
				player->dir -= 2*PI;
			// old_orient_x = player->orient.map.x;
			// player->orient.map.x = player->orient.map.x * cos(-player->dir) - player->orient.map.y * sin(-player->dir);
      		// player->orient.map.y = old_orient_x * sin(-player->dir) + player->orient.map.y * cos(-player->dir);
		}
		if (player->turn_left)
		{
			player->dir -= 0.1;
			if (player->dir <= 0)
				player->dir += 2*PI;
			// old_orient_x = player->orient.map.x;
			// player->orient.map.x = player->orient.map.x * cos(player->dir) - player->orient.map.y * sin(player->dir);
      		// player->orient.map.y = old_orient_x * sin(player->dir) + player->orient.map.y * cos(player->dir);
		}
		player->orient.map.x = cos(player->dir);
		player->orient.map.y = - sin(player->dir);
	}
}

void	move(t_storage *dat, t_player *player, t_dir direction)
{
	double	dx;
	double	dy;
	int		sign;

	sign = 1;
	if (direction == DOWN)
		sign = -1;
	dx = sign * player->orient.map.x * (double)SPEED;
	dy = sign * player->orient.map.y * (double)SPEED;
	if (!is_wall(player->x + dx + copysign(0.2, dx), player->y, dat))
		player->x += dx;
	if (!is_wall(player->x, player->y + dy + copysign(0.2, dy), dat))
		player->y += dy;
}

void	recalc_player_pos(t_storage *dat, t_player *player)
{
	calculate_dir(player);
	if (player->up == true)
		move(dat, player, UP);
	if (player->down == true)
		move(dat, player, DOWN);
	if (player->right == true)
	{
		player->orient.map.y = -player->orient.map.y;
		move(dat, player, LEFT);
	}
	if (player->left == true)
	{
		player->orient.map.x = -player->orient.map.x;
		move(dat, player, RIGHT);
	}
}

/*
void	recalc_player_pos(t_storage *dat, t_player *player)
{
	calculate_dir(player);
	if (player->up && no_collission(dat, UP))
	{
		player->x += player->orient.map.x * 0.05;
		player->y += player->orient.map.y * 0.05;
	}
	if (player->down && no_collission(dat, DOWN))
	{
		player->x -= player->orient.map.x * 0.05;
		player->y -= player->orient.map.y * 0.05;
	}
	// if (player->left) //&& no_collission(dat, LEFT))
	// {
	// 	player->x += player->orient.map.x * 0.05;
	// 	player->y += player->orient.map.y * 0.05;
	// }
	// if (player->right) // && no_collission(dat, RIGHT))
	// {
	// 	player->x += player->orient.map.x * 0.05;
	// 	player->y += player->orient.map.y * 0.05;
	// }
	// if (player->left && no_collission(dat, LEFT))
	// 	player->x -= 0.05;
	// if (player->right && no_collission(dat, RIGHT))
	// 	player->x += 0.05;
	
}
	*/

/*
void	recalc_player_pos(t_storage *dat, t_player *player)
{
	if (player->up && no_collission(dat, UP))
	{
		player->x = player->x + cos(player->dir) * 0.05;
		player->y = player->y + sin(player->dir) * 0.05;
	}
	if (player->down && no_collission(dat, DOWN))
		player->y += 0.05;
	if (player->left && no_collission(dat, LEFT))
		player->x -= 0.05;
	if (player->right && no_collission(dat, RIGHT))
		player->x += 0.05;
	calculate_ray(player);
}*/
