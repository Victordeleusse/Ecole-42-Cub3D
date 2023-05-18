/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:26:34 by tchevrie          #+#    #+#             */
/*   Updated: 2023/05/18 16:50:02 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	parsing_error(char *text)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Parsing failed : "RED"\"", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("\""ENDCL"\n", 2);
}

static void	print_data(t_game *game)
{
	size_t	i;

	printf(GREEN"Parsing data"ENDCL"\n");
	printf("\n");
	printf("NO: %p\n", game->north);
	printf("SO: %p\n", game->south);
	printf("WE: %p\n", game->west);
	printf("EA: %p\n", game->east);
	printf("\n");
	printf("F: #%x\n", game->ground_color);
	printf("C: #%x\n", game->sky_color);
	printf("\n");
	if (!game->map || !game->map->map)
	{
		printf("tab: "BLUEBG"(nil)"ENDCL"\n");
		return ;
	}
	i = 0;
	while (game->map->map[i])
	{
		printf("%2zu: "BLUEBG"%s"ENDCL"\n", i, game->map->map[i]);
		i++;
	}
}

static int	init_parsing(t_game *game, char *file)
{
	int	fd;

	game->buffer_map = malloc(sizeof(char) * 1);
	game->buffer_map[0] = '\0';
	game->north = malloc(sizeof(t_minimap));
	game->south = malloc(sizeof(t_minimap));
	game->west = malloc(sizeof(t_minimap));
	game->east = malloc(sizeof(t_minimap));
	if (!game->north || !game->south || !game->west || !game->east \
	|| !game->buffer_map)
		return (ft_putstr_fd("Error\n"RED"malloc failed."ENDCL"\n", 2), -1);
	game->north->image = NULL;
	game->north->addr = NULL;
	game->south->image = NULL;
	game->south->addr = NULL;
	game->west->image = NULL;
	game->west->addr = NULL;
	game->east->image = NULL;
	game->east->addr = NULL;
	fd = open(file, O_RDONLY);
	return (fd);
}

int	parsing(t_game *game, char *file)
{
	int	fd;
	int	len;

	fd = init_parsing(game, file);
	if (fd == -1)
		return (ft_putstr_fd("Error\n"RED"Could not open file."ENDCL \
		"\n", 2), 0);
	len = ft_strlen(file);
	if (len < 5 || ft_strcmp(".cub", file + len - 4) != 0)
		return (ft_putstr_fd("Error\n"RED"Incorrect file extension."ENDCL \
		"\n", 2), close(fd), 0);
	if (!parse_data(game, fd) || !is_map_and_player_check(game->map))
		return (close(fd), 0);
	print_data(game);
	return (close(fd), 1);
}
