/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseColors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:25:48 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 18:12:01 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

static char	*atoi_colors_next(char *str, int *nbr)
{
	*nbr = 0;
	if (!(*str) || !ft_isdigit(*str))
		return (NULL);
	while (*str != '\0' && ft_isdigit(*str))
		(*nbr) = ((*nbr) * 10) + (*(str++) - '0');
	return (str);
}

static int	atoi_colors(char *str)
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
	printf("line: %s | sky: %x\n | ground : %x | case: %x | *elem = %x | elem = %p\n", line, 0, 0, case_n, *elem, elem);
	return (1);
}
