/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:36:31 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 20:02:03 by tchevrie         ###   ########.fr       */
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

	if (x < 0 || x >= WIN_W / 3.1 || y < 0 || y >= WIN_H / 3.1)
		return ;
	dst = minimap->addr + (y * minimap->line_length + x * (minimap->bpp / 8));
	*(unsigned int *)dst = color;
}

t_vector	generate_new_vector(int pos_x, int pos_y)
{
	t_vector	vector;

	vector.x = pos_x;
	vector.y = pos_y;
	return (vector);
}

void	fill_player(t_minimap *minimap, t_vector position, t_vector sd)
{
	int	x_move;
	int	y_move;
	int	zoom_h;
	int	zoom_w;

	y_move = 2;
	zoom_h = ((WIN_H / 3.1) / minimap->map->height) - 0.2;
	zoom_w = ((WIN_W / 3.1) / minimap->map->width) - 0.2;
	while (y_move < sd.y - 2)
	{
		x_move = 2;
		while (x_move < sd.x - 2)
		{	
			my_mlx_pixel_put_minimap(minimap, zoom_w * position.x \
			+ x_move, zoom_h * position.y + y_move, 0x000088FF);
			x_move++;
		}
		y_move++;
	}
}

void	fill_line(t_minimap *minimap, t_vector position, t_vector sd)
{
	int	x_move;
	int	y_move;
	int	zoom_h;
	int	zoom_w;

	y_move = 0;
	x_move = 0;
	zoom_h = ((WIN_H / 3.1) / minimap->map->height) - 0.2;
	zoom_w = ((WIN_W / 3.1) / minimap->map->width) - 0.2;
	while (y_move < sd.y && x_move < sd.x)
	{
		my_mlx_pixel_put_minimap(minimap, zoom_w * position.x \
		+ x_move, zoom_h * position.y + y_move, 0x00005555);
		x_move++;
		y_move++;
	}
	x_move = 0;
	while (y_move > 0 && x_move < sd.x)
	{
		my_mlx_pixel_put_minimap(minimap, zoom_w * position.x \
		+ x_move, zoom_h * position.y + y_move, 0x00005555);
		x_move++;
		y_move--;
	}
}
