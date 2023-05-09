/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyMiniLibx.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:55:46 by vde-leus          #+#    #+#             */
/*   Updated: 2023/05/09 15:57:21 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYMINILIBX_H
# define MYMINILIBX_H


typedef struct s_mini_img
{
	void	*image;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
} t_mini_img;

#endif