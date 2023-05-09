/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:22 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 12:34:21 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniMap.h"
#include "MyMiniLibx.h"

void	ft_draw(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->window, game->data.image, 0, 0);
	mlx_key_hook(game->window, &ft_get_transfo, game);
	mlx_loop(game->mlx);
}

int	main(void)
{
	t_game		*game;
	
	game = (t_game *)malloc(sizeof(t_game));
	game->map = ft_split( \
"        1111111111111111111111111\n"
"        1000000000110000000000001\n"
"        1011000001110000000000001\n"
"        1001000000000000000000001\n"
"111111111011000001110000000000001\n"
"100000000011000001110111111111111\n"
"11110111111111011100000010001\n"
"11110111111111011101010010001\n"
"11000000110101011100000010001\n"
"10000000000000001100000010001\n"
"10000000000000001101010010001\n"
"11000001110101011111011110N0111\n"
"11110111 1110101 101111010001\n"
"11111111 1111111 111111111111\n"
, '\n');
	game->height = 0;
	game->width = 0;
	while (game->map[0][game->width])
		game->width++;
	while (game->map[game->height][0])
		game->height++;
	game->pos.x = 150;
	game->pos.y = 300;
	game->pos.dir = 'N';
	game->mlx = mlx_init();
	game->data.image = mlx_new_image(game->mlx, 640, 480);
	game->window = mlx_new_window(game->mlx, 640, 480, "mini_map");
	game->data.addr = mlx_get_data_addr(game->data.image, &game->data.bpp, &game->data.line_length,
								&game->data.endian);
	ft_draw(game);
	return (0);
}
