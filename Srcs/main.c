/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:05:22 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/08 20:31:57 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniMap.h"
#include "MyMiniLibx.h"

int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_mini_img	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 640, 480, "mini_map");
	img.img = mlx_new_image(mlx, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_key_hook(mlx_win, key_hook, &img);
	mlx_loop(mlx);
	return (0);
}
