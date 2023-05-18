/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:12:11 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 14:28:50 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"
	
int	ft_key_action(int keycode, t_game *game)
{
	//move backward 
	if (keycode == KEY_S)
	{
		if (game->map->map[(int)(game->rayon->pos_x - game->rayon->dir_x * game->rayon->movespeed)][(int)(game->rayon->pos_y)] == '0')
			game->rayon->pos_x -= game->rayon->dir_x * game->rayon->movespeed;
		if (game->map->map[(int)(game->rayon->pos_x)][(int)(game->rayon->pos_y - game->rayon->dir_y * game->rayon->movespeed)] == '0')
			game->rayon->pos_y -= game->rayon->dir_y * game->rayon->movespeed;
	}
	//move forward 
	if (keycode == KEY_W)
	{
		if (game->map->map[(int)(game->rayon->pos_x + game->rayon->dir_x * game->rayon->movespeed)][(int)(game->rayon->pos_y)] == '0')
			game->rayon->pos_x += game->rayon->dir_x * game->rayon->movespeed;
		if (game->map->map[(int)(game->rayon->pos_x)][(int)(game->rayon->pos_y + game->rayon->dir_y * game->rayon->movespeed)] == '0')
			game->rayon->pos_y += game->rayon->dir_y * game->rayon->movespeed;
	}
	//move to the right
	if (keycode == KEY_D)
	{
		if (game->map->map[(int)(game->rayon->pos_x + game->rayon->plane_x * game->rayon->movespeed)][(int)(game->rayon->pos_y)] == '0')
			game->rayon->pos_x += game->rayon->plane_x * game->rayon->movespeed;
		if (game->map->map[(int)(game->rayon->pos_x)][(int)(game->rayon->pos_y + game->rayon->plane_y * game->rayon->movespeed)] == '0')
			game->rayon->pos_y += game->rayon->plane_y * game->rayon->movespeed;
	}
	//move to the left
	if (keycode == KEY_A)
	{
		if (game->map->map[(int)(game->rayon->pos_x - game->rayon->plane_x * game->rayon->movespeed)][(int)(game->rayon->pos_y)] == '0')
			game->rayon->pos_x -= game->rayon->plane_x * game->rayon->movespeed;
		if (game->map->map[(int)(game->rayon->pos_x)][(int)(game->rayon->pos_y - game->rayon->plane_y * game->rayon->movespeed)] == '0')
			game->rayon->pos_y -= game->rayon->plane_y * game->rayon->movespeed;
	}
	//rotation to the right
	if (keycode == KEY_RIGHT)
	{
		// game->rayon->plane_x = 0;
		game->rayon->old_dir_x = game->rayon->dir_x;
		game->rayon->dir_x = game->rayon->dir_x * cos(-game->rayon->rotspeed) - game->rayon->dir_y * sin(-game->rayon->rotspeed);
		game->rayon->dir_y = game->rayon->old_dir_x * sin(-game->rayon->rotspeed) + game->rayon->dir_y * cos(-game->rayon->rotspeed);
		game->rayon->old_plane_x = game->rayon->plane_x;
		game->rayon->plane_x = game->rayon->plane_x * cos(-game->rayon->rotspeed) - game->rayon->plane_y * sin(-game->rayon->rotspeed);
		game->rayon->plane_y = game->rayon->old_plane_x * sin(-game->rayon->rotspeed) + game->rayon->plane_y * cos(-game->rayon->rotspeed);
	}
	//move to the left
	if (keycode == KEY_LEFT)
	{
		game->rayon->old_dir_x = game->rayon->dir_x;
		game->rayon->dir_x = game->rayon->dir_x * cos(game->rayon->rotspeed) - game->rayon->dir_y * sin(game->rayon->rotspeed);
		game->rayon->dir_y = game->rayon->old_dir_x * sin(game->rayon->rotspeed) + game->rayon->dir_y * cos(game->rayon->rotspeed);
		game->rayon->old_plane_x = game->rayon->plane_x;
		game->rayon->plane_x = game->rayon->plane_x * cos(game->rayon->rotspeed) - game->rayon->plane_y * sin(game->rayon->rotspeed);
		game->rayon->plane_y = game->rayon->old_plane_x * sin(game->rayon->rotspeed) + game->rayon->plane_y * cos(game->rayon->rotspeed);
	}
	if (keycode == KEY_ESC)
		free_and_quit(game);
	return (0);
}
	