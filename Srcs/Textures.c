/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:41:16 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 20:12:46 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

t_text	*find_text(t_game *game, int texdir)
{
	t_text	*tex;

	tex = NULL;
	if (texdir == 0)
		tex = game->north;
	else if (texdir == 1)
		tex = game->south;
	else if (texdir == 2)
		tex = game->west;
	else if (texdir == 3)
		tex = game->east;
	return (tex);
}

void	draw_text(t_game *game, int texdir, int x, int y)
{
	t_text	*tex;
	int		i;

	tex = find_text(game, texdir);
	y = y - 1;
	tex->step = 1.0 * tex->height / game->rayon->line_height;
	tex->tex_x = (int)(tex->wallx * (double)tex->width);
	if (game->rayon->side == 0 && game->rayon->rdx > 0)
		tex->tex_x = tex->width - tex->tex_x - 1;
	if (game->rayon->side == 1 && game->rayon->rdy < 0)
		tex->tex_x = tex->width - tex->tex_x - 1;
	tex->texpos = (y - game->rayon->h / 2 \
	+ game->rayon->line_height / 2) * tex->step;
	tex->texpos += tex->step;
	tex->tex_y = (int)tex->texpos & (tex->height - 1);
	i = tex->tex_y * tex->line_length + tex->tex_x * (tex->bpp / 8);
	my_mlx_pixel_put(game, x, y, create_trgb(0, \
	(int)(unsigned char)tex->addr[i + 2], \
	(int)(unsigned char)tex->addr[i + 1], \
	(int)(unsigned char)tex->addr[i]));
}

void	choose_tex(t_game *game, t_text **tex)
{
	if (game->rayon->side == 0 && game->rayon->rdx < 0)
	{	
		game->texdir = 0;
		*tex = game->north;
	}
	if (game->rayon->side == 0 && game->rayon->rdx >= 0)
	{	
		game->texdir = 1;
		*tex = game->south;
	}
	if (game->rayon->side == 1 && game->rayon->rdy < 0)
	{	
		game->texdir = 2;
		*tex = game->west;
	}	
	if (game->rayon->side == 1 && game->rayon->rdy >= 0)
	{	
		game->texdir = 3;
		*tex = game->east;
	}
}

void	choose_tex_ray(t_game *game)
{
	t_text	*tex;

	game->texdir = 0;
	choose_tex(game, &tex);
	if (game->rayon->side == 0)
		tex->wallx = game->rayon->pos_y
			+ game->rayon->perp_wall_dist * game->rayon->rdy;
	else
		tex->wallx = game->rayon->pos_x
			+ game->rayon->perp_wall_dist * game->rayon->rdx;
	tex->wallx -= floor((tex->wallx));
}
