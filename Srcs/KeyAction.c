/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyAction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:12:11 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 17:36:18 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static void	rotate_right(t_game *game)
{
	game->rayon->old_dir_x = game->rayon->dir_x;
	game->rayon->dir_x = game->rayon->dir_x \
	* cos(-game->rayon->rotspeed) - game->rayon->dir_y \
	* sin(-game->rayon->rotspeed);
	game->rayon->dir_y = game->rayon->old_dir_x \
	* sin(-game->rayon->rotspeed) + game->rayon->dir_y \
	* cos(-game->rayon->rotspeed);
	game->rayon->old_plane_x = game->rayon->plane_x;
	game->rayon->plane_x = game->rayon->plane_x \
	* cos(-game->rayon->rotspeed) - game->rayon->plane_y \
	* sin(-game->rayon->rotspeed);
	game->rayon->plane_y = game->rayon->old_plane_x \
	* sin(-game->rayon->rotspeed) + game->rayon->plane_y \
	* cos(-game->rayon->rotspeed);
}

static void	rotate_left(t_game *game)
{
	game->rayon->old_dir_x = game->rayon->dir_x;
	game->rayon->dir_x = game->rayon->dir_x \
	* cos(game->rayon->rotspeed) - game->rayon->dir_y \
	* sin(game->rayon->rotspeed);
	game->rayon->dir_y = game->rayon->old_dir_x \
	* sin(game->rayon->rotspeed) + game->rayon->dir_y \
	* cos(game->rayon->rotspeed);
	game->rayon->old_plane_x = game->rayon->plane_x;
	game->rayon->plane_x = game->rayon->plane_x \
	* cos(game->rayon->rotspeed) - game->rayon->plane_y \
	* sin(game->rayon->rotspeed);
	game->rayon->plane_y = game->rayon->old_plane_x \
	* sin(game->rayon->rotspeed) + game->rayon->plane_y \
	* cos(game->rayon->rotspeed);
}

int	ft_key_action(int keycode, t_game *game)
{
	if (keycode == KEY_S)
		move_backward(game);
	if (keycode == KEY_W)
		move_forward(game);
	if (keycode == KEY_D)
		move_right(game);
	if (keycode == KEY_A)
		move_left(game);
	if (keycode == KEY_RIGHT)
		rotate_right(game);
	if (keycode == KEY_LEFT)
		rotate_left(game);
	if (keycode == KEY_ESC)
		free_and_quit(game);
	return (0);
}
