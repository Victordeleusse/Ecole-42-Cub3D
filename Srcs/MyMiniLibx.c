/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:58:40 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 18:57:15 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

t_vector	ft_newvector(int x, int y)
{
	t_vector	position;

	position.x = x;
	position.y = y;
	return (position);
}

void	my_mlx_pixel_put(t_mini_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_mini_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
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
	cub_miniview(game);
	redraw_elem(game, game->miniview, WIN_W - game->miniview.width - 20, \
			WIN_H - game->miniview.height - 20);
	my_mlx_pixel_put(&(game->data), game->pos.x, game->pos.y, 0x00FF0000);
	mlx_put_image_to_window(game->mlx, game->window, game->data.image, 0, 0);
}

void	ft_mlx_pack(t_game *game)
{
	ft_draw(game);
	mlx_key_hook(game->window, &ft_get_transfo, game);
	mlx_loop(game->mlx);
}

void	my_mlx_img_to_img(int p[2], t_mini_img img[2], int c1)
{
	int	xy[2];
	int	color;

	xy[1] = -1;
	while (++xy[1] < img[0].height)
	{
		xy[0] = -1;
		while (++xy[0] < img[0].width)
		{
			if (xy[0] + p[0] >= 0 && xy[1] + p[1] >= 0)
			{
				color = my_mlx_pixel_get(&img[0], xy[0], xy[1]);
				if (color != c1)
					my_mlx_pixel_put(&img[1], xy[0] + p[0], \
						xy[1] + p[1], color);
			}
		}
	}
}

