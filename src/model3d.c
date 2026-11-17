/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:34:42 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/17 14:15:12 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int		get_colour_from_tex(t_coordinates ray, t_storage *data, int x_tex, int y_tex)
{
	if (ray.tex == NORTH)
		return (*(unsigned int *)(get_texture_address(ray, data) + (y_tex * data->walls.north.line_length + x_tex * (data->img->bits_per_pixel / 8))));
	if (ray.tex == SOUTH)
		return (*(unsigned int *)(get_texture_address(ray, data) + (y_tex * data->walls.south.line_length + x_tex * (data->img->bits_per_pixel / 8))));
	if (ray.tex == EAST)
		return (*(unsigned int *)(get_texture_address(ray, data) + (y_tex * data->walls.east.line_length + x_tex * (data->img->bits_per_pixel / 8))));
	if (ray.tex == WEST)
		return (*(unsigned int *)(get_texture_address(ray, data) + (y_tex * data->walls.west.line_length + x_tex * (data->img->bits_per_pixel / 8))));
	return (0);
}
/*
void	scale(t_coordinates ray, t_storage *data, double hos, double vh, t_coordinates screen)
{
	char	*tex_adress;
	int		x_tex;
	int		y_tex;
	int		screen_y_start;
	int		wall_top;
	double	step;
	int		colour;
	int		y_wall;

	x_tex = (int)(texture_size(ray, data) * pos_on_texture(ray));
	tex_adress = get_texture_address(ray, data);
	wall_top = WINDOW_HEIGHT / 2.0 - vh / 2.0;
	step = texture_size(ray, data) / vh;
	screen.pix.y = (int)(((double)WINDOW_HEIGHT / 2) - (vh / 2));
	if (vh > hos)
		screen.pix.y += (int)((vh - hos) / 2);
	screen_y_start = screen.pix.y;
	while(screen.pix.y < screen_y_start + hos)
	{
		y_wall = (int)(screen.pix.y - wall_top);
		y_tex = y_wall * step;
		colour = *(unsigned int *)(tex_adress + (y_tex * data->img->line_length_tex + x_tex * (data->img->bits_per_pixel_tex / 8)));
		put_pixel_3d(data->img, screen.pix.x, screen.pix.y, colour);
		screen.pix.y++;
	}
}*/

void	scale(t_coordinates ray, t_storage *data, double hos, double vh)
{
	int		x_tex;
	int		y_tex;
	int		screen_y_start;
	int		wall_top;

	x_tex = (int)(texture_size(ray, data) * pos_on_texture(ray));
	wall_top = WINDOW_HEIGHT / 2.0 - vh / 2.0;
	ray.pix.y = (int)(((double)WINDOW_HEIGHT / 2) - (vh /2));
	ray.pix.x = WINDOW_WIDTH - ray.pos;
	if (vh > hos)
		ray.pix.y += (int)((vh - hos) / 2);
	screen_y_start = ray.pix.y;
	while(ray.pix.y < screen_y_start + hos)
	{
		y_tex = (int)(ray.pix.y - wall_top) * texture_size(ray, data) / vh;
		put_pixel_3d(data->img, ray.pix.x, ray.pix.y, get_colour_from_tex(ray, data, x_tex, y_tex));
		ray.pix.y++;
	}
}

// line length is measured in bytes that*s why we use char * for the adress on the image.
// And the we cast to int to make it read 32bits
/*
void	draw_texture(t_coordinates ray, t_storage *data, 

void	prep_texture(t_coordinates ray, t_storage *data, double hos, double vh)
{
	char	*tex_adress;
	int		x_tex;
	int		y_tex;
	int		screen_y_start;
	int		wall_top;
	double	step;
	int		colour;
	int		y_wall;

	x_tex = (int)(texture_size(ray, data) * pos_on_texture(ray));
	tex_adress = get_texture_adress(ray, data);
	wall_top = WINDOW_HEIGHT / 2.0 - vh / 2.0;
	step = texture_size(ray, data) / vh;
	screen.pix.y = (int)(((double)WINDOW_HEIGHT / 2) - (vh / 2));
	if (vh > hos)
		screen.pix.y += (int)((vh - hos) / 2);
	screen_y_start = screen.pix.y;

}*/

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
	screen.pix.x = WINDOW_WIDTH - ray.pos;
	screen.pix.y = (int)((double)WINDOW_HEIGHT / 2 - virtual_height / 2);
	scale(ray, data, height_on_screen, virtual_height);
}
