/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:55:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/08 20:35:38 by vde-leus         ###   ########.fr       */
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

typedef struct s_mini_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}t_mini_img;


void			my_mlx_pixel_put(t_mini_img *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_mini_img *data, int x, int y);
int				key_hook(int keycode);

#endif