/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:10 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/24 13:50:17 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char *dst;

	dst = all->img->addr +
	(y * all->img->line_length + x * (all->img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
