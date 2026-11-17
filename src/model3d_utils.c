/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model3d_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:59:36 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/17 15:03:41 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_address(t_coordinates ray, t_storage *data)
{
	if (ray.tex == NORTH)
		return (data->walls.north.txt_addr);
	if (ray.tex == SOUTH)
		return (data->walls.south.txt_addr);
	if (ray.tex == EAST)
		return (data->walls.east.txt_addr);
	if (ray.tex == WEST)
		return (data->walls.west.txt_addr);
	else
		return (NULL);
}

int	texture_size(t_coordinates ray, t_storage *data)
{
	if (ray.tex == NORTH)
	{
		if (data->walls.north.width > data->walls.north.height)
			return (data->walls.north.height);
		return (data->walls.north.width);
	}
	if (ray.tex == SOUTH)
	{
		if (data->walls.south.width > data->walls.south.height)
			return (data->walls.south.height);
		return (data->walls.south.width);
	}
	if (ray.tex == EAST)
	{
		if (data->walls.east.width > data->walls.east.height)
			return (data->walls.east.height);
		return (data->walls.east.width);
	}
	if (ray.tex == WEST)
	{
		if (data->walls.west.width > data->walls.west.height)
			return (data->walls.west.height);
		return (data->walls.west.width);
	}
	return (0);
}

double	pos_on_texture(t_coordinates ray)
{
	if (ray.tex == NORTH)
		return (ray.map.x - floor(ray.map.x));
	if (ray.tex == SOUTH)
		return (1 - (ray.map.x - floor(ray.map.x)));
	if (ray.tex == EAST)
		return (1 - (ray.map.y - floor(ray.map.y)));
	if (ray.tex == WEST)
		return (ray.map.y - floor(ray.map.y));
	else
		return (0);
}

int	get_colour_from_tex(t_coordinates ray, t_storage *dat, int x_tex, int y_tex)
{
	if (ray.tex == NORTH)
		return (*(unsigned int *)(get_texture_address(ray, dat) + (y_tex
				* dat->walls.north.line_length + x_tex
				* (dat->img->bits_per_pixel / 8))));
	if (ray.tex == SOUTH)
		return (*(unsigned int *)(get_texture_address(ray, dat) + (y_tex
				* dat->walls.south.line_length + x_tex
				* (dat->img->bits_per_pixel / 8))));
	if (ray.tex == EAST)
		return (*(unsigned int *)(get_texture_address(ray, dat) + (y_tex
				* dat->walls.east.line_length + x_tex
				* (dat->img->bits_per_pixel / 8))));
	if (ray.tex == WEST)
		return (*(unsigned int *)(get_texture_address(ray, dat) + (y_tex
				* dat->walls.west.line_length + x_tex
				* (dat->img->bits_per_pixel / 8))));
	return (0);
}
