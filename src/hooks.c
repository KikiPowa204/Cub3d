/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 10:02:37 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/04 14:04:39 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	stop_player(int keycode, t_storage *dat)
{
	if (keycode == XK_a || keycode == XK_A)
		dat->player->left = false;
	else if (keycode == XK_d || keycode == XK_D)
		dat->player->right = false;
	else if (keycode == XK_w || keycode == XK_W)
		dat->player->up = false;
	else if (keycode == XK_s || keycode == XK_S)
		dat->player->down = false;
	else if (keycode == XK_Left)
		dat->player->turn_left = false;
	else if (keycode == XK_Right)
		dat->player->turn_right = false;
	recalc_player_pos(dat, dat->player);
	return (1);
}

int	move_player(int keycode, t_storage *dat)
{
	if (keycode == XK_Escape)
		exit(0);
	else if ((keycode == XK_a || keycode == XK_A))
		dat->player->left = true;
	else if ((keycode == XK_d || keycode == XK_D))
		dat->player->right = true;
	else if ((keycode == XK_w || keycode == XK_W))
		dat->player->up = true;
	else if ((keycode == XK_s || keycode == XK_S))
		dat->player->down = true;
	else if (keycode == XK_Left)
		dat->player->turn_left = true;
	else if (keycode == XK_Right)
		dat->player->turn_right = true;
	recalc_player_pos(dat, dat->player);
	return (1);
}

int	close_game(t_storage *dat)
{
	(void)dat;
	exit(0);
}

void	setup_hooks(t_storage *dat)
{
	mlx_hook(dat->img->win_ptr, DESTROY_NOTIFY, 0, close_game, dat);
	mlx_hook(dat->img->win_ptr, KEY_PRESS, 1L<<0, move_player, dat);
	mlx_hook(dat->img->win_ptr, KEY_RELEASE, 1L<<1, stop_player, dat);
	mlx_loop_hook(dat->img->mlx_ptr, frame_per_second, dat);
}
