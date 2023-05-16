/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingColor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:58:21 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/16 15:54:49 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static int	isLineFloor(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == 'F')
	{
		i++;
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		while (str[i] != '\n')
		{
			if (str[i] != ',' && (str[i] > '9' || str[i] < '0'))
				return (0);
			else if (str[i] == ',')
				count++;
			i++;
		}
	}
	if (str[i - 1] == ',' || count != 2)
		return (0);
	return (1);
}

static int	isLineSky(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == 'C')
	{
		i++;
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		while (str[i] != '\n')
		{
			if (str[i] != ',' && (str[i] > '9' || str[i] < '0'))
				return (0);
			else if (str[i] == ',')
				count++;
			i++;
		}
	}
	if (str[i - 1] == ',' || count != 2)
		return (0);
	return (1);
}

static int	getRGB(char *str, t_rgb *color)
{
	int		i;
	int		j;
	int		count;
	char	buffer[4];
	int		int_buffer;

	i = 0;
	while (str[i] && str[i] != '\n' && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && str[i] != '\n')
	{
		j = 0;
		count = 0;
		ft_bzero(buffer, 4);
		if (str[i] == 'F' || str[i] == 'C')
		{	
			i++;
			if (str[i] != ' ' && str[i] != '\t')
				return (0);
		}
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		while ((str[i] != ',' && str[i] != '\n') && j < 3)
			buffer[j++] = str[i++];
		if (str[i] != ',' && str[i] != '\n')
			return (0);
		int_buffer = ft_atoi(buffer, &count);
		if ((0 <= int_buffer && 255 >= int_buffer))
		{	
			if (color->r == -1)
				color->r = int_buffer;
			else if (color->g == -1)
				color->g = int_buffer;
			else if (color->b == -1)
				color->b = int_buffer;
		}
		else
			return (0);
		i++;
	}
	if (color->r == -1 || color->g == -1 || color->b == -1)
		return (0);
	return (1);
}

// static unsigned long	createRGB(int r, int g, int b)
// {
// 	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
// }

int	getColors(t_game *game, char *file)
{
	int		fd;
	t_rgb	colorFloor;
	t_rgb	colorSky;
	char	*line;

	(void)game;
	colorFloor.r = -1;
	colorFloor.g = -1;
	colorFloor.b = -1;
	colorSky.r = -1;
	colorSky.g = -1;
	colorSky.b = -1;
	fd = open(file, O_RDWR);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (isLineSky(line))
		{	
			if(!getRGB(line, &colorSky))
			{	
				dprintf(2, "ERROR SKY when trying to get colors\n");
				free(line);
				return (0);
			}
		}
		if (isLineFloor(line))
		{	
			if(!getRGB(line, &colorFloor))
			{	
				dprintf(2, "ERROR FLOOR when trying to get colors\n");
				free(line);
				return (0);
			}
		}
		free(line);
	}
	dprintf(2, "FLOOR : r->%d g->%d b->%d\n", colorFloor.r, colorFloor.g, colorFloor.b);
	dprintf(2, "SKY : r->%d g->%d b->%d\n", colorSky.r, colorSky.g, colorSky.b);
	return (1);
}

