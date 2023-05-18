/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:22 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 11:41:52 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	end_it(t_game *game)
{
	(void) game;
	exit(0);
}

int	main(int argc, char **argv)
{
	t_map2D		*map2D;
	t_ray		*ray;
	t_game		*game;
	t_minimap	*minimap;
	
	(void)argc;
	game = (t_game *)malloc(sizeof(t_game));
	ray = (t_ray *)malloc(sizeof(t_ray));
	map2D = (t_map2D *)malloc(sizeof(t_map2D));
	minimap = (t_minimap *)malloc(sizeof(t_minimap));
	game->mlx = mlx_init(); // a free
	game->map = map2D;
	if (!fillTheTab(game, argv[1]) || !isMapAndPlayerCheck(map2D))
		return(dprintf(2, "Need to free.\n"), 1);
	if (!getColors(game, argv[1]))
		return(dprintf(2, "FREE->Erreur sur ls couleurs\n"), 0);
	initAll(game, map2D, ray, minimap);
	if (!get_player_position(map2D->map, ray))
		return (dprintf(2, "ERROR MAP\n"), 1);
	dprintf(2, "Height : %d || Width : %d\n", game->map->height, game->map->width);
	ft_mlx_pack(game);
	fillMinimap(game);
	return (0);
}
