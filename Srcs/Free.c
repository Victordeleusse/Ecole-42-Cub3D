/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:48:21 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 16:53:12 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static void	free_parsing(t_game *game)
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

static void	free_mlx(t_game *game)
{
	if (game->minimap->image)
		mlx_destroy_image(game->mlx, game->minimap->image);
	if (game->image)
		mlx_destroy_image(game->mlx, game->image);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
}

static void	free_map2d(t_map2D *map2D)
{
	int	i;

	i = 0;
	if (!map2D)
		return ;
	if (map2D->map)
	{
		while (map2D->map[i])
		{
			free(map2D->map[i]);
			i++;
		}
		free(map2D->map);
	}
	free(map2D);
}

int	free_and_quit(t_game *game)
{
	free_parsing(game);
	free_mlx(game);
	free_map2d(game->map);
	free(game->rayon);
	free(game->minimap);
	free(game->mlx);
	free(game);
	exit(0);
}
