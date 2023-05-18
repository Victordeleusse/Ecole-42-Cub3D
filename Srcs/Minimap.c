/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:36:31 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 17:20:39 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	init_minimap(t_minimap *minimap, t_game *game)
{
	minimap->map = game->map;
	minimap->rayon = game->rayon;
	minimap->width = game->map->width;
	minimap->height = game->map->height;
}

void	my_mlx_pixel_put_minimap(t_minimap *minimap, int x, int y, int color)
{
	char	*dst;

	dst = minimap->addr + (y * minimap->line_length + x * (minimap->bpp / 8));
	*(unsigned int *)dst = color;
}

t_vector	generateNewVector(int pos_x, int pos_y)
{
	t_vector	vector;

	vector.x = pos_x;
	vector.y = pos_y;
	return (vector);
}

void	fillPlayer(t_minimap *minimap, t_vector position, t_vector standardDimension)
{
	int	x_move;
	int	y_move;
	int			zoom_h;
	int			zoom_w;

	y_move = 2;
	zoom_h = ((WIN_H / 3) / minimap->map->height) - 0.2;
	zoom_w = ((WIN_W / 3) / minimap->map->width) - 0.2;
	while (y_move < standardDimension.y - 2)
	{
		x_move = 2;
		while (x_move < standardDimension.x - 2)
		{	
			my_mlx_pixel_put_minimap(minimap,  zoom_w * position.x + x_move, zoom_h * position.y + y_move, 0x000088FF);
			x_move++;
		}
		y_move++;	
	}
}

void	fillLine(t_minimap *minimap, t_vector position, t_vector standardDimension)
{
	int	x_move;
	int	y_move;
	int	zoom_h;
	int	zoom_w;

	y_move = 0;
	x_move = 0;
	zoom_h = ((WIN_H / 3) / minimap->map->height) - 0.2;
	zoom_w = ((WIN_W / 3) / minimap->map->width) - 0.2;
	while (y_move < standardDimension.y && x_move < standardDimension.x)
	{
		my_mlx_pixel_put_minimap(minimap,  zoom_w * position.x + x_move, zoom_h * position.y + y_move, 0x00005555);
		x_move++;
		y_move++;	
	}
	x_move = 0;
	while (y_move > 0 && x_move < standardDimension.x)
	{
		my_mlx_pixel_put_minimap(minimap, zoom_w * position.x + x_move, zoom_h * position.y + y_move, 0x00005555);
		x_move++;
		y_move--;	
	}
}


void	fillArea(t_minimap *minimap, t_vector position, t_vector standardDimension)
{
	int	x_move;
	int	y_move;
	int	zoom_h;
	int	zoom_w;
	
	zoom_h = ((WIN_H / 3) / minimap->map->height) - 0.2;
	zoom_w = ((WIN_W / 3) / minimap->map->width) - 0.2;
	y_move = 0;
	while (y_move < standardDimension.y && minimap->map->map[position.y])
	{
		x_move = 0;
		while (x_move < standardDimension.x && minimap->map->map[position.y][position.x])
		{	
			if (minimap->map->map[position.y][position.x] != '1')
				my_mlx_pixel_put_minimap(minimap,  zoom_w * position.x + x_move, zoom_h * position.y + y_move, 0x000000);
			x_move++;
		}
		y_move++;	
	}
}

void	fillAreaAgain(t_minimap *minimap, t_vector position, t_vector standardDimension)
{
	int	x_move;
	int	y_move;
	int	zoom_h;
	int	zoom_w;
	
	zoom_h = ((WIN_H / 3) / minimap->map->height) - 0.2;
	zoom_w = ((WIN_W / 3) / minimap->map->width) - 0.2;
	y_move = 0;
	while (y_move < standardDimension.y && minimap->map->map[position.y])
	{
		x_move = 0;
		while (x_move < standardDimension.x \
		&& minimap->map->map[position.y][position.x])
		{	
			if (minimap->map->map[position.y][position.x] == '1')
				my_mlx_pixel_put_minimap(minimap,  zoom_w * position.x + x_move, zoom_h * position.y + y_move, 0xFF0000);
			x_move++;
		}
		y_move++;	
	}
}

void	fillMinimap(t_game *game)
{
	int			i;
	int			j;
	t_vector	position;
	t_vector	standard;
	int			zoom_h;
	int			zoom_w;
	
	zoom_h = ((WIN_H / 3) / game->map->height) - 0.2;
	zoom_w = ((WIN_W / 3) / game->map->width) - 0.2;
	standard = generateNewVector(zoom_w, zoom_h);
	j = 0;
	while (j < game->minimap->height)
	{
		i = 0;
		while (game->map->map[j][i])
		{
			position = generateNewVector(i, j);
			fillArea(game->minimap, position, standard);
			i++;
		}
		j++;
	}
}

void	fillMinimapAgain(t_game *game)
{
	int			i;
	int			j;
	t_vector	position;
	t_vector	standard;
	int			zoom_h;
	int			zoom_w;
	
	zoom_h = ((WIN_H / 3) / game->map->height) - 0.2;
	zoom_w = ((WIN_W / 3) / game->map->width) - 0.2;
	standard = generateNewVector(zoom_w, zoom_h);
	j = 0;
	while (j < game->minimap->height)
	{
		i = 0;
		while (game->map->map[j][i])
		{
			position = generateNewVector(i, j);
			fillAreaAgain(game->minimap, position, standard);
			i++;
		}
		j++;
	}
}
