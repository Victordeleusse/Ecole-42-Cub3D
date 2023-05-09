/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:45:26 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 18:58:02 by vde-leus         ###   ########.fr       */
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

# include "MyMiniLibx.h"
# include "Ray.h"
# include "Keys.h"

///////// MyMiniLib

void			my_mlx_pixel_put(t_mini_img *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_mini_img *data, int x, int y);
void			my_mlx_area_put(t_mini_img *d, t_vector p, t_vector dim, int c);
void			my_mlx_img_to_img(int p[2], t_mini_img img[2], int c1);
void			redraw_elem(t_game *g, t_mini_img img, int x, int y);

int				ft_key_action(int keycode, t_game *game);
void			ft_mlx_pack(t_game *game);
void			ft_draw(t_game *game);
int				ft_get_transfo(int key, t_game *game);

///////// Ray

void		init_ray(t_game *game);
t_vector	ft_newvector(int x, int y);
int			get_mini_color(t_game *g, int len, int xy[2]);
void		cub_minimap(t_game *g);
void		cub_miniview(t_game *g);
void		cub_raycast(t_game *g);
void		move_player(int keycode, t_game *g, float ray_cos, float ray_sin);

#endif