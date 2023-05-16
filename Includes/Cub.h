/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:45:26 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/16 14:22:24 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# ifndef WIN_H
#  define WIN_H 720
# endif

# ifndef WIN_W
#  define WIN_W 720
# endif

# ifndef SIZE
#  define SIZE 1
# endif

// KEYS_CODE //

# define KEY_ESC	65307
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_A		97
# define KEY_D		100
# define KEY_W		119
# define KEY_S		115

// WALL_COLORS // 

# ifndef RGB_RED
#  define RGB_RED 0xFFFF0000
# endif

# ifndef RGB_BLUE
#  define RGB_BLUE 0xFF00FF00
# endif

// STRUCTURES //

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_ray
{
	int						color;
	double					pos_x;
	double					pos_y;
	char					dir;
	double					dir_x;
	double					dir_y;
	double					plane_x;
	double					plane_y;
	int						w;
	int						h;
	double					camera_x;
	double					rdx;
	double					rdy;
	int						map_x;
	int						map_y;
	double					side_dist_x;
	double					side_dist_y;
	double					delta_dist_x;
	double					delta_dist_y;
	double					perp_wall_dist;
	int						step_x;
	int						step_y;
	int						hit;
	int						side;
	int						line_height;
	int						draw_start;
	int						draw_end;
	double					movespeed;
	double					rotspeed;
	double					old_dir_x;
	double 					old_plane_x;
}	t_ray;

typedef struct s_map2D
{
	char	**map;
	int		width;
	int		height;
	int 	fd;
}	t_map2D;

typedef struct s_game
{
	void			*mlx;
	void			*window;
	void			*image;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	unsigned long	ground_color;
	unsigned long	sky_color;
	t_ray			*rayon;
	t_map2D			*map;
} t_game;

////////////////// Init.c //////////////////

void	init_map_2D(t_map2D *map2D);
int		get_player_position(char **map, t_ray *player);
void	get_player_direction(t_ray *ray);

////////////////// Parsing.c //////////////////

int	isDir(char c);
int	fillTheTab(char *file, t_map2D *map2D);

int	isMapAndPlayerCheck(t_map2D *map2D);

unsigned long	getColors(t_game *game, char *file);

////////////////// MyMiniLibx.c //////////////////

void	init_game(t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	ft_clear_window(t_game *game);
int		ft_get_transfo(int key, t_game *game);
void	ft_draw(t_game *game);
void	ft_mlx_pack(t_game *game);

////////////////// Raycasting.c //////////////////

void	ray_init(t_ray *ray);
void	raycasting(t_game *game, t_ray *ray, t_map2D *map2D);

////////////////// Action.c //////////////////

int		ft_key_action(int keycode, t_game *game);

////////////////// Free.c //////////////////

void	free_all(t_map2D *map2D, t_ray *ray, t_game *game);


#endif