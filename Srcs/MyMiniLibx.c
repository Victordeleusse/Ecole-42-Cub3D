/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:10:32 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/13 20:01:52 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
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

void	ft_clear_window(t_game *game)
{
	mlx_destroy_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, WIN_W, WIN_H);
	return ;
}

int	ft_get_transfo(int key, t_ray *ray, t_map2D *map2D, t_game *game)
{	
	ft_key_action(key, ray, map2D);
	ft_draw(ray, map2D, game);
	return (0);
}

void	ft_draw(t_ray *ray, t_map2D *map2D, t_game *game)
{
	ft_clear_window(game);
	mlx_clear_window(game->mlx, game->window);
	raycasting(game, ray, map2D);
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
}

void	ft_mlx_pack(t_ray *ray, t_map2D *map2D, t_game *game)
{
	ft_draw(ray, map2D, game);
	mlx_hook(game->window, 2, 1L << 0, &ft_get_transfo, game);
	dprintf(2, "After putting \n");
	mlx_loop(game->mlx);
}
