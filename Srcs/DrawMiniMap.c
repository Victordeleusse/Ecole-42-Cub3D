/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawMiniMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:10:24 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 18:55:01 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	get_mini_color(t_game *g, int len, int xy[2])
{
	int	color;

	color = 0xFF000000;
	if (xy[0] < len && g->map[xy[1]][xy[0]] == ' ')
		color = 0xFF000000;
	else if (xy[0] < len && g->map[xy[1]][xy[0]] != '1')
		color = 0x005E5C64;
	else if (xy[0] < len)
		color = 0x008BB5F8;
	return (color);
}

void	cub_miniview(t_game *g)
{
	int	xy[2];
	int	aux[2];

	aux[1] = -1;
	xy[1] = (g->pos.y + 0.5) * SIZE - (int)(g->miniview.height / 2);
	while (++aux[1] < (g->miniview.height))
	{
		aux[0] = -1;
		xy[0] = (g->pos.x + 0.5) * SIZE - (int)(g->miniview.width / 2);
		while (++aux[0] < g->miniview.width)
		{
			if (xy[1] >= 0 && xy[1] < (g->height * SIZE) && xy[0] >= 0 \
						&& xy[0] < (g->width * SIZE))
				my_mlx_pixel_put(&g->miniview, aux[0], aux[1], \
					my_mlx_pixel_get(&g->data, xy[0], xy[1]));
			else
				my_mlx_pixel_put(&g->miniview, aux[0], aux[1], 0xFFFF00);
			xy[0]++;
		}
		xy[1]++;
	}
}


void	cub_minimap(t_game *g)
{
	int	xy[2];
	int	len;

	xy[1] = -1;
	while (++xy[1] < g->height)
	{
		xy[0] = -1;
		len = ft_strlen(g->map[xy[1]]);
		while (++xy[0] < g->width)
			my_mlx_area_put(&g->data, \
				ft_newvector(xy[0] * SIZE, xy[1] * SIZE), \
				ft_newvector(SIZE, SIZE), get_mini_color(g, len, xy));
	}
}

void	redraw_elem(t_game *g, t_mini_img img, int x, int y)
{
	int			p[2];
	t_mini_img	images[2];

	p[0] = x;
	p[1] = y;
	images[0] = img;
	images[1] = g->data;
	my_mlx_img_to_img(p, images, 0xFF000000);
}