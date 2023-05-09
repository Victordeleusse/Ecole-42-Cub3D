/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:58:40 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 17:24:15 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	my_mlx_pixel_put(t_mini_img *data, int x, int y, int color)
{
	char	*dst;

	dprintf(2, "x : %d || y : %d\n", x, y);
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_mini_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

t_vector	ft_newvector(int x, int y)
{
	t_vector	position;

	position.x = x;
	position.y = y;
	return (position);
}

void	my_mlx_area_put(t_mini_img *d, t_vector p, t_vector dim, int c)
{
	int	x;
	int	y;

	y = -1;
	while (++y < dim.y)
	{
		x = -1;
		while (++x < dim.x)
			my_mlx_pixel_put(d, p.x + x, p.y + y, c);
	}
}

void	ft_clear_window(t_game *game)
{
	mlx_destroy_image(game->mlx, game->data.image);
	game->data.image = mlx_new_image(game->mlx, WIN_W, WIN_H);
	return ;
}

int	ft_key_action(int keycode, t_game *game)
{
	fprintf(stderr, "KEY -> %d\n", keycode);
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
	ft_key_action(key, game);
	ft_draw(game);
	return (0);
}

void	ft_draw(t_game *game)
{
	ft_clear_window(game);
	mlx_clear_window(game->mlx, game->window);
	cub_minimap(game);
	my_mlx_pixel_put(&(game->data), game->pos.x, game->pos.y, 0x00FF0000);
	mlx_put_image_to_window(game->mlx, game->window, game->data.image, 0, 0);
}

void	ft_mlx_pack(t_game *game)
{
	ft_draw(game);
	mlx_key_hook(game->window, &ft_get_transfo, game);
	mlx_loop(game->mlx);
}
