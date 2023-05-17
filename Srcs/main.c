/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:22 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/17 19:23:29 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	end_it(t_game *game)
{
	(void) game;
	exit(0);
}

t_game	*ft_init(void)
{
	t_map2D		*map2D;
	t_ray		*ray;
	t_game		*game;
	t_minimap	*minimap;

	game = NULL;
	game = (t_game *)malloc(sizeof(t_game));
	ray = NULL;
	ray = (t_ray *)malloc(sizeof(t_ray));
	map2D = NULL;
	map2D = (t_map2D *)malloc(sizeof(t_map2D));
	minimap = NULL;
	minimap = (t_minimap *)malloc(sizeof(t_minimap));
	if (!game || !ray || ! map2D || !minimap)
		return (free(game), free(ray), free(map2D), free(minimap), NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), free(ray), free(map2D), free(minimap), NULL);
	game->rayon = ray;
	game->map = map2D;
	game->minimap = minimap;
	return (game);
}

int	main(int argc, char **argv)
{
	t_game		*game;

	game = ft_init();
	if (!game)
		return (1);
	(void)argc;
	ft_init();
	if (!fillTheTab(game, argv[1]) || !isMapAndPlayerCheck(game->map))
		return(dprintf(2, "Need to free.\n"), 1);
	initAll(game);
	if (!get_player_position(game->map->map, game->rayon))
		return (dprintf(2, "ERROR MAP\n"), 1);
	ft_mlx_pack(game);
	return (0);
}
