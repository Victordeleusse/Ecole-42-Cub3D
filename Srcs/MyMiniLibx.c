/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:58:40 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 12:34:57 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniMap.h"
#include "MyMiniLibx.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->data.addr + (y * game->data.line_length + x * (game->data.bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_game *game, int x, int y)
{
	char	*dst;

	dst = game->data.addr + (y * game->data.line_length + x * (game->data.bpp / 8));
	return (*(unsigned int *)dst);
}

void	ft_clear_window(t_game *game)
{
	mlx_destroy_image(game->mlx, game->data.image);
	game->data.image = mlx_new_image(game->mlx, 640, 480);
	return ;
}

int	ft_key_action(int keycode, t_game *game)
{
	fprintf(stderr, "KEY\n");
	if (keycode == KEY_LEFT)
		game->pos.x -= DEP;
	else if (keycode == KEY_RIGHT)
		game->pos.x += DEP;	
	if (keycode == KEY_UP)
		game->pos.y -= DEP;
	if (keycode == KEY_DOWN)
		game->pos.y += DEP;
	return (0);
}

int	ft_get_transfo(int key, t_game *game)
{	
	ft_clear_window(game);
	mlx_clear_window(game->mlx, game->window);
	ft_key_action(key, game);
	ft_mlx_pack(game);
	return (0);
}

void	ft_mlx_pack(t_game *game)
{
	my_mlx_pixel_put(game->data, game->pos.x, game->pos.y, 0x00FF0000);
	mlx_put_image_to_window(game->mlx, game->window, game->data.image, 0, 0);
	mlx_key_hook(game->window, &ft_get_transfo, game);
	mlx_loop(game->mlx);
}