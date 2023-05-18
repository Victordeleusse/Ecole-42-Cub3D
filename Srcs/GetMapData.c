/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetMapData.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:11:40 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 14:07:14 by tchevrie         ###   ########.fr       */
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
	int	width;
	int	i;

	if (!map[0])
		return (0);
	width = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > width)
			width = (int)ft_strlen(map[i]);
		i++;
	}
	return (width);
}

static void	get_data_map_2D(t_map2D *map2D)
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
				map[(int)player->pos_x][(int)player->pos_y] = '0';
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
	get_data_map_2D(game->map);
	get_data_ray(game->rayon);
	init_minimap(game->minimap, game);
}