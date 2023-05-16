/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:22 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/16 16:30:24 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	main(int argc, char **argv)
{
	t_map2D		*map2D;
	t_ray		*ray;
	t_game		*game;

	(void)argc;
	game = (t_game *)malloc(sizeof(t_game));
	ray = (t_ray *)malloc(sizeof(t_ray));
	map2D = (t_map2D *)malloc(sizeof(t_map2D));

	if (!fillTheTab(argv[1], map2D) || !isMapAndPlayerCheck(map2D))
		return(dprintf(2, "FREE->Erreur sur la map"), 0);
	if (!getColors(game, argv[1]))
		return(dprintf(2, "FREE->Erreur sur ls couleurs\n"), 0);
	dprintf(2, "sky color : |%lu| || ground color : |%lu|\n", game->sky_color, game->ground_color);
	// game->map = map2D;
	// game->rayon = ray;
	// init_game(game);
	// init_map_2D(map2D);
	// if (!get_player_position(map2D->map, ray))
	// 	return (dprintf(2, "ERROR MAP\n"), 1);
	// dprintf(2, "x : %f || y : %f\n", ray->pos_x, ray->pos_y);
	// ray_init(ray);
	// get_player_direction(ray);
	// ft_mlx_pack(game);
	// // free_all(map2D, ray, game);
	return (0);
}
