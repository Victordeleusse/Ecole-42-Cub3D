/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:23:49 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 16:50:13 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static int	cross_check(t_map2D *map2D, int i, int j)
{
	if (i == 0 || j == 0 || !map2D->map[i + 1] || !map2D->map[i][j + 1])
		return (0);
	if (map2D->map[i - 1][j] != '0' && map2D->map[i - 1][j] != '1' \
	&& !is_dir(map2D->map[i - 1][j]))
		return (0);
	if (map2D->map[i + 1][j] != '0' && map2D->map[i + 1][j] != '1' \
	&& !is_dir(map2D->map[i + 1][j]))
		return (0);
	if (map2D->map[i][j - 1] != '0' && map2D->map[i][j - 1] != '1' \
	&& !is_dir(map2D->map[i][j - 1]))
		return (0);
	if (map2D->map[i][j + 1] != '0' && map2D->map[i][j + 1] != '1' \
	&& !is_dir(map2D->map[i][j + 1]))
		return (0);
	return (1);
}

static int	cross_check_dir(t_map2D *map2D, int i, int j)
{
	if (i == 0 || j == 0 || !map2D->map[i + 1] || !map2D->map[i][j + 1])
		return (0);
	if (map2D->map[i - 1][j] != '0' && map2D->map[i - 1][j] != '1')
		return (0);
	if (map2D->map[i + 1][j] != '0' && map2D->map[i + 1][j] != '1')
		return (0);
	if (map2D->map[i][j - 1] != '0' && map2D->map[i][j - 1] != '1')
		return (0);
	if (map2D->map[i][j + 1] != '0' && map2D->map[i][j + 1] != '1')
		return (0);
	return (1);
}

static int	is_only_one_player(t_map2D *map2D)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map2D->map[i])
	{
		j = 0;
		while (map2D->map[i][j])
		{
			if (is_dir(map2D->map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count == 1)
		return (1);
	return (0);
}

static int	is_well_closed(t_map2D *map2D)
{
	int	i;
	int	j;

	i = 0;
	while (map2D->map[i])
	{
		j = 0;
		while (map2D->map[i][j])
		{
			if (map2D->map[i][j] == '0')
			{
				if (!cross_check(map2D, i, j))
					return (0);
			}
			else if (is_dir(map2D->map[i][j]))
			{	
				if (!cross_check_dir(map2D, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_map_and_player_check(t_map2D *map2D)
{
	if (!is_only_one_player(map2D) || !is_well_closed(map2D))
		return (ft_putstr_fd("Error\n" \
		"Parsing failed : "RED"incorrect map format."ENDCL"\n", 2), 0);
	return (1);
}
