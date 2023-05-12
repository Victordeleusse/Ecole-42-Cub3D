/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:12:11 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/12 21:50:28 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub.h"
	
int	ft_key_action(int keycode, t_ray *ray, t_map2D *map2D)
{
	//move backward if no wall behind you
	if (keycode == KEY_S)
	{
		if (map2D->map[(int)(ray->pos_x - ray->dir_x * ray->movespeed)][(int)(ray->pos_y)] == '0')
			ray->pos_x -= ray->dir_x * ray->movespeed;
		if (map2D->map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_y * ray->movespeed)] == '0')
			ray->pos_y -= ray->dir_y * ray->movespeed;
	}
	//move forward if no wall in front of you
	if (keycode == KEY_W)
	{
		if (map2D->map[(int)(ray->pos_x + ray->dir_x * ray->movespeed)][(int)(ray->pos_y)] == '0')
			ray->pos_x += ray->dir_x * ray->movespeed;
		if (map2D->map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_y * ray->movespeed)] == '0')
			ray->pos_y += ray->dir_y * ray->movespeed;
	}
	//move to the right
	if (keycode == KEY_D)
	{
		if (map2D->map[(int)(ray->pos_x + ray->plane_x * ray->movespeed)][(int)(ray->pos_y)] == '0')
			ray->pos_x += ray->plane_x * ray->movespeed;
		if (map2D->map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->plane_y * ray->movespeed)] == '0')
			ray->pos_y += ray->plane_y * ray->movespeed;
	}
	//move to the left
	if (keycode == KEY_A)
	{
		if (map2D->map[(int)(ray->pos_x - ray->plane_x * ray->movespeed)][(int)(ray->pos_y)] == '0')
			ray->pos_x -= ray->plane_x * ray->movespeed;
		if (map2D->map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->plane_y * ray->movespeed)] == '0')
			ray->pos_y -= ray->plane_y * ray->movespeed;
	}
	//rotation to the right
	if (keycode == KEY_RIGHT)
	{
		ray->old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-ray->rotspeed)
			- ray->dir_y * sin(-ray->rotspeed);
		ray->dir_y = ray->old_dir_x * sin(-ray->rotspeed)
			+ ray->dir_y * cos(-ray->rotspeed);
		ray->old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-ray->rotspeed)
			- ray->plane_y * sin(-ray->rotspeed);
		ray->plane_y = ray->old_plane_x * sin(-ray->rotspeed)
			+ ray->plane_y * cos(-ray->rotspeed);
	}
	//move to the left
	if (keycode == KEY_LEFT)
	{
		ray->old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(ray->rotspeed)
			- ray->dir_y * sin(ray->rotspeed);
		ray->dir_y = ray->old_dir_x * sin(ray->rotspeed)
			+ ray->dir_y * cos(ray->rotspeed);
		ray->old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(ray->rotspeed)
			- ray->plane_y * sin(ray->rotspeed);
		ray->plane_y = ray->old_plane_x * sin(ray->rotspeed)
			+ ray->plane_y * cos(ray->rotspeed);
	}
	return (0);
}
	