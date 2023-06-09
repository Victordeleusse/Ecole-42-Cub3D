/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:45:26 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 20:18:59 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>

# define GREEN "\033[32m"
# define RED "\033[0;31m"
# define BLUEBG "\033[37;44m"
# define ENDCL "\033[0m"

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# ifndef WIN_H
#  define WIN_H 1000
# endif

# ifndef WIN_W
#  define WIN_W 1000
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

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

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
	double					old_plane_x;
}	t_ray;

typedef struct s_map2D
{
	char	**map;
	int		width;
	int		height;
	int		fd;
}	t_map2D;

typedef struct s_minimap
{
	void			*image;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	t_map2D			*map;
	t_ray			*rayon;
}	t_minimap;

typedef struct s_text
{
	void			*image;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	double			wallx;
	int				tex_x;
	int				tex_y;
	double			step;
	double			texpos;
}	t_text;

typedef struct s_game
{
	void			*mlx;
	void			*window;
	void			*image;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				ground_color;
	int				sky_color;
	int				texdir;
	t_ray			*rayon;
	t_map2D			*map;
	char			*buffer_map;
	t_minimap		*minimap;
	t_text			*north;
	t_text			*south;
	t_text			*west;
	t_text			*east;
}	t_game;

////////////////// Init.c //////////////////

int			get_player_position(char **map, t_ray *player);
void		get_map_data(t_game *game);

////////////////// Minimap.c //////////////////

void		init_minimap(t_minimap *minimap, t_game *game);
t_vector	generate_new_vector(int pos_x, int pos_y);
void		my_mlx_pixel_put_minimap(t_minimap *minimap, \
			int x, int y, int color);
void		fill_player(t_minimap *minimap, t_vector position, \
			t_vector standardDimension);
void		fill_area(t_minimap *minimap, t_vector position, \
			t_vector standardDimension);
void		fill_line(t_minimap *minimap, t_vector position, \
			t_vector standardDimension);
void		fill_area_again(t_minimap *minimap, t_vector position, \
			t_vector standardDimension);
void		fill_minimap(t_game *game);
void		fill_minimap_again(t_game *game);

////////////////// Parsing.c //////////////////

char		*strip_l(char *line);
int			parse_texture(t_game *game, char *line, t_text *elem, int case_n);
int			parsing(t_game *game, char *file);
void		parsing_error(char *text);
int			parse_color(char *line, int *elem, int case_n);

int			is_dir(char c);
int			parse_data(t_game *game, int fd);

int			is_map_and_player_check(t_map2D *map2D);

int			getColors(t_game *game, char *file);
int			create_trgb(int t, int r, int g, int b);

////////////////// Textures.c //////////////////

void		draw_text(t_game *game, int texdir, int x, int y);
void		choose_tex_ray(t_game *game);

////////////////// MyMiniLibx.c //////////////////

void		init_game(t_game *game);
void		my_mlx_pixel_put(t_game *game, int x, int y, int color);
void		ft_clear_window(t_game *game);
int			ft_get_transfo(int key, t_game *game);
void		ft_mlx_pack(t_game *game);

////////////////// Raycasting.c //////////////////

void		raycasting(t_game *game, t_ray *ray, t_map2D *map2D);

////////////////// Action.c //////////////////

int			ft_key_action(int keycode, t_game *game);
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		move_right(t_game *game);
void		move_left(t_game *game);

////////////////// Free.c //////////////////

int			free_and_quit(t_game *game);

#endif