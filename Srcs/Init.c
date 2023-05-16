/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:11:40 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/16 19:54:28 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static void	init_ray(t_ray *ray)
{
	ray->w = WIN_W;
	ray->h = WIN_H;
	ray->movespeed = 0.1;
	ray->rotspeed = 0.1;
}

static int	get_map_height(char **map)
{
	int	cur;

	cur = 0;
	while (map[cur])
		cur++;
	return (cur);
}

static int	get_map_width(char **map)
{
	if (map[0])
		return (ft_strlen(map[0]));
	return (0);
}

static void	init_map_2D(t_map2D *map2D)
{
	map2D->height = get_map_height(map2D->map);
	map2D->width = get_map_width(map2D->map);
}

static void	get_player_direction(t_ray *ray)
{
	ray->dir_y = 0;
	ray->dir_x = 0;
	ray->plane_x = 0;
	ray->plane_y = 0;
	ray->old_plane_x = 0;
	ray->old_dir_x = 0;
	if (ray->dir == 'N')
	{	
		ray->dir_x = -1;
		ray->plane_y = 0.66;
	}
	else if (ray->dir == 'S')
	{	
		ray->dir_x = 1;
		ray->plane_y = -0.66;
	}
	else if (ray->dir == 'E')
	{	
		ray->dir_y = 1;		
		ray->plane_x = 0.66;
	}
	else if (ray->dir == 'W')
	{	
		ray->dir_y = -1;
		ray->plane_x = -0.66;
	}
	return ;
}

int	get_player_position(char **map, t_ray *player)
{
	player->pos_x = 0;
	while (map[(int)player->pos_x])
	{
		player->pos_y = 0;
		while (map[(int)player->pos_x][(int)player->pos_y])
		{
			if (map[(int)player->pos_x][(int)player->pos_y] == 'N' || map[(int)player->pos_x][(int)player->pos_y] == 'S' ||
				map[(int)player->pos_x][(int)player->pos_y] == 'E' || map[(int)player->pos_x][(int)player->pos_y] == 'W')
			{	
				player->dir = map[(int)player->pos_x][(int)player->pos_y];
				get_player_direction(player);
				return (1);
			}
			player->pos_y++;
		}
		player->pos_x++;
	}
	return (0);
}

void	initAll(t_game *game, t_map2D *map2D, t_ray *ray, t_minimap *minimap)
{
	game->map = map2D;
	game->rayon = ray;
	game->minimap = minimap;
	init_game(game);
	init_map_2D(map2D);
	init_ray(ray);
	init_minimap(minimap, game);
}