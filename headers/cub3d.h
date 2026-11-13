/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:30:03 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/13 13:18:58 by bastalze         ###   ########.fr       */
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
# include <assert.h>
# include <stdio.h> //perror
# include <sys/stat.h> //open
# include <fcntl.h> //open


# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define PI 3.141592653589793
# define HALF_PI PI/2
# define THREE_HALF_PI 3*PI/2
# define TILE_SIZE 30
# define PLAYER_SIZE 8
# define WALL 1
# define FLOOR 0
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define DESTROY_NOTIFY 17
# define SPEED 0.05
//# define FPS 60

//Parsing

typedef enum	e_compass
{
	NO,
	SO,
	WE,
	EA
}	t_compass;

//Execution

typedef enum	e_voh
{
	none,
	hor,
	ver,
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

// typedef struct	s_coordinates
// {
// 	int		x;
// 	int		y;
// 	int		z;
// 	size_t	colour;
// }			t_coordinates;

typedef	enum e_dir
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
	int			tex_size;
}	t_coordinates;

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
	double		dir;
	t_coordinates	orient;
}	t_player;

typedef	struct s_constants
{
	void		*img_mini;
	void		*img_3d;
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	*player;
	char		*addr_mini;
	char		*addr_3d;
	int			bits_per_pixel;
	int			bits_per_pixel_tex;
	int			line_length_3d;
	int			line_length_mini;
	int			line_length_tex;
	int			endian;
	int			floor_c;
	int			ceiling_c;
	int			max_w;
	int			max_h;
}	t_constants;

typedef struct s_texture
{
	void	*txt_ptr;
	//int	line_length;
	int		width;
	int		height;
	//int	size;
} t_texture;

typedef struct s_walls
{
	struct s_texture	north;
	struct s_texture	south;
	struct s_texture	east;
	struct s_texture	west;
} t_walls;

typedef	struct s_storage
{
	t_player	*player;
	t_constants	*img;
	char		*map;
	t_walls		walls;
} t_storage;


//t_voh	ray_collision(t_storage *dat, t_voh voh, int x, int y);
//bool	ray_collision(int x, int y, double a, t_storage *dat);

//Parsing:
int				parse_description_file(char *path, t_storage *dat, char **texture_paths);
//Rayyy casting:
bool			collide_horizontal(t_coordinates *rh, t_player *player, t_storage *dat, t_dir dir);
bool			collide_vertical(t_coordinates *rh, t_player *player, t_storage *dat, t_dir dir);
void			ray_casting(t_player *player, t_storage *data, int pos);
bool			check_if_wall(int x, int y, int max_d, char *map);
double			distance(double x1, double y1, double x2, double y2);
int				map_to_screen(double coordinate);
int				get_map_index(int rx, int ry, int max_d);
t_coordinates	bres_transform(double x, double y);
//void	ray_casting_horizontal(t_player *player, t_storage *data);
//void	ray_casting_vertical(t_player *player, t_storage *data);
bool			is_wall(double x, double y, t_storage *d);
void			model3d(t_coordinates ray, t_storage *data);
void		cone_casting(t_storage *dat);
void		bresenham_algo(t_coordinates p1, t_coordinates p2, t_storage *img);
void		recalc_player_pos(t_storage *dat, t_player *player);
int			stop_player(int keycode, t_storage *dat);
int			move_player(int keycode, t_storage *dat);
void		setup_hooks(t_storage *dat);
void		fill_map(t_storage *dat);
int			frame_per_second(t_storage *dat);
void		fill_tile(int x, int y, int colour, t_constants *img);
void		put_pixel_mini(t_constants *img, int x, int y, int color);
void		put_pixel_3d(t_constants *img, int x, int y, int color);
//Error and cleanup funcs
void		error(const char *msg, bool perr);
#endif
