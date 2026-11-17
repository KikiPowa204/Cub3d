/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:34:42 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/17 15:02:45 by knajmech         ###   ########.fr       */
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

void	scale(t_coordinates ray, t_storage *data, double hos, double vh)
{
	int		x_tex;
	int		y_tex;
	int		screen_y_start;
	int		wall_top;
	double	step;

	x_tex = (int)(texture_size(ray, data) * pos_on_texture(ray));
	wall_top = WINDOW_HEIGHT / 2.0 - vh / 2.0;
	ray.pix.y = (int)((double)WINDOW_HEIGHT / 2 - vh / 2);
	ray.pix.x = WINDOW_WIDTH - ray.pos;
	step = texture_size(ray, data) / vh;
	if (vh > hos)
		ray.pix.y += (int)((vh - hos) / 2);
	screen_y_start = ray.pix.y;
	while (ray.pix.y < screen_y_start + hos)
	{
		y_tex = (int)(ray.pix.y - wall_top) *step;
		put_pixel_3d(data->img, ray.pix.x, ray.pix.y,
			get_colour_from_tex(ray, data, x_tex, y_tex));
		ray.pix.y++;
	}
}

void	model3d(t_coordinates ray, t_storage *data)
{
	double			height_on_screen;
	double			virtual_height;

	ray.norm_length = remove_distortion(ray.length, data->player);
	virtual_height = WINDOW_WIDTH / ray.norm_length;
	if (virtual_height > WINDOW_HEIGHT)
		height_on_screen = WINDOW_HEIGHT;
	else
		height_on_screen = virtual_height;
	scale(ray, data, height_on_screen, virtual_height);
}
