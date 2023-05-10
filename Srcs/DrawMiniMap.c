/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawMiniMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:10:24 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/10 11:19:29 by vde-leus         ###   ########.fr       */
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
