/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:10 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/24 13:50:17 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		sprites_to_array(t_all *all)
{
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	if (!(all->spritecast->sprites = (t_sprite *)malloc(
			all->pars->count_spr * sizeof(t_sprite))))
		error_handler(MAP_PARS, 0);
	while (i < all->pars->map_h && all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '2')
			{
				all->map[i][j] = 's';
				all->spritecast->sprites[k].x = (double)i;
				all->spritecast->sprites[k].y = (double)j;
				k++;
			}
			j++;
		}
		i++;
	}
}

static void	bubble_sort(t_sprite *sprite, int count)
{
	int			i;
	int			sorted;
	t_sprite	tmp;

	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (i < count - 1)
		{
			if (sprite[i].dist < sprite[i + 1].dist)
			{
				tmp = sprite[i];
				sprite[i] = sprite[i + 1];
				sprite[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

void		sort_sprites(t_sprite *sprites, int count)
{
	bubble_sort(sprites, count);
}
