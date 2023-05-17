/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingColor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:58:21 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/17 12:41:48 by vde-leus         ###   ########.fr       */
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
	if (i == 0 || i == 1)
		return (0);
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
	if (i == 0 || i == 1)
		return (0);
	if (str[i - 1] == ',' || count != 2)
		return (0);
	return (1);
}

static void	initRGB(t_rgb *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
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

static unsigned long	createRGB(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int	getColors(t_game *game, char *file)
{
	int		fd;
	int 	data;
	t_rgb	colorFloor;
	t_rgb	colorSky;
	char	*line;

	data = 0;
	initRGB(&colorFloor);
	initRGB(&colorSky);
	fd = open(file, O_RDWR);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (isLineSky(line))
		{	
			data++;
			if(!getRGB(line, &colorSky))
				data = -1;
		}
		if (isLineFloor(line))
		{	
			data++;
			if(!getRGB(line, &colorFloor))
				data = -1;
		}
		free(line);
	}
	if (data != 2)
	{	
		dprintf(2, "COLORS : Data missing or not well settled\n");
		return (0);
	}
	game->ground_color = createRGB(colorFloor.r, colorFloor.g, colorFloor.b);
	game->sky_color = createRGB(colorSky.r, colorSky.g, colorSky.b);
	return (1);
}

