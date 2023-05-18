/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseData.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:25:48 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 16:48:26 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

int	is_dir(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

char	*strip_l(char *line)
{
	size_t	i;

	while (*line == ' ')
		line++;
	i = ft_strlen(line);
	if (i > 0)
		line[i - 1] = '\0';
	return (line);
}

static int	parse_map(t_game *game, char *line)
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

static int	parse_line(t_game *game, char *line)
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

int	parse_data(t_game *game, int fd)
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
