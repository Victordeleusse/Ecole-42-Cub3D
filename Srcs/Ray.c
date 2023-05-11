/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:04:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/11 19:44:26 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

float	degree_to_radians(float degree)
{
	return (degree * M_PI / 180);
}

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
	game->ray.lim = 30;
	return ;
}

void	move_player(int keycode, t_game *g, float ray_cos, float ray_sin)
{
	float	angle;

	angle = g->ray.angle;
	if (keycode == KEY_S)
		angle = g->ray.angle - 180;
	else if (keycode == KEY_A)
		angle = g->ray.angle - 90;	
	else if (keycode == KEY_D)
		angle = g->ray.angle + 90;
	ray_cos = cos(degree_to_radians(angle)) * g->pos.speed;
	ray_sin = sin(degree_to_radians(angle)) * g->pos.speed;
	if (!ft_strchr("1", g->map[(int)(g->pos.y + 0.5 + \
			(3 * ray_sin))][(int)(g->pos.x + 0.5)]))
		g->pos.y += ray_sin;
	if (!ft_strchr("1", \
		g->map[(int)(g->pos.y + 0.5)][(int)(g->pos.x + 0.5 + (3 * ray_cos))]))
		g->pos.x += ray_cos;
}

float	distance_to_wall(t_game *game, float ray_angle)
{
	float	d;

	game->ray.cos = cos(degree_to_radians(ray_angle)) / game->ray.precision;
	game->ray.sin = sin(degree_to_radians(ray_angle)) / game->ray.precision;
	game->x = game->pos.x + 0.5;
	game->y = game->pos.y + 0.5;
	while (!ft_strchr("1", game->map[(int)game->y][(int)game->x]) && \
		sqrt(powf(game->x - game->pos.x - 0.5, 2.) + \
		powf(game->y - game->pos.y - 0.5, 2.)) < game->ray.lim)
	{
		game->x += game->ray.cos;
		game->y += game->ray.sin;
		if (ft_strchr("1", game->map[(int)game->y][(int)game->x]))
			my_mlx_pixel_put(&game->data, game->x * SIZE_D, game->y * SIZE_D, 0x00FF0000);
		else if (((ray_angle - 1) < game->ray.angle) && ((ray_angle + 1) > game->ray.angle))
			my_mlx_pixel_put(&game->data, game->x * SIZE_D, game->y * SIZE_D, 0x0000FFFF);
		else
			my_mlx_pixel_put(&game->data, game->x * SIZE_D, game->y * SIZE_D, 0x00BDC1C6);
	}
	my_mlx_area_put(&game->data, ft_newvector((int)(game->pos.x + 0.5) * SIZE_D, \
		(int)(game->pos.y + 0.5) * SIZE_D), ft_newvector(SIZE_D, SIZE_D), 0x00FDD663);
	d = sqrt(powf(game->x - game->pos.x - 0.5, 2.) + powf(game->y - game->pos.y - 0.5, 2.));
	return (d * cos(degree_to_radians(ray_angle - game->ray.angle)));
}

void	cub_raycast(t_game *g)
{
	float	ray_angle;
	int		ray_count;
	float	dist;

	ray_angle = g->ray.angle - g->ray.hfov;
	dprintf(2, "ray_angle : %f\n", ray_angle);
	ray_count = -1;
	while (++ray_count < WIN_W)
	{
		dist = distance_to_wall(g, ray_angle);
		ray_angle += g->ray.incre_angle;
	}
}

