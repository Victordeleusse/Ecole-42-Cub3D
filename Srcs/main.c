/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:22 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 11:00:23 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniMap.h"
#include "MyMiniLibx.h"

void	ft_draw(t_mini_img *data)
{
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	mlx_key_hook(data->window, &ft_get_transfo, data);
	mlx_loop(data->mlx);
}

int	main(void)
{
	t_mini_img	*data;
	
	data = (t_mini_img *)malloc(sizeof(t_mini_img));
	data->pos = (t_player *)malloc(sizeof(t_player));
	data->pos->x = 150;
	data->pos->y = 300;
	data->pos->dir = 'N';
	data->mlx = mlx_init();
	data->image = mlx_new_image(data->mlx, 640, 480);
	data->window = mlx_new_window(data->mlx, 640, 480, "mini_map");
	data->addr = mlx_get_data_addr(data->image, &data->bpp, &data->line_length,
								&data->endian);
	ft_draw(data);
	return (0);
}
