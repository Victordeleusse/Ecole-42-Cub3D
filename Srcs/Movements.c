/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:44:18 by tchevrie          #+#    #+#             */
/*   Updated: 2023/05/18 16:44:40 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	move_forward(t_game *game)
{
	if (game->map->map[(int)(game->rayon->pos_x + game->rayon->dir_x \
	* game->rayon->movespeed)][(int)(game->rayon->pos_y)] == '0')
		game->rayon->pos_x += game->rayon->dir_x * game->rayon->movespeed;
	if (game->map->map[(int)(game->rayon->pos_x)] \
	[(int)(game->rayon->pos_y + game->rayon->dir_y \
	* game->rayon->movespeed)] == '0')
		game->rayon->pos_y += game->rayon->dir_y * game->rayon->movespeed;
}

void	move_backward(t_game *game)
{
	if (game->map->map[(int)(game->rayon->pos_x - game->rayon->dir_x \
	* game->rayon->movespeed)][(int)(game->rayon->pos_y)] == '0')
		game->rayon->pos_x -= game->rayon->dir_x * game->rayon->movespeed;
	if (game->map->map[(int)(game->rayon->pos_x)] \
	[(int)(game->rayon->pos_y - game->rayon->dir_y \
	* game->rayon->movespeed)] == '0')
		game->rayon->pos_y -= game->rayon->dir_y * game->rayon->movespeed;
}

void	move_right(t_game *game)
{
	if (game->map->map[(int)(game->rayon->pos_x + game->rayon->plane_x \
	* game->rayon->movespeed)][(int)(game->rayon->pos_y)] == '0')
		game->rayon->pos_x += game->rayon->plane_x \
		* game->rayon->movespeed;
	if (game->map->map[(int)(game->rayon->pos_x)] \
	[(int)(game->rayon->pos_y + game->rayon->plane_y \
	* game->rayon->movespeed)] == '0')
		game->rayon->pos_y += game->rayon->plane_y \
		* game->rayon->movespeed;
}

void	move_left(t_game *game)
{
	if (game->map->map[(int)(game->rayon->pos_x - game->rayon->plane_x \
	* game->rayon->movespeed)][(int)(game->rayon->pos_y)] == '0')
		game->rayon->pos_x -= game->rayon->plane_x \
		* game->rayon->movespeed;
	if (game->map->map[(int)(game->rayon->pos_x)] \
	[(int)(game->rayon->pos_y - game->rayon->plane_y \
	* game->rayon->movespeed)] == '0')
		game->rayon->pos_y -= game->rayon->plane_y \
		* game->rayon->movespeed;
}
