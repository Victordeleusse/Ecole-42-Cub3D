/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:22 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/17 12:37:46 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

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
	if (!fillTheTab(argv[1], map2D) || !isMapAndPlayerCheck(map2D))
		return(dprintf(2, "FREE->Erreur sur la map"), 0);
	if (!getColors(game, argv[1]))
		return(dprintf(2, "FREE->Erreur sur ls couleurs\n"), 0);
	initAll(game, map2D, ray, minimap);
	if (!get_player_position(map2D->map, ray))
		return (dprintf(2, "ERROR MAP\n"), 1);
	ft_mlx_pack(game);
	// fillMinimap(game);
	// raycasting(game, ray, map2D);
	mlx_put_image_to_window(game->mlx, game->window, game->minimap->image, 0, 0);
	mlx_loop(game->mlx);
	// // free_all(map2D, ray, game);
	return (0);
}
