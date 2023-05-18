/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:41:16 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/18 18:36:27 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"

void	draw_text(t_game *game, int	texdir, int x, int y)
{
	t_text	*tex;
	int		i;

	tex = NULL;
	y = y - 1;
	if (texdir == 0)
		tex = game->north;
	else if (texdir == 1)
		tex = game->south;
	else if (texdir == 2)
		tex = game->west;
	else if (texdir == 3)
		tex = game->east;
	tex->step = 1.0 * tex->height / game->rayon->line_height;
	tex->tex_x = (int)(tex->wallx * (double)tex->width);
	if (game->rayon->side == 0 && game->rayon->rdx > 0)
		tex->tex_x = tex->width - tex->tex_x - 1;
	if (game->rayon->side == 1 && game->rayon->rdy < 0)
		tex->tex_x = tex->width - tex->tex_x - 1;
	tex->texpos = (y - game->rayon->h / 2 + game->rayon->line_height / 2) * tex->step;
	tex->texpos += tex->step;
	tex->tex_y = (int)tex->texpos & (tex->height - 1);
	i = tex->tex_y * tex->line_length + tex->tex_x * (tex->bpp / 8);
	{
		my_mlx_pixel_put(game, x, y, create_trgb(0,
				(int)(unsigned char)tex->addr[i + 2],
				(int)(unsigned char)tex->addr[i + 1],
				(int)(unsigned char)tex->addr[i]));
	}
}

void	choose_tex_ray(t_game *game)
{
	t_text	*tex;
	
	game->texdir = 0;
	if (game->rayon->side == 0 && game->rayon->rdx < 0)
	{	
		game->texdir = 0;
		tex = game->north;
	}
	if (game->rayon->side == 0 && game->rayon->rdx >= 0)
	{	
		game->texdir = 1;
		tex = game->south;
	}
	if (game->rayon->side == 1 && game->rayon->rdy < 0)
	{	
		game->texdir = 2;
		tex = game->west;
	}	
	if (game->rayon->side == 1 && game->rayon->rdy >= 0)
	{	
		game->texdir = 3;
		tex = game->east;
	}
	if (game->rayon->side == 0)
		tex->wallx = game->rayon->pos_y
			+ game->rayon->perp_wall_dist * game->rayon->rdy;
	else
		tex->wallx = game->rayon->pos_x
			+ game->rayon->perp_wall_dist * game->rayon->rdx;
	tex->wallx -= floor((tex->wallx));
}
