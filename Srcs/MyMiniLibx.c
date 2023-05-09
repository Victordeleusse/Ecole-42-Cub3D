/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:58:40 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 10:58:39 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MyMiniLibx.h"

void	my_mlx_pixel_put(t_mini_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_mini_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	ft_clear_window(t_mini_img *data)
{
	mlx_destroy_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, 640, 480);
	return ;
}

int	ft_key_action(int keycode, t_player *pos)
{
	fprintf(stderr, "KEY\n");
	if (keycode == KEY_LEFT)
		pos->x -= DEP;
	else if (keycode == KEY_RIGHT)
		pos->x += DEP;	
	if (keycode == KEY_UP)
		pos->y -= DEP;
	if (keycode == KEY_DOWN)
		pos->y += DEP;
	return (0);
}

int	ft_get_transfo(int key, t_mini_img *data)
{	
	ft_clear_window(data);
	mlx_clear_window(data->mlx, data->window);
	ft_key_action(key, data->pos);
	ft_mlx_pack(data);
	return (0);
}

void	ft_mlx_pack(t_mini_img *data)
{
	my_mlx_pixel_put(data, data->pos->x, data->pos->y, 0x00FF0000);
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	mlx_key_hook(data->window, &ft_get_transfo, data);
	mlx_loop(data->mlx);
}