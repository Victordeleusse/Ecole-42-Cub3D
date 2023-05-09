/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:35:29 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 18:25:45 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# ifndef WIN_H
#  define WIN_H 480
# endif

# ifndef WIN_W
#  define WIN_W 640
# endif

# ifndef SIZE
#  define SIZE 18
# endif

typedef struct	s_player
{
	double	x;
	double	y;
	char	dir;
	float	speed;
} t_player;

typedef struct	s_vector
{
	int	x;
	int	y;
} t_vector;

typedef struct	s_ray
{
	float	incre_angle;
	float	angle;
	float	cos;
	float	sin;
	float	hfov;
	float	lim;
	int		precision;
} t_ray;

typedef struct	s_game
{
	char		**map;
	void		*mlx;
	void		*window;
	int			height;
	int			width;
	t_mini_img	data;
	t_mini_img	miniview;
	t_ray		ray;
	t_player	pos;
	float		x;
	float		y;
} t_game;




// typedef struct	s_point
// {	
// 	t_vector	*pos_player;
// 	t_vector	*dir_view;
// 	t_vector	*cam_plan;
// }t_point;
	
// typedef struct	s_map_2D
// {
// 	char	**map;
// 	int		width;
// 	int		height;
// }t_map_2D;

// typedef struct	s_cub
// {
// 	void		*mlx_ptr;
// 	void		*win_ptr;
// 	t_mini_img	minimap;
// 	t_mini_img	miniview;
// 	double		posx;
// 	double		posy;
// }t_cub;

// t_map_2D	*ft_init_map2D(void);
// t_vector	*init_vector(double x_start, double y_start);
// t_point		*get_starting_param(void);

#endif

