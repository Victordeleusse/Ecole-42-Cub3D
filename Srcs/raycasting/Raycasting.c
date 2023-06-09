/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:42:37 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 20:13:50 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"
#include <math.h>

void	dda_calcul(t_game *game);
void	draw_text(t_game *game, int texdir, int x, int y);

static void	raycasting_one(t_game *game, t_ray *ray)
{
	t_vector	position;
	t_vector	standard;

	standard = generate_new_vector(WIN_H / 100, WIN_W / 100);
	ray->rdx = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->rdy = ray->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	position = generate_new_vector(game->rayon->map_y, game->rayon->map_x);
	fill_player(game->minimap, position, standard);
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = fabs(1 / ray->rdx);
	ray->delta_dist_y = fabs(1 / ray->rdy);
	ray->perp_wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
}

static void	raycasting_two(t_ray *ray)
{
	if (ray->rdx < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->rdy < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

static void	raycasting_last(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->rdx;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->rdy;
	ray->line_height = (int)(ray->h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + ray->h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + ray->h / 2;
	if (ray->draw_end >= ray->h)
		ray->draw_end = ray->h - 1;
}

static void	draw_line(t_game *game, t_ray *ray, int x)
{
	int	ground;
	int	sky;

	ground = ray->draw_start - 1;
	sky = ray->draw_end;
	ray->draw_start = ray->draw_start - 1;
	while (++ray->draw_start < ray->draw_end)
	{
		if (ray->draw_start < ray->h && x < ray->w)
			draw_text(game, game->texdir, x, ray->draw_start);
	}
	while (ground > 1)
	{
		my_mlx_pixel_put(game, x, ground, game->sky_color);
		ground--;
	}
	while (sky <= ray->h)
	{
		my_mlx_pixel_put(game, x, sky, game->ground_color);
		sky++;
	}
}

void	raycasting(t_game *game, t_ray *ray, t_map2D *map2d)
{
	int	x;

	(void)map2d;
	x = 0;
	while (x < ray->w)
	{
		ray->camera_x = 2.0 * x / (double)ray->w - 1.0;
		raycasting_one(game, ray);
		raycasting_two(ray);
		dda_calcul(game);
		raycasting_last(ray);
		if (map2d->map[ray->map_x][ray->map_y] == '1')
			ray->color = RGB_RED;
		else if (map2d->map[ray->map_x][ray->map_y] == '2')
			ray->color = RGB_BLUE;
		else
			ray->color = 0xFFF00FFF;
		if (ray->draw_start < ray->draw_end)
		{
			choose_tex_ray(game);
			draw_line(game, ray, x);
			ray->draw_start++;
		}
		x++;
	}
}
