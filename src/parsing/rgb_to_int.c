/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 15:20:21 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/25 08:19:25 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(t_storage *dat, t_colours *rgb, bool floor)
{
	if (floor)
	{
		if (dat->floor_c != -1)
			return (error("Description file: Floor is listed multiple times", false), 1);
		dat->floor_c = rgb->red + rgb->green * 256
			+ rgb->blue * 256 * 256;
	}
	else
	{
		if (dat->ceiling_c != -1)
			return (error("Description file: Ceiling is listed multiple times", false), 1);
		dat->ceiling_c = rgb->red + rgb->green * 256
			+ rgb->blue * 256 * 256;
	}
	return (0);
}
