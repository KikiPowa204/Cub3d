/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 10:45:44 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/16 10:52:10 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	frame_per_second(t_storage *dat)
{
	struct timeval	tv;
	time_t			milliseconds;
	time_t			limit;

	gettimeofday(&tv, NULL);
	milliseconds = (tv.tv_usec / 1000 + tv.tv_sec * 1000);
	limit = milliseconds + 16;
	while ((tv.tv_usec / 1000 + tv.tv_sec * 1000) < limit)
	{
		usleep(200);
		gettimeofday(&tv, NULL);
	}
	fill_map(dat);
	return (0);
}

void	put_pixel_3d(t_constants *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr_3d +
		(y * img->line_length_3d + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_pixel_mini(t_constants *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr_mini +
		(y * img->line_length_mini + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
