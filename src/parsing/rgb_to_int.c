/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 15:20:21 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/18 17:26:53 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(t_storage *dat, t_colours *rgb, bool floor)
{
	if (floor)
	{
		if (dat->img->floor_c != -1)
			return (error("Description file: Floor is listed multiple times", false), 1);
		dat->img->floor_c = rgb->red + rgb->green * 256
			+ rgb->blue * 256 * 256;
	}
	else
	{
		if (dat->img->ceiling_c != -1)
			return (error("Description file: Ceiling is listed multiple times", false), 1);
		dat->img->ceiling_c = rgb->red + rgb->green * 256
			+ rgb->blue * 256 * 256;
	}
	return (0);
}