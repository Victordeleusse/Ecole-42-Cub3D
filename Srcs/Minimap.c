/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:36:31 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/17 18:48:54 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	init_minimap(t_minimap *minimap, t_game *game)
{
	minimap->map = game->map;
	minimap->rayon = game->rayon;
	minimap->width = game->map->width;
	minimap->height = game->map->height;
	minimap->image = mlx_new_image(game->mlx, WIN_W / 2, WIN_H / 3);
	minimap->addr = mlx_get_data_addr(minimap->image, &minimap->bpp, &minimap->line_length,
								&minimap->endian);
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

	y_move = 3;
	while (y_move < standardDimension.y - 3)
	{
		x_move = 3;
		while (x_move < standardDimension.x - 3)
		{	
			my_mlx_pixel_put_minimap(minimap, SIZE * position.x + x_move, SIZE * position.y + y_move, 0x000088FF);
			x_move++;
		}
		y_move++;	
	}
}

void	fillLine(t_minimap *minimap, t_vector position, t_vector standardDimension)
{
	int	x_move;
	int	y_move;

	y_move = 0;
	x_move = 0;
	while (y_move < standardDimension.y && x_move < standardDimension.x)
	{
		my_mlx_pixel_put_minimap(minimap, SIZE * position.x + x_move, SIZE * position.y + y_move, 0x00005555);
		x_move++;
		y_move++;	
	}
}

void	fillArea(t_minimap *minimap, t_vector position, t_vector standardDimension)
{
	int	x_move;
	int	y_move;
	int	color;
	
	color = 0xFF000000;
	if (!minimap->map->map[position.y][position.x])
		return ;
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

void	fillMinimap(t_game *game)
{
	int			i;
	int			j;
	// int			center_x = 0;;
	// int			center_y = 0;
	// int			delta_sup_x = 0;
	// int			delta_sup_y = 0;
	// int			delta_inf_x = 0;
	// int			delta_inf_y = 0;
	// int			diff_x = 0;
	// int			diff_y = 0;
	t_vector	position;
	t_vector	standard;
	
	// center_x = (int)game->rayon->pos_x;
	// if (center_x < 4)
	// 	diff_x = 4 - center_x;
	// center_y = (int)game->rayon->pos_y;
	// if (center_x < 4)
	// 	diff_x = 4 - center_x;
	// delta_sup_x = game->map->width - center_x;
	// if (delta_sup_x < 4)
	// 	diff_x = 4 - delta_sup_x;
	
		
	// center_y = (int)game->rayon->pos_y;
	standard = generateNewVector(SIZE, SIZE);
	j = 0;
	while (j < game->minimap->height)
	{
		i = 0;
		while (i < game->minimap->width)
		{
			position = generateNewVector(i, j);
			fillArea(game->minimap, position, standard);
			i++;
		}
		j++;
	}
}
