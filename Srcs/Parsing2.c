/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:23:49 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/15 16:37:07 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static int	crossCheck(t_map2D *map2D, int i, int j)
{
	if (i == 0 || j == 0 || !map2D->map[i + 1] || !map2D->map[i][j + 1])
		return (0);
	if (map2D->map[i - 1][j] != '0' && map2D->map[i - 1][j] != '1' && !isDir(map2D->map[i - 1][j]))
		return (0);
	if (map2D->map[i + 1][j] != '0' && map2D->map[i + 1][j] != '1' && !isDir(map2D->map[i + 1][j]))
		return (0);
	if (map2D->map[i][j - 1] != '0' && map2D->map[i][j - 1] != '1' && !isDir(map2D->map[i][j - 1]))
		return (0);
	if (map2D->map[i][j + 1] != '0' && map2D->map[i][j + 1] != '1' && !isDir(map2D->map[i][j + 1]))
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

int	isOnlyOnePlayer(t_map2D *map2D)
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

int	isWellClosed(t_map2D *map2D)
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
}
