/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:35:29 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/11 19:13:02 by vde-leus         ###   ########.fr       */
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

# ifndef SIZE_D
#  define SIZE_D 1
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
	t_ray		ray;
	t_player	pos;
	float		x;
	float		y;
} t_game;

#endif

