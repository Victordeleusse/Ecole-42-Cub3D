/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:22 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/15 13:06:31 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	main(int argc, char **argv)
{
	t_map2D		*map2D;
	t_ray		*ray;
	t_game		*game;
	int			result = 0;

	(void)argc;
	game = (t_game *)malloc(sizeof(t_game));
	ray = (t_ray *)malloc(sizeof(t_ray));
	map2D = (t_map2D *)malloc(sizeof(t_map2D));
	map2D->map = ft_split( \
"111111111111111\n"
"100000000000001\n"
"100000000000001\n"
"100001111000001\n"
"100001111000001\n"
"100000000000001\n"
"100000000000001\n"
"100000000000001\n"
"100N00000000001\n"
"100000000000001\n"
"100000000000001\n"
"100000000000001\n"
"100000000000001\n"
"100000000000001\n"
"111111111111111\n"
, '\n');
	map2D->fd = open(argv[1], O_RDWR);
	result = extract_map(map2D);
	dprintf(2, "HEIGHT map : %d\n", result);
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
