/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 09:53:37 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/16 10:54:32 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup(t_storage *dat)
{
	free(dat->map);
	mlx_destroy_image(dat->img->mlx_ptr, dat->walls.north.txt_ptr);
	mlx_destroy_image(dat->img->mlx_ptr, dat->walls.south.txt_ptr);
	mlx_destroy_image(dat->img->mlx_ptr, dat->walls.west.txt_ptr);
	mlx_destroy_image(dat->img->mlx_ptr, dat->walls.east.txt_ptr);
	mlx_destroy_image(dat->img->mlx_ptr, dat->img->img_3d);
	mlx_destroy_image(dat->img->mlx_ptr, dat->img->img_mini);
	mlx_destroy_window(dat->img->mlx_ptr, dat->img->win_ptr);
	mlx_destroy_display(dat->img->mlx_ptr);
}

int	close_game(t_storage *dat)
{
	cleanup(dat);
		exit(0);
}

