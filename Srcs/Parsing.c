/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:25:48 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/15 16:24:34 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	isDir(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

static int	isMapLine(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '0')
		{		
			if (isDir(str[i]))
				;
			else if (str[i] == '\n' && i != 0)
				break;
			else 
				return (0);
		}
		i++;
	}
	return (1);
}

static void	getHeightMap(char *file, t_map2D *map2D)
{
	char	*line;
	
	map2D->fd = open(file, O_RDWR);
	map2D->height = 0;
	while (1)
	{
		line = get_next_line(map2D->fd);
		if (!line)
			break ;
		if (!isMapLine(line))
			free (line);
		else
		{
			map2D->height++;
			free(line);
			line = get_next_line(map2D->fd);
			while (isMapLine(line))
			{
				map2D->height++;
				free(line);
				line = get_next_line(map2D->fd);
			}
			break ;
		}
	}
	close(map2D->fd);
}

int	fillTheTab(char *file, t_map2D *map2D)
{
	char	*line;
	int		len;
	int		i;
	// int	j;

	i = 0;
	len = 0;
	getHeightMap(file, map2D);
	map2D->width = 0;
	if (!map2D->height)
		return (0);
	map2D->fd = open(file, O_RDWR);
	map2D->map = (char **)malloc(sizeof(char *) * (map2D->height + 1));
	map2D->map[map2D->height] = 0;
	while (1)
	{
		line = get_next_line(map2D->fd);
		if (!line)
			break ;
		if (isMapLine(line))
		{	
			len = ft_strlen(line);
			if (len > map2D->width)
				map2D->width = len;
			map2D->map[i] = (char *)malloc(sizeof(char) * (len));
			ft_memcpy(map2D->map[i], line, len);
			map2D->map[i][len - 1] = '\0';
			i++;
		}	
		free (line);
	}
	close(map2D->fd);
	// j = 0;
	// while (j < map2D->height)
	// {
	// 	dprintf(2, "%d : %s\n", (j + 1), map2D->map[j]);
	// 	j++;
	// }
	return (1);
}
