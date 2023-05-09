/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:22 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 18:29:45 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	find_start(t_game *game)
{
	game->pos.y = 0;
	while (game->map[(int)game->pos.y][(int)game->pos.x] != 'N' && game->map[(int)game->pos.y][(int)game->pos.x] != '0')
	{	
		game->pos.x = 0;
		while(game->map[(int)game->pos.y][(int)game->pos.x] != 'N' && game->map[(int)game->pos.y][(int)game->pos.x])
			game->pos.x++;
		game->pos.y++;
	}
	game->pos.x = game->pos.x * SIZE;
	game->pos.y = game->pos.y * SIZE;
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
"100000000011000001110111100111111\n"
"11110111111111011100000010001\n"
"11110111111111011101010010001\n"
"11000000000101011100000010001\n"
"10000000000000001100000010001\n"
"10000000000000001101010010001\n"
"11000001110101011111011110N0111\n"
"11110111 1110101 101111010001\n"
"11111111 1111111 111111111111\n"
"00000000000000000000000000000\n"
, '\n');
	game->width = 0;
	game->height = 0;
	while (game->map[0][game->width])
		game->width++;
	while (game->map[game->height][0] != '0')
		game->height++;
	find_start(game);
	game->pos.dir = 'N';
	game->pos.speed = 0.15;
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, WIN_W, WIN_H, "mini_map");
	game->data.image = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->data.addr = mlx_get_data_addr(game->data.image, &game->data.bpp, &game->data.line_length,
								&game->data.endian);
	game->miniview.image = mlx_new_image(game->mlx, 30 * SIZE, 15 * SIZE);
	game->miniview.addr = mlx_get_data_addr(game->miniview.image, &game->miniview.bpp, \
		&game->miniview.line_length, &game->miniview.endian);
	game->miniview.width = 30 * SIZE;
	game->miniview.height = 15 * SIZE;
	ft_mlx_pack(game);
	return (0);
}
