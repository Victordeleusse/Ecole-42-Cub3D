/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:22 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 15:29:06 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	init_mlx(t_game *game)
{
	game->buffer_map = NULL;
	game->north = NULL;
	game->south = NULL;
	game->west = NULL;
	game->east = NULL;
	game->window = NULL;
	game->image = NULL;
	game->addr = NULL;
	game->minimap->image = NULL;
	game->minimap->addr = NULL;
	game->image = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->minimap->image = mlx_new_image(game->mlx, WIN_W / 2, WIN_H / 3);
	if (!game->image || !game->minimap->image)
		return (0);
	game->addr = mlx_get_data_addr(game->image, &game->bpp, \
		&game->line_length,&game->endian);
	game->minimap->addr = mlx_get_data_addr(game->minimap->image, \
		&game->minimap->bpp, &game->minimap->line_length, &game->minimap->endian);
	if (!game->addr || !game->minimap->addr)
		return (0);
	return (1);
}

t_game	*init_allocs(void)
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
	game->map->map = NULL;
	return (game);
}

int	main(int argc, char **argv)
{
	t_game		*game;

	(void) argc;
	game = init_allocs();
	if (!game)
		return (ft_putstr_fd("Error\n" "Memory allocation failed.\n", 2), 1);
	if (!init_mlx(game) || !parsing(game, argv[1]))
		return (free_and_quit(game), 1);
	get_map_data(game);
	if (!get_player_position(game->map->map, game->rayon))
		return (free_and_quit(game), 1);
	game->window = mlx_new_window(game->mlx, WIN_W, WIN_H, "map");
	ft_mlx_pack(game);
	return (0);
}
