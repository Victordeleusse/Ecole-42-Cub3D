/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:48:21 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 13:34:10 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	free_parsing(t_game *game)
{
	free(game->buffer_map);
	if (game->north && game->north->image)
		mlx_destroy_image(game->mlx, game->north->image);
	free(game->north);
	if (game->south && game->south->image)
		mlx_destroy_image(game->mlx, game->south->image);
	free(game->south);
	if (game->west && game->west->image)
		mlx_destroy_image(game->mlx, game->west->image);
	free(game->west);
	if (game->east && game->east->image)
		mlx_destroy_image(game->mlx, game->east->image);
	free(game->east);
}

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