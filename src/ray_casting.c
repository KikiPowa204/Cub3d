/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:41:12 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/03 09:26:24 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "stdio.h"

void	top_right(t_player *player, t_storage *data)
/*
void	ray_casting_horizontal(t_player *player, t_storage *data)
{
	t_coordinates	r1;
	t_coordinates	r2;
	double			atan;
	int				dir;
	int				dof;

	atan = 1/tan(player->a);
	printf("tan a: %lf\n", tan(player->a));
	if (tan(player->a) < 0.001 && tan(player->a) > -0.001)
		return;
	r1.x = map_to_screen(player->x);
	r1.y = map_to_screen(player->y);
	r2.x = map_to_screen(player->x);
	r2.y = map_to_screen(player->y);
	dir = 0;
	dof = 0;
	if (player->a < PI)
	{
		dir = -1;
		r2.y = (int)player->y * TILE_SIZE;
		r2.x = ((r1.y - r2.y) * atan + player->x * TILE_SIZE);
		puts("one");
	}
	else if (player->a > PI)
	{
		dir = 1;
		r2.y = map_to_screen((int)player->y + 1);
		r2.x = ((r1.y - r2.y) * atan + player->x * TILE_SIZE);
	}
	if (player->a == 0 || player->a == PI)
		return ;
	while (dir && map[get_map_index(r2.x, r2.y, data->img->max_w)] != WALL)
	{		
		r2.y = r2.y + dir;
		r2.x = ((r1.y - r2.y) * atan + r1.x);
		if (r2.x < 0 || r2.y < 0 || r2.x >= data->img->max_w * TILE_SIZE || r2.y >= data->img->max_h * TILE_SIZE)
			return ;
		printf("r1.y: %d, r1.x: %d, r2.y: %d, r2.x: %d\n", r1.y, r1.x, r2.y, r2.x);

	}
	r1.colour = 0xD11515;
	bresenham_algo(r1, r2, data);
	// ugly way of making line thicker
	r1.x++;
	r2.x++;
	bresenham_algo(r1, r2, data);
	r1.x++;
	r2.x++;
	bresenham_algo(r1, r2, data);
}*/

t_map	ray_casting_horizontal(t_storage *data, double rx, double ry)
{
	t_map	start_pos;
	t_map	end_pos;

	start_pos.x = data->player->x;
	start_pos.y = data->player->y;
	if (data->player->a < PI)
	{
		
	}
}

/*
void	ray_casting_vertical(t_player *p, t_storage *data)
>>>>>>> 84b93a2 (just a backup for safety)
{
	double			cot;
	double			tan_a;
	t_coordinates	rh;
	t_coordinates	rv;
	bool			hor;
	bool			vert;
	
	hor = false;
	cot = 0;
	if (player->a > 0.01)
	{
		cot = 1/tan(player->a);
		rh.map.y = (int)player->y;
		rh.map.x = ((player->y - rh.map.y) * cot + player->x);
		hor = true;
		rh.length = distance(player->x, player->y, rh.map.x, rh.map.y);
	}
	else
		ft_bzero(&rh, sizeof(t_coordinates));
	tan_a = tan(player->a);
	rv.map.x = (int)player->x + 1;
	rv.map.y = ((player->x - rv.map.x) * tan_a + player->y);
	rv.length = distance(player->x, player->y, rv.map.x, rv.map.y);
	
	if (rh.length < rv.length && rh.length != 0)
		return (bresenham_algo(bres_transform(player->x, player->y),
			bres_transform(rh.map.x, rh.map.y), data));
	else
		return (bresenham_algo(bres_transform(player->x, player->y),
			bres_transform(rv.map.x, rv.map.y), data));
}

void	ray_casting(t_player *player, t_storage *data)
{
	if (player->a >= 0 && player->a < HALF_PI)
		top_right(player, data);
}
