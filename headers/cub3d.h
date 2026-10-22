/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:30:03 by knajmech          #+#    #+#             */
/*   Updated: 2026/10/22 15:00:33 by knajmech         ###   ########.fr       */
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
# define TWOPI PI/2
# define THREEPI 3*PI/2
# define TILE_SIZE 90
# define PLAYER_SIZE 8
# define WALL 1
# define FLOOR 0
# define KEY_PRESS 2
# define KEY_RELEASE 3
//# define FPS 60

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
}				t_coordinates;

typedef	enum e_direction
{
	UP,
	LEFT,
	RIGHT,
	DOWN,
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
	double		dx;
	double		dy;
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
} t_storage;

void	bresenham_algo(t_coordinates p1, t_coordinates p2, t_storage *img);
void	recalc_player_pos(t_storage *dat, t_player *player);
int		stop_player(int keycode, t_storage *dat);
int		move_player(int keycode, t_storage *dat);
void	setup_hooks(t_storage *dat);
int		fill_map(t_storage *dat);
void	fill_tile(int x, int y, int colour, t_constants *img);
void	put_pixel(t_constants *img, int x, int y, int color);

#endif
