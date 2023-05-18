/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:26:34 by tchevrie          #+#    #+#             */
/*   Updated: 2023/05/18 13:36:17 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	print_data(t_game *game)
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

int	isDir(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	init_parsing(t_game *game, char *file)
{
	int	fd;

	game->buffer_map = malloc(sizeof(char) * 1);
	game->buffer_map[0] = '\0';
	game->north = NULL;
	game->south = NULL;
	game->west = NULL;
	game->east = NULL;
	game->north = malloc(sizeof(t_minimap));
	game->south = malloc(sizeof(t_minimap));
	game->west = malloc(sizeof(t_minimap));
	game->east = malloc(sizeof(t_minimap));
	if (!game->north || !game->south || !game->west || !game->east \
	|| !game->buffer_map)
		return (ft_putstr_fd("Error\n" "malloc failed.\n", 2), -1);
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

	game->map->map = NULL;
	fd = init_parsing(game, file);
	if (fd == -1)
		return (0);
	if(!fillTheTab(game, fd) || !isMapAndPlayerCheck(game->map))
		return (close(fd), 0);
	print_data(game);
	return (close(fd), 1);
}
