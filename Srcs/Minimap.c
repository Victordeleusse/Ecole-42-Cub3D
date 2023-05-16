/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:36:31 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/16 20:28:41 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	init_minimap(t_minimap *minimap, t_game *game)
{
	minimap->map = game->map;
	minimap->rayon = game->rayon;
	minimap->width = game->map->width;
	minimap->height = game->map->height;
	minimap->image = mlx_new_image(game->mlx, WIN_W / 2, WIN_H / 2);
	minimap->addr = mlx_get_data_addr(minimap->image, &minimap->bpp, &minimap->line_length,
								&minimap->endian);
}

static void	my_mlx_pixel_put_minimap(t_minimap *minimap, int x, int y, int color)
{
	char	*dst;

	dst = minimap->addr + (y * minimap->line_length + x * (minimap->bpp / 8));
	*(unsigned int *)dst = color;
}

static t_vector	generateNewVector(int pos_x, int pos_y)
{
	t_vector	vector;

	vector.x = pos_x;
	vector.y = pos_y;
	return (vector);
}

static void	fillArea(t_minimap *minimap, t_vector position, t_vector standardDimension)
{
	int	x_move;
	int	y_move;
	int	color;

	color = 0xFF000000;
	if (minimap->map->map[position.y][position.x] == '1')
		color = 0x00FF0000;
	y_move = 0;
	while (y_move < standardDimension.y)
	{
		x_move = 0;
		while (x_move < standardDimension.x)
		{	
			my_mlx_pixel_put_minimap(minimap, SIZE * position.x + x_move, SIZE * position.y + y_move, color);
			x_move++;
		}
		y_move++;	
	}
}

void	fillMinimap(t_minimap *minimap)
{
	int			i;
	int			j;
	t_vector	position;
	t_vector	standard;
	
	j = 0;
	while (j < minimap->height)
	{
		i = 0;
		while (i < minimap->width)
		{
			position = generateNewVector(i, j);
			standard = generateNewVector(SIZE, SIZE);
			fillArea(minimap, position, standard);
			i++;
		}
		j++;
	}
}

// void	ft_drawMinimap(t_game *game)
// {
// 	// raycasting(game, game->rayon, game->map);
// 	fillMinimap(game->minimap);
// 	mlx_put_image_to_window(game->mlx, game->window, game->minimap->image, 0, 0);
// }
