/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:55:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 12:33:45 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYMINILIBX_H
# define MYMINILIBX_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include "Keys.h"
# include "MiniMap.h"

typedef struct s_mini_img
{
	void	*image;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
} t_mini_img;

void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_game *game, int x, int y);

int				ft_key_action(int keycode, t_game *game);
void			ft_mlx_pack(t_game *game);
void			ft_draw(t_game *game);
int				ft_get_transfo(int key, t_game *game);

#endif