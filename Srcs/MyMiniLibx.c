/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:58:40 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/08 20:35:31 by vde-leus         ###   ########.fr       */
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

int	key_hook(int keycode)
{
	printf("Hello from key_hook! from -> %d\n", keycode);
	return (0);
}