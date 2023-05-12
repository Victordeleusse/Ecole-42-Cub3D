/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:42:37 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/12 23:36:18 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	ray_init(t_ray *ray)
{
	ray->w = WIN_W;
	ray->h = WIN_H;
	ray->movespeed = 0.1;
	ray->rotspeed = 0.1;
}

static void	dda_calcul(t_ray *ray, t_map2D *map2D)
{
	while (ray->hit == 0)
	{
		dprintf(2, "AVANCEMENT 3 -> side_dist_x : %f || side_dist_y : %f\n", ray->side_dist_x, ray->side_dist_y);	
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			dprintf(2, "map_x : %d -> ", ray->map_x);
			ray->map_x += ray->step_x;
			dprintf(2, "map_x : %d\n", ray->map_x);
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		// dprintf(2, "map_x : %d map_y : %d \n", ray->map_x, ray->map_y);
		// dprintf(2, "map position : %c \n", map2D->map[(int)ray->map_x][(int)ray->map_y]);
		dprintf(2, "map position : %c \n", map2D->map[5][5]);
		if (map2D->map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
}

static void	get_wall_color(t_ray *ray, t_map2D *map2D)
{
	if (map2D->map[ray->map_x][ray->map_y] == '1')
		ray->color = RGB_BLUE;
	else if (map2D->map[ray->map_x][ray->map_y] == '2')
		ray->color = RGB_RED;
	else 
		ray->color = 0xFF000000;
	if (ray->side == 1)
			ray->color = ray->color / 2;
}

static void	ft_verline(t_game *game, int x, int draw_start, int draw_end, int color)
{
	if (draw_start < draw_end)
	{
		my_mlx_pixel_put(game, x, draw_start, color);
		draw_start++;
	}
}


void	raycasting(t_game *game, t_ray *ray, t_map2D *map2D)
{
	int	x;

	x = 0;
	dprintf(2, "TEST : %d\n", ray->w);
	while (x < ray->w)
	{
		ray->camera_x = 2.0 * x / (double)ray->w - 1.0;
		ray->rdx = ray->dir_x + ray->plane_x * ray->camera_x;
		ray->rdy = ray->dir_y + ray->plane_y * ray->camera_x;
		dprintf(2, "AVANCEMENT 1 -> rdx : %f || rdy : %f\n", ray->rdx, ray->rdy);	
		ray->map_x = (int)ray->pos_x;
		ray->pos_x += 0.5;
		ray->map_y = (int)ray->pos_y;
		ray->pos_y += 0.5;
		ray->side_dist_x = 0;
		ray->side_dist_y = 0;
		ray->delta_dist_x = fabs(1 / ray->rdx);
		ray->delta_dist_y = fabs(1 / ray->rdy);
		dprintf(2, "AVANCEMENT 2 -> delta_dist_x : %f || delta_dist_y : %f\n", ray->delta_dist_x, ray->delta_dist_y);	
		ray->perp_wall_dist = 0;
		ray->step_x = 0;
		ray->step_y = 0;
		ray->hit = 0;
		ray->side = 0;
		// ray->movespeed = 5;
		// ray->rotspeed = 3;
		if (ray->rdx < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (double)(ray->pos_x - ray->map_x) * ray->delta_dist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = (double)(ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
		}
		if (ray->rdy < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = (double)(ray->pos_y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (double)(ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
		}
		// dprintf(2, "AVANCEMENT 3 -> side_dist_x : %f || side_dist_y : %f\n", ray->side_dist_x, ray->side_dist_y);	
		dda_calcul(ray, map2D);
		dprintf(2, "AVANCEMENT POST DDA\n");	
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
		get_wall_color(ray, map2D);
		ft_verline(game, x, ray->draw_start, ray->draw_end, ray->color);
		x++;
	}
}


