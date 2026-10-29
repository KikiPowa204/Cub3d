/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:30:03 by knajmech          #+#    #+#             */
/*   Updated: 2026/10/29 14:45:43 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# include <unistd.h>
# include <sys/time.h>
# include "libft.h"
# include <X11/keysym.h>

# define PI 3.141592653589793
# define HALF_PI PI/2
# define THREE_HALF_PI 3*PI/2
# define TILE_SIZE 90
# define PLAYER_SIZE 8
# define WALL 1
# define FLOOR 0
# define KEY_PRESS 2
# define KEY_RELEASE 3
//# define FPS 60

typedef enum	e_voh
{
	none,
	ver,
	hor,
	both
}				t_voh;

typedef struct	s_algo
{
	int	dx;
	int	dy;
	int	d_p;
	int	dirx;
	int	diry;
}				t_algo;

typedef struct	s_coordinates
{
	int		x;
	int		y;
	int		z;
	size_t	colour;
}			t_coordinates;
/*
typedef struct s_coordinates
{
	union	u_cotype
	{
		typedef struct	s_pix
		{
			int		x;
			int		y;
			int		z;
		}				t_pix;
		typedef struct	s_map
		{
			double	x;
			double	y;
			double	z;
		}				t_map;
	}
	double	length;
	size_t	colour;
}			t_coordinates;
*/
typedef	enum e_direction
{
	UP,
	LEFT,
	RIGHT,
	DOWN,
	VERT,
	HORI
} t_dir;
extern char map[]; 

typedef	struct s_player
{
	double		x;
	double		y;
	bool		left;
	bool		right;
	bool		down;
	bool		up;
	bool		turn_left;
	bool		turn_right;
	double		z;
	double		a;
	t_coordinates	p1;
	t_coordinates	p2;
}	t_player;


typedef	struct s_constants
{
	void		*img;
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	*player;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			max_w;
	int			max_h;
}	t_constants;

typedef	struct s_storage
{
	t_player	*player;
	t_constants	*img;
	char		*map;
} t_storage;

t_voh	ray_collision(t_storage *dat, t_voh voh, int x, int y);
//bool	ray_collision(int x, int y, double a, t_storage *dat);
bool	check_if_wall(int x, int y, int max_d, char *map);
int		map_to_screen(double coordinate);
int		get_map_index(int rx, int ry, int max_d);
void	ray_casting_horizontal(t_player *player, t_storage *data);
void	ray_casting_vertical(t_player *player, t_storage *data);
void	bresenham_algo(t_coordinates p1, t_coordinates p2, t_storage *img);
void	recalc_player_pos(t_storage *dat, t_player *player);
int		stop_player(int keycode, t_storage *dat);
int		move_player(int keycode, t_storage *dat);
void	setup_hooks(t_storage *dat);
int		fill_map(t_storage *dat);
void	fill_tile(int x, int y, int colour, t_constants *img);
void	put_pixel(t_constants *img, int x, int y, int color);

#endif
