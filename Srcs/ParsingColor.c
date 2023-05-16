/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingColor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:58:21 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/16 12:35:44 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static int	isLineFloor(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == 'F')
	{
		i++;
		while (str[i])
		{
			if (str[i] != ',' && (str[i] >= '9' || str[i] <= '0'))
				return (0);
			i++;
		}
		return (1);
	}
	else 
		return (0);
}

static int	getFloorColor(char *str, t_rgb *colorFloor)
{
	int		i;
	int		j;
	int		count;
	char	buffer[4];
	int		int_buffer;

	i = 0;
	j = 0;
	count = 0;
	ft_bzero(buffer, 4);
	while (str[i] != '\n' && str[i] == ' ')
		i++;
	while (str[i] != '\n')
	{
		if (str[i] == 'F')
			i = i + 2;
		while ((str[i] != ',' && str[i]) && j < 3)
		{
			if ('0' <= str[i] && '9' >= str[i])
				buffer[j++] = str[i++];
			else
				return (0);
		}
		if (str[i] != ',' && str[i] != '\n')
			return (0);
		int_buffer = ft_atoi(buffer, &count);
		if ((0 <= int_buffer && 255 >= int_buffer))
		{	
			if (colorFloor->r == -1)
				colorFloor->r = int_buffer;
			else if (colorFloor->g == -1)
				colorFloor->r = int_buffer;
			else if (colorFloor->b == -1)
				colorFloor->b = int_buffer;
		}
		else
			return (0);
		i++;
		ft_bzero(buffer, 4);
		j = 0;
		count = 0;
	}
	return (1);
}

unsigned long	createRGB(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

unsigned long	getColors(t_map2D *map2D, char *file)
{
	int		fd;
	t_rgb	colorFloor;
	t_rgb	colorGround;
	char	*line;
	int		count = 0;

	colorFloor.r = -1;
	colorFloor.g = -1;
	colorFloor.b = -1;
	colorGround.r = -1;
	colorGround.g = -1;
	colorGround.b = -1;
	fd = open(file, O_RDWR);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		
	}
}

