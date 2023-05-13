/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:48:21 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/13 16:01:05 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static void	free_map2D(t_map2D *map2D)
{
	int	i;

	i = 0;
	while (map2D->map[i])
	{
		free(map2D->map[i]);
		i++;
	}
	free(map2D->map);
	free(map2D);
}

void	free_all(t_map2D *map2D, t_ray *ray, t_game *game)
{
	free_map2D(map2D);
	free(ray);
	free(game);
}