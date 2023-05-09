/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniMap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:35:29 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 10:59:48 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOM_H
# define GEOM_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# include "libft.h"

# include "mlx.h"
# include "mlx_int.h"

typedef struct	s_player
{
	double	x;
	double	y;
	char	dir;
}t_player;


typedef struct s_ray
{
	float	incre_angle;
	float	angle;
	float	cos;
	float	sin;
	float	hfov;
	float	lim;
	int		precision;
}				t_ray;


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

