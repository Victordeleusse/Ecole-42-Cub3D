/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:10:32 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/17 18:46:47 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	init_game(t_game *game)
{
	game->window = mlx_new_window(game->mlx, WIN_W, WIN_H, "map");
	game->image = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->addr = mlx_get_data_addr(game->image, &game->bpp, &game->line_length,
								&game->endian);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_length + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	ft_draw(t_game *game)
{
	fillMinimap(game);
	raycasting(game, game->rayon, game->map);
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, game->minimap->image, 0, 0);
}

int	ft_get_transfo(int key, t_game *game)
{	
	ft_key_action(key, game);
	dprintf(2, "change detected\n");
	ft_draw(game);
	return (0);
}

void	ft_mlx_pack(t_game *game)
{
	ft_draw(game);
	mlx_hook(game->window, 17, 0, &end_it, game);
	mlx_hook(game->window, 2, 1L << 0, &ft_get_transfo, game);
	mlx_loop(game->mlx);
}
