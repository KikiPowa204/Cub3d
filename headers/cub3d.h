/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:30:03 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/23 12:58:42 by knajmech         ###   ########.fr       */
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

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define PI 3.141592653589793
# define HALF_PI 1.5707963268
# define THREE_HALF_PI 4.7123889804
# define TILE_SIZE 30
# define PLAYER_SIZE 8
# define WALL 1
# define FLOOR 0
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define DESTROY_NOTIFY 17
# define SPEED 0.05
# define MINI_VIEW 10

typedef struct s_algo
{
	int	dx;
	int	dy;
	int	d_p;
	int	dirx;
	int	diry;
}				t_algo;

typedef enum e_dir
{
	UP,
	LEFT,
	RIGHT,
	DOWN,
	VERT,
	HORI,
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_dir;

typedef struct s_pix
{
	int		x;
	int		y;
	int		z;
}				t_pix;

typedef struct s_map
{
	double	x;
	double	y;
	double	z;
}				t_map;

typedef struct s_coordinates
{
	union
	{
		t_pix	pix;
		t_map	map;
	};
	double		length;
	double_t	norm_length;
	size_t		colour;
	int			pos;
	enum e_dir	tex;
}	t_coordinates;

extern char map[];

typedef struct s_player
{
	double			x;
	double			y;
	bool			left;
	bool			right;
	bool			down;
	bool			up;
	bool			turn_left;
	bool			turn_right;
	double			z;
	double			a;
	double			dir;
	t_coordinates	orient;
}	t_player;

typedef struct s_constants
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_constants;

typedef struct s_texture
{
	void			*txt_ptr;
	char			*txt_addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}				t_texture;

typedef struct s_walls
{
	struct s_texture	north;
	struct s_texture	south;
	struct s_texture	east;
	struct s_texture	west;
}				t_walls;

typedef struct s_minimap
{
	double	x_start;
	double	y_start;
	double	curr_x;
	double	curr_y;
	int		mini_h;
	int		mini_w;
}	t_minimap;

typedef struct s_storage
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		*player;
	t_constants		*img_mini;
	t_constants		*img_3d;
	char			*map;
	t_walls			walls;
	int				max_w;
	int				max_h;
	t_minimap		mini;
}				t_storage;

//Rayyy casting:
bool			collide_horizontal(t_coordinates *rh, t_player *player,
					t_storage *dat, t_dir dir);
bool			collide_vertical(t_coordinates *rh, t_player *player,
					t_storage *dat, t_dir dir);
void			ray_casting(t_player *player, t_storage *data, int pos);
bool			check_if_wall(int x, int y, int max_d, char *map);
double			distance(double x1, double y1, double x2, double y2);
int				map_to_screen(double coordinate);
int				get_map_index(int rx, int ry, int max_d);
t_coordinates	bres_transform(double x, double y);
bool			is_wall(double x, double y, t_storage *d);
void			model3d(t_coordinates ray, t_storage *data);
void			cone_casting(t_storage *dat);
void			bresenham_algo(t_coordinates p1, t_coordinates p2,
					t_storage *img);
void			recalc_player_pos(t_storage *dat, t_player *player);
int				stop_player(int keycode, t_storage *dat);
int				move_player(int keycode, t_storage *dat);
void			setup_hooks(t_storage *dat);
void			fill_map(t_storage *dat);
int				frame_per_second(t_storage *dat);
//void			fill_tile(double x, double y, int colour, t_constants *img);
void			put_pixel_mini(t_storage *data, int x, int y, int color);
void			put_pixel_3d(t_storage *data, int x, int y, int color);
char			*get_texture_address(t_coordinates ray, t_storage *data);
void			cleanup(t_storage *data);
int				close_game(t_storage *data);
char			*get_texture_address(t_coordinates ray, t_storage *data);
int				texture_size(t_coordinates ray, t_storage *data);
double			pos_on_texture(t_coordinates ray);
int				get_colour_from_tex(t_coordinates ray, t_storage *dat,
					int x_tex, int y_tex);
void			grab_player_coordinates(t_storage *dat);
void			alter_values(double vector, double *map_coordi,
					int dir, double *count);
void			top_right(t_player *player, t_storage *data,
					t_coordinates ray_h, t_coordinates ray_v);
void			top_left(t_player *player, t_storage *data,
					t_coordinates ray_h, t_coordinates ray_v);
void			bottom_right(t_player *player, t_storage *data,
					t_coordinates ray_h, t_coordinates ray_v);
void			bottom_left(t_player *player, t_storage *data,
					t_coordinates ray_h, t_coordinates ray_v);
void			mini_map_window(t_storage *dat, int *x, int *y);
void			minimap(t_storage *dat);
void			draw_player(double x, double y, t_constants *img_mini);

#endif
