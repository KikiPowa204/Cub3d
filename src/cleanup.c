/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 09:53:37 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/25 12:45:38 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_img(void *mlx_ptr, void *txt_ptr, int (f)(void *, void *))
{
	if (txt_ptr)
		f(mlx_ptr, txt_ptr);
}

void	cleanup(t_storage *dat)
{
	free(dat->map);
	destroy_img(dat->mlx_ptr, dat->walls.north.txt_ptr, mlx_destroy_image);
	destroy_img(dat->mlx_ptr, dat->walls.south.txt_ptr, mlx_destroy_image);
	destroy_img(dat->mlx_ptr, dat->walls.east.txt_ptr, mlx_destroy_image);
	destroy_img(dat->mlx_ptr, dat->walls.west.txt_ptr, mlx_destroy_image);
	destroy_img(dat->mlx_ptr, dat->img_3d->img_ptr, mlx_destroy_image);
	destroy_img(dat->mlx_ptr, dat->img_mini->img_ptr, mlx_destroy_image);
	destroy_img(dat->mlx_ptr, dat->win_ptr, mlx_clear_window);
	destroy_img(dat->mlx_ptr, dat->win_ptr, mlx_destroy_window);
	if (dat->mlx_ptr)
		mlx_destroy_display(dat->mlx_ptr);
	free(dat->mlx_ptr);
}

int	close_game(t_storage *dat)
{
	cleanup(dat);
	exit(0);
}
