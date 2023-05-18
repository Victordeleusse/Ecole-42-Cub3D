/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DdaCalcul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:42:37 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 17:57:32 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"
#include <math.h>

static void	_dda_calcul_wall(t_game *game, t_vector standard)
{
	double		arrondi;
	t_vector	position;

	if (game->map->map[game->rayon->map_x][game->rayon->map_y] == '1')
		game->rayon->hit = 1;
	else
	{
		if (game->rayon->side == 0)
		{
			arrondi = round(game->rayon->dir_x * 100) / 100;
			if (arrondi > 0.80 || arrondi < -0.80)
			{
				position = generateNewVector(game->rayon->map_y, \
				game->rayon->map_x);
				fillLine(game->minimap, position, standard);
			}
		}
		else if (game->rayon->side == 1)
		{
			position = generateNewVector(game->rayon->map_y, \
			game->rayon->map_x);
			fillLine(game->minimap, position, standard);
		}
	}
}

void	dda_calcul(t_game *game)
{
	t_vector	standard;

	standard = generateNewVector(WIN_H / 100, WIN_W / 100);
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
		_dda_calcul_wall(game, standard);
	}
}
