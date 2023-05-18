/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseTextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:25:48 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 17:25:48 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static int	good_extension(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	if (i == -1)
		return (0);
	if (i < 3)
		return (0);
	i -= 3;
	return (!ft_strncmp(line + i, ".xpm", 4));
}

int	parse_texture(t_game *game, char *line, t_text *elem, int case_n)
{
	static int	north;
	static int	south;
	static int	west;
	static int	east;

	line = strip_l(line);
	if ((case_n == 1 && north) || (case_n == 2 && south) \
	|| (case_n == 3 && west) || (case_n == 4 && east) || !good_extension(line))
		return (parsing_error(line), 0);
	else if (case_n == 1)
		north = 1;
	else if (case_n == 2)
		south = 1;
	else if (case_n == 3)
		west = 1;
	else if (case_n == 4)
		east = 1;
	elem->image = mlx_xpm_file_to_image(game->mlx, line, \
	&(elem->width), &(elem->height));
	if (!(elem->image))
		return (parsing_error(line), 0);
	elem->addr = mlx_get_data_addr(elem->image, \
	&(elem->bpp), &(elem->line_length), &(elem->endian));
	return (1);
}
