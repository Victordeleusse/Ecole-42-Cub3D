/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingMap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:25:48 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 13:36:12 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	good_extension(char *line)
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

char	*strip_l(char *line)
{
	size_t	i;
	(void) i;
	(void) line;

	while (*line == ' ')
		line++;
	i = ft_strlen(line);
	if (i > 0)
		line[i - 1] = '\0';
	return (line);
}

char	*atoi_colors_next(char *str, int *nbr)
{
	*nbr = 0;
	if (!(*str) || !ft_isdigit(*str))
		return (NULL);
	while (*str != '\0' && ft_isdigit(*str))
		(*nbr) = ((*nbr) * 10) + (*(str++) - '0');
	return (str);
}

int	atoi_colors(char *str)
{
	int	color;
	int	nbr;

	str = atoi_colors_next(str, &nbr);
	if (!str)
		return (-1);
	color = nbr * 256 * 256;
	if (*(str++) != ',')
		return (-1);
	str = atoi_colors_next(str, &nbr);
	if (!str)
		return (-1);
	color += (nbr * 256);
	if (*(str++) != ',')
		return (-1);
	str = atoi_colors_next(str, &nbr);
	if (!str)
		return (-1);
	if (*str)
		return (-1);
	color += nbr;
	return (color);
}

void	parsing_error(char *text)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Parsing failed : "RED"\"", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("\""ENDCL"\n", 2);
}

int	parse_texture(t_game *game, char *line, t_minimap *elem, int case_n)
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

int	parse_color(char *line, int *elem, int case_n)
{
	static int	floor;
	static int	ceiling;

	line = strip_l(line);
	if ((case_n == 1 && floor) || (case_n == 2 && ceiling))
		return (parsing_error(line), 0);
	else if (case_n == 1)
		floor = 1;
	else if (case_n == 2)
		ceiling = 1;
	*elem = atoi_colors(line);
	if (*elem == -1)
		return (parsing_error(line), 0);
	return (1);
}

int	parse_map(t_game *game, char *line)
{
	char	*buffer;

	if (line[0] == '\n')
		return (parsing_error(line), 0);
	buffer = ft_strjoin(game->buffer_map, line);
	free(game->buffer_map);
	game->buffer_map = buffer;
	if (!game->buffer_map)
		return (parsing_error(line), 0);
	return (1);
}

int	parse_line(t_game *game, char *line)
{
	static int	elem_parsed;

	elem_parsed += 1;
	if (line[0] && line[0] != '\n' && elem_parsed < 7)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			return (parse_texture(game, line + 3, game->north, 1));
		else if (ft_strncmp(line, "SO ", 3) == 0)
			return (parse_texture(game, line + 3, game->south, 2));
		else if (ft_strncmp(line, "WE ", 3) == 0)
			return (parse_texture(game, line + 3, game->west, 3));
		else if (ft_strncmp(line, "EA ", 3) == 0)
			return (parse_texture(game, line + 3, game->east, 4));
		else if (ft_strncmp(line, "F ", 2) == 0)
			return (parse_color(line + 2, &game->ground_color, 1));
		else if (ft_strncmp(line, "C ", 2) == 0)
			return (parse_color(line + 2, &game->sky_color, 2));
		return (parsing_error(line), 0);
	}
	else if (elem_parsed > 7 || (line[0] && line[0] != '\n'))
		return (parse_map(game, line));
	elem_parsed -= 1;
	return (1);
}

int	fillTheTab(t_game *game, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!parse_line(game, line))
			return (free(line), 0);
		free(line);
	}
	game->map->map = ft_split(game->buffer_map, '\n');
	if (!game->map->map)
		return (0);
	return (1);
}


