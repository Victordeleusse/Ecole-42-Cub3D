/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:42:37 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 13:44:43 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"
#include <math.h>

static void	raycasting_one(t_game *game,t_ray *ray);
static void	raycasting_two(t_ray *ray);
static void	dda_calcul(t_game *game);
static void	raycasting_last(t_ray *ray);
static void	choose_color(t_ray *ray, t_map2D *map2D);
static void	draw_line(t_game *game, t_ray *ray, int x);


static void	ft_verline(t_game *game, int x, t_ray *ray)
{
	if (ray->draw_start < ray->draw_end)
	{
		draw_line(game, ray, x);
		ray->draw_start++;
	}
}

void	raycasting(t_game *game, t_ray *ray, t_map2D *map2D)
{
	int	x;

	(void)map2D;
	x = 0;
	while (x < ray->w)
	{
		ray->camera_x = 2.0 * x / (double)ray->w - 1.0;
		raycasting_one(game, ray);
		raycasting_two(ray);
		dda_calcul(game);
		raycasting_last(ray);
		choose_color(ray, map2D);
		ft_verline(game, x, ray);
		x++;
	}
}

static void	raycasting_one(t_game *game, t_ray *ray)
{
	t_vector	position;
	t_vector	standard;
	
	standard = generateNewVector( WIN_H /100, WIN_W /100);
	ray->rdx = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->rdy = ray->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	position = generateNewVector(game->rayon->map_y, game->rayon->map_x);
	fillPlayer(game->minimap, position, standard);
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

static void	dda_calcul(t_game *game)
{
	t_vector	standard;
	t_vector	position;
	double		arrondi;
	
	standard = generateNewVector( WIN_H /100, WIN_W /100);
	while (game->rayon->hit == 0)
	{
		if (game->rayon->side_dist_x < game->rayon->side_dist_y)
		{
			game->rayon->side_dist_x += game->rayon->delta_dist_x;
			game->rayon->map_x += game->rayon->step_x;
			game->rayon->side = 0;
		}
		else
		{
			game->rayon->side_dist_y += game->rayon->delta_dist_y;
			game->rayon->map_y += game->rayon->step_y;
			game->rayon->side = 1;
		}
		if (game->map->map[game->rayon->map_x][game->rayon->map_y] == '1')
			game->rayon->hit = 1;		
		else
		{
			if (game->rayon->side == 0)
			{
				arrondi = round(game->rayon->dir_x * 100) / 100;
				if (arrondi > 0.80 || arrondi < -0.80)
				{
					position = generateNewVector(game->rayon->map_y, game->rayon->map_x);
					fillLine(game->minimap, position, standard);	
				}
			}
			else if (game->rayon->side == 1)
			{
				position = generateNewVector(game->rayon->map_y, game->rayon->map_x);
				fillLine(game->minimap, position, standard);
			}
		}
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

static void	choose_color(t_ray *ray, t_map2D *map2D)
{
	if (map2D->map[ray->map_x][ray->map_y] == '1')
		ray->color = RGB_RED;
	else if (map2D->map[ray->map_x][ray->map_y] == '2')
		ray->color = RGB_BLUE;
	else 
		ray->color = 0xFFF00FFF;
}

static void	draw_line(t_game *game, t_ray *ray, int x)
{
	int	ground = ray->draw_start - 1;
	int sky = ray->draw_end;

	ray->draw_start = ray->draw_start - 1;
	while (++ray->draw_start < ray->draw_end)
	{
		if (ray->draw_start < ray->h && x < ray->w)
			my_mlx_pixel_put(game, x, ray->draw_start, ray->color);
	}
	while (ground > 1)
	{	
		my_mlx_pixel_put(game, x, ground, 0xFFafebff);
		ground--;
	}
	while (sky <= ray->h)
	{
		my_mlx_pixel_put(game, x, sky, 0xFF006500);
		sky++;
	}
}

