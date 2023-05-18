/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:23:49 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 15:10:24 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static int	crossCheck(t_map2D *map2D, int i, int j)
{
	if (i == 0 || j == 0 || !map2D->map[i + 1] || !map2D->map[i][j + 1])
		return (0);
	if (map2D->map[i - 1][j] != '0' && map2D->map[i - 1][j] != '1' \
	&& !isDir(map2D->map[i - 1][j]))
		return (0);
	if (map2D->map[i + 1][j] != '0' && map2D->map[i + 1][j] != '1' \
	&& !isDir(map2D->map[i + 1][j]))
		return (0);
	if (map2D->map[i][j - 1] != '0' && map2D->map[i][j - 1] != '1' \
	&& !isDir(map2D->map[i][j - 1]))
		return (0);
	if (map2D->map[i][j + 1] != '0' && map2D->map[i][j + 1] != '1' \
	&& !isDir(map2D->map[i][j + 1]))
		return (0);
	return (1);
}

static int	crossCheckDir(t_map2D *map2D, int i, int j)
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

static int	isOnlyOnePlayer(t_map2D *map2D)
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
			if (isDir(map2D->map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count == 1)
		return (1);
	return (0);
}

static int	isWellClosed(t_map2D *map2D)
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
				if (!crossCheck(map2D, i, j))
					return (0);
			}
			else if (isDir(map2D->map[i][j]))
			{	
				if (!crossCheckDir(map2D, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	isMapAndPlayerCheck(t_map2D *map2D)
{
	if (!isOnlyOnePlayer(map2D) || !isWellClosed(map2D))
		return (ft_putstr_fd("Error\n" "Parsing failed : "RED"incorrect map format."ENDCL"\n", 2), 0);
	return (1);
}
