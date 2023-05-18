/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:36:31 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 20:02:13 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	fill_area(t_minimap *minimap, t_vector position, t_vector sd)
{
	int	x_move;
	int	y_move;
	int	zoom_h;
	int	zoom_w;

	zoom_h = ((WIN_H / 3.1) / minimap->map->height) - 0.2;
	zoom_w = ((WIN_W / 3.1) / minimap->map->width) - 0.2;
	y_move = 0;
	while (y_move < sd.y && minimap->map->map[position.y])
	{
		x_move = 0;
		while (x_move < sd.x && minimap->map->map[position.y][position.x])
		{	
			if (minimap->map->map[position.y][position.x] != '1')
				my_mlx_pixel_put_minimap(minimap, zoom_w * position.x \
				+ x_move, zoom_h * position.y + y_move, 0x000000);
			x_move++;
		}
		y_move++;
	}
}

void	fill_area_again(t_minimap *minimap, t_vector position, t_vector sd)
{
	int	x_move;
	int	y_move;
	int	zoom_h;
	int	zoom_w;

	zoom_h = ((WIN_H / 3.1) / minimap->map->height) - 0.2;
	zoom_w = ((WIN_W / 3.1) / minimap->map->width) - 0.2;
	y_move = 0;
	while (y_move < sd.y && minimap->map->map[position.y])
	{
		x_move = 0;
		while (x_move < sd.x \
		&& minimap->map->map[position.y][position.x])
		{	
			if (minimap->map->map[position.y][position.x] == '1')
				my_mlx_pixel_put_minimap(minimap, zoom_w * position.x \
				+ x_move, zoom_h * position.y + y_move, 0xFF0000);
			x_move++;
		}
		y_move++;
	}
}

void	fill_minimap(t_game *game)
{
	int			i;
	int			j;
	t_vector	position;
	t_vector	standard;

	standard = generate_new_vector(((WIN_W / 3.1) / game->map->width) - 0.2, \
	((WIN_H / 3.1) / game->map->height) - 0.2);
	j = 0;
	while (j < game->minimap->height)
	{
		i = 0;
		while (game->map->map[j][i])
		{
			position = generate_new_vector(i, j);
			fill_area(game->minimap, position, standard);
			i++;
		}
		j++;
	}
}

void	fill_minimap_again_v2(t_game *game, t_vector standard, \
		int zoom_w, int zoom_h)
{
	int	i;
	int	j;
	int	x_move;
	int	y_move;

	j = game->minimap->height;
	while (j * zoom_h < WIN_H - (WIN_H / 1.5))
	{	
		i = -1;
		while (++i < game->minimap->width)
		{
			y_move = -1;
			while (++y_move < standard.y)
			{	
				x_move = -1;
				while (++x_move < standard.x)
					my_mlx_pixel_put_minimap(game->minimap, zoom_w * i \
					+ x_move, zoom_h * j + y_move, 0xFF000000);
			}
		}
		j++;
	}	
}

void	fill_minimap_again(t_game *game)
{
	int			i;
	int			j;
	t_vector	position;
	t_vector	standard;

	standard = generate_new_vector(((WIN_W / 3.1) / game->map->width) \
	- 0.2, ((WIN_H / 3.1) / game->map->height) - 0.2);
	j = 0;
	while (j < game->minimap->height)
	{
		i = 0;
		while (game->map->map[j][i])
		{
			position = generate_new_vector(i, j);
			fill_area_again(game->minimap, position, standard);
			i++;
		}
		j++;
	}
	fill_minimap_again_v2(game, standard, ((WIN_W / 3.1) / game->map->width) \
	- 0.2, ((WIN_H / 3.1) / game->map->height) - 0.2);
}
