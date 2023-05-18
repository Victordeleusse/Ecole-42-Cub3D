/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:41:16 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 17:05:17 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

// void	draw_text(t_game *game, int	texdir, int x, int y)
// {
// 	t_text	tex;
// 	int		i;

// 	y = y - 1;
// 	tex = texture[data->texdir];
// 	tex.step = 1.0 * tex.height / data->ray->line_height;
// 	tex.tex_x = (int)(tex.wallx * (double)tex.width);
// 	if (data->ray->side == 0 && data->ray->rdx > 0)
// 		tex.tex_x = tex.width - tex.tex_x - 1;
// 	if (data->ray->side == 1 && data->ray->rdy < 0)
// 		tex.tex_x = tex.width - tex.tex_x - 1;
// 	tex.texpos = (y - data->ray->h / 2 + data->ray->line_height / 2) * tex.step;
// 	while (++y <= data->ray->draw_end)
// 	{
// 		tex.texpos += tex.step;
// 		tex.tex_y = (int)tex.texpos & (tex.height - 1);
// 		i = tex.tex_y * tex.line_length + tex.tex_x * (tex.bits_per_pixel / 8);
// 		if (y < data->ray->h && x < data->ray->w)
// 		{
// 			my_mlx_pixel_put(data, x, y, create_trgb(0,
// 					(int)(unsigned char)tex.addr[i + 2],
// 					(int)(unsigned char)tex.addr[i + 1],
// 					(int)(unsigned char)tex.addr[i]));
// 		}
// 	}
// }