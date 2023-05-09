/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:55:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 10:59:09 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYMINILIBX_H
# define MYMINILIBX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# include "libft.h"

# include "mlx.h"
# include "mlx_int.h"
# include "MiniMap.h"
# include "Keys.h"

typedef struct s_mini_img
{
	void	*mlx;
	void	*image;
	void	*window;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	t_player	*pos;
}t_mini_img;


void			my_mlx_pixel_put(t_mini_img *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_mini_img *data, int x, int y);

int				ft_key_action(int keycode, t_player *pos);
void			ft_mlx_pack(t_mini_img *data);
void			ft_draw(t_mini_img *data);
int				ft_get_transfo(int key, t_mini_img *data);

#endif