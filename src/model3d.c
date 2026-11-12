/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:34:42 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/12 14:45:01 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <mlx.h>

double	remove_distortion(double length, t_player *player)
{
	double	alpha;
	
	if (player->a < player->dir)
		alpha = player->dir - player->a;
	else
		alpha = player->a - player->dir;
	if (alpha >= 2 * PI)
		alpha -= 2 * PI;
	if (alpha < 0)
		alpha += 2 * PI;
	return (length * cos(alpha));
}

char	*get_texture_adress(t_coordinates ray, t_storage *data)
{
	if (ray.tex == NORTH)
		return (mlx_get_data_addr(data->walls.north.txt_ptr, &data->img->bits_per_pixel_tex,
			&data->img->line_length_tex, &data->img->endian));
	if (ray.tex == SOUTH)
		return (mlx_get_data_addr(data->walls.south.txt_ptr, &data->img->bits_per_pixel_tex,
			&data->img->line_length_tex, &data->img->endian));
	if (ray.tex == EAST)
		return (mlx_get_data_addr(data->walls.east.txt_ptr, &data->img->bits_per_pixel_tex,
			&data->img->line_length_tex, &data->img->endian));
	if (ray.tex == WEST)
		return (mlx_get_data_addr(data->walls.west.txt_ptr, &data->img->bits_per_pixel_tex,
			&data->img->line_length_tex, &data->img->endian));
	else
	 	return (NULL);
}

int	texture_size(t_coordinates ray, t_storage *data)
{
	if (ray.tex == NORTH)
	{
		if (data->walls.north.width > data->walls.north.height)
			return (data->walls.north.height);
		else
		 	return (data->walls.north.width);
	}
	if (ray.tex == SOUTH)
	{
		if (data->walls.south.width > data->walls.south.height)
			return (data->walls.south.height);
		else
		 	return (data->walls.south.width);
	}
	if (ray.tex == EAST)
	{
		if (data->walls.east.width > data->walls.east.height)
			return (data->walls.east.height);
		else
		 	return (data->walls.east.width);
	}
	if (ray.tex == WEST)
	{
		if (data->walls.west.width > data->walls.west.height)
			return (data->walls.west.height);
		else
		 	return (data->walls.west.width);
	}
	else
		return (0);
}

double	pos_on_texture(t_coordinates ray)
{
	if (ray.tex == NORTH)
		return (ray.map.x - floor(ray.map.x));
	if (ray.tex == SOUTH)
		return (1- (ray.map.x - floor(ray.map.x)));
	if (ray.tex == EAST)
		return (1- (ray.map.y - floor(ray.map.y)));
	if (ray.tex == WEST)
		return (ray.map.y - floor(ray.map.y));
	else
		return (0);
}

void	scale(t_coordinates ray, t_storage *data, double hos, double vh, t_coordinates screen)
{
	char	*tex_adress;
	//char	*tex_curr_adress;
	int		x_tex;
	int		y_tex;
	int		screen_y_start;
	int		tex_size;
	int		wall_top;
	double	step;
	int		colour;
	int		y_wall;
	
	tex_size = texture_size(ray, data);
	x_tex = (int)(tex_size * pos_on_texture(ray));
	tex_adress = get_texture_adress(ray, data);
	wall_top = WINDOW_HEIGHT / 2.0 - vh / 2.0;
	step = tex_size / vh;
	screen.pix.y = (int)(((double)WINDOW_HEIGHT / 2) - (vh / 2));
	if (vh > hos)
		screen.pix.y += (int)((vh - hos) / 2);
	screen_y_start = screen.pix.y;
	while(screen.pix.y < screen_y_start + hos)
	{
		y_wall = (int)(screen.pix.y - wall_top);
		y_tex = y_wall * step;
		//y_tex = (int)(screen.pix.y * (vh / tex_size) + 0.5);
		colour = *(unsigned int *)(tex_adress + (y_tex * data->img->line_length_tex + x_tex * (data->img->bits_per_pixel_tex / 8)));
		put_pixel_3d(data->img, screen.pix.x, screen.pix.y, colour);
		screen.pix.y++;
	}
}

// line length is measured in bytes that*s why we use char * for the adress on the image.
// And the we cast to int to make it read 32bits

void	model3d(t_coordinates ray, t_storage *data)
{
	double			height_on_screen;
	double			virtual_height;
	t_coordinates	screen;

	ray.norm_length = remove_distortion(ray.length, data->player);
	virtual_height = WINDOW_WIDTH / ray.norm_length;
	if (virtual_height > WINDOW_HEIGHT)
		height_on_screen = WINDOW_HEIGHT;
	else
	 	height_on_screen = virtual_height;
	screen.pix.y = (int)((double)WINDOW_HEIGHT / 2 - height_on_screen / 2);
	screen.pix.x = WINDOW_WIDTH - ray.pos;
	//if (ray.tex == NORTH)
		scale(ray, data, height_on_screen, virtual_height, screen);
	// else
	// {
	// 	while (screen.pix.y < (int)(((double)WINDOW_HEIGHT / 2 - height_on_screen / 2) + height_on_screen))
	// 	{
	// 		put_pixel_3d(data->img, screen.pix.x, screen.pix.y, 0x00FFFF);
	// 		screen.pix.y++;
	// 	}
	// }
}
