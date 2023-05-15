/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:25:48 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/15 13:08:36 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static int	begin_end_Map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}


int	extract_map(t_map2D *map2D)
{
	int		height;
	char	*line;

	height = 0;
	while (1)
	{
		line = get_next_line(map2D->fd);
		dprintf(2, "line : %s\n", line);
		if (!line)
			break ;
		if (!begin_end_Map(line))
			free (line);
		else
		{
			height++;
			free(line);
			line = get_next_line(map2D->fd);
			while (!begin_end_Map(line))
			{
				height++;
				free(line);
				line = get_next_line(map2D->fd);
			}
			break ;
		}
	}
	if (height == 0)
		return (0);
	return (height);
}

