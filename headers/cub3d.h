/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:30:03 by knajmech          #+#    #+#             */
/*   Updated: 2026/10/21 14:34:14 by knajmech         ###   ########.fr       */
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

# define TILE_SIZE 90
# define PLAYER_SIZE 8
# define WALL 1
# define FLOOR 0
# define KEY_PRESS 2
# define KEY_RELEASE 3
//# define FPS 60

typedef	enum e_direction
{
	UP,
	LEFT,
	RIGHT,
	DOWN
} t_dir;
extern char map[]; 

typedef	struct s_player
{
	double	pos;
	double	x;
	double	y;
	bool	left;
	bool	right;
	bool	down;
	bool	up;
	//float	dx;
	//float	dy;
	//float	z;
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

void	recalc_player_pos(t_storage *dat, t_player *player);
int		stop_player(int keycode, t_storage *dat);
int		move_player(int keycode, t_storage *dat);
void	setup_hooks(t_storage *dat);
int		fill_map(t_storage *dat);
void	fill_tile(int x, int y, int colour, t_constants *img);
void	put_pixel(t_constants *img, int x, int y, int color);

#endif
