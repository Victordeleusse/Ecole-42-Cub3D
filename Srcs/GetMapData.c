/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetMapData.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:11:40 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/19 14:03:50 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static void	get_data_ray(t_ray *ray)
{
	ray->w = WIN_W;
	ray->h = WIN_H;
	ray->movespeed = 0.1;
	ray->rotspeed = 0.1;
}

static void	get_map_width_and_height(t_map2D *map_container)
{
	int		width;
	int		height;
	char	**map;

	map = map_container->map;
	height = 0;
	width = 0;
	if (map && map[0])
	{
		while (map[height])
		{
			if ((int)ft_strlen(map[height]) > width)
				width = (int)ft_strlen(map[height]);
			height++;
		}
	}
	map_container->width = width;
	map_container->height = height;
}

static void	get_player_direction(t_ray *ray)
{
	ray->dir_y = 0;
	ray->dir_x = 0;
	ray->plane_x = 0;
	ray->plane_y = 0;
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
}

int	get_player_position(char **map, t_ray *player)
{
	player->pos_x = 0;
	while (map[(int)player->pos_x])
	{
		player->pos_y = 0;
		while (map[(int)player->pos_x][(int)player->pos_y])
		{
			if (map[(int)player->pos_x][(int)player->pos_y] == 'N' \
			|| map[(int)player->pos_x][(int)player->pos_y] == 'S' \
			|| map[(int)player->pos_x][(int)player->pos_y] == 'E' \
			|| map[(int)player->pos_x][(int)player->pos_y] == 'W')
			{	
				player->dir = map[(int)player->pos_x][(int)player->pos_y];
				player->old_plane_x = 0;
				get_player_direction(player);
				map[(int)player->pos_x][(int)player->pos_y] = '0';
				player->pos_x += 0.5;
				player->pos_y += 0.5;
				return (1);
			}
			player->pos_y++;
		}
		player->pos_x++;
	}
	return (0);
}

void	get_map_data(t_game *game)
{
	get_map_width_and_height(game->map);
	get_data_ray(game->rayon);
	init_minimap(game->minimap, game);
}
