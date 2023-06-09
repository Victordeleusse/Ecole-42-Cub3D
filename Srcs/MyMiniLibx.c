/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:10:32 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 19:51:47 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	ft_draw(t_game *game)
{
	fill_minimap(game);
	raycasting(game, game->rayon, game->map);
	fill_minimap_again(game);
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, game->minimap->image, \
	0, 0);
}

int	ft_get_transfo(int key, t_game *game)
{	
	ft_key_action(key, game);
	ft_draw(game);
	return (0);
}

void	ft_mlx_pack(t_game *game)
{
	ft_draw(game);
	mlx_hook(game->window, 17, 0, &free_and_quit, game);
	mlx_hook(game->window, 2, 1L << 0, &ft_get_transfo, game);
	mlx_loop(game->mlx);
}
