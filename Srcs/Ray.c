/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:04:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 12:36:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniMap.h"

void	init_ray(t_game *game)
{
	game->ray.angle = 0;
	if (game->pos.dir == 'S')
		game->ray.angle = 90;
	else if (game->pos.dir == 'W')
		game->ray.angle = 180;
	else if (game->pos.dir == 'N')
		game->ray.angle = 270;
	game->ray.hfov = 30;
	game->ray.incre_angle = 2 * game->ray.hfov / WIN_W;
	game->ray.precision = 50;
	game->ray.lim = 11;
	return ;
}

float	distance_to_wall(t_game *game, float ray_angle)
{
	float	d;

	game->ray.cos = cos(degree_to_radians(ray_angle)) / game->ray.precision;
	game->ray.sin = sin(degree_to_radians(ray_angle)) / game->ray.precision;
	game->x = game->pos.x + 0.5;
	game->y = game->pos.y + 0.5;
	while (!ft_strchr("1c", game->map[(int)game->y][(int)game->x]) && \
		sqrt(powf(game->x - game->pos.x - 0.5, 2.) + \
		powf(game->y - game->pos.y - 0.5, 2.)) < game->ray.lim)
	{
		game->x += game->ray.cos;
		game->y += game->ray.sin;
		if (ft_strchr("1c", game->map[(int)game->y][(int)game->x]))
			my_mlx_pixel_put(&game->data, game->x * SIZE, game->y * SIZE, 0x00FF0000);
		else if (ray_angle - 1 < game->ray.angle && ray_angle + 1 > game->ray.angle)
			my_mlx_pixel_put(&game->data, game->x * SIZE, game->y * SIZE, 0x0000FF00);
		else
			my_mlx_pixel_put(&game->data, game->x * SIZE, game->y * SIZE, 0x00BDC1C6);
	}
	my_mlx_area_put(&game->data, ft_newvector((int)(game->pos.x + 0.5) * SIZE, \
		(int)(game->pos.y + 0.5) * SIZE), ft_newvector(SIZE, SIZE), 0x00FDD663);
	d = sqrt(powf(game->x - game->pos.x - 0.5, 2.) + powf(game->y - game->pos.y - 0.5, 2.));
	return (d * cos(degree_to_radians(ray_angle - game->ray.angle)));
}
