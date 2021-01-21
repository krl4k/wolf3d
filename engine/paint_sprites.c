/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:10 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/24 13:50:17 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		init_sprite_order_dist(t_all *all)
{
	int i;

	i = 0;
	while (i < all->spritecast->num_sprites)
	{
		all->spritecast->sprites[i].dist = (
				(all->plr->player_x - all->spritecast->sprites[i].x) *
				(all->plr->player_x - all->spritecast->sprites[i].x) +
				(all->plr->player_y - all->spritecast->sprites[i].y) *
				(all->plr->player_y - all->spritecast->sprites[i].y));
		i++;
	}
	all->spritecast->tex_width = 64;
	all->spritecast->tex_height = 64;
}

void		calc_draw_sprt(t_sprt_cast *s, t_all *all)
{
	int y;
	int d;

	while (s->stripe < s->draw_end_x)
	{
		s->tex_x = (int)(256 * (s->stripe - (-s->sprite_width / 2 +
		s->sprite_screen_x)) * s->tex_width / s->sprite_width) / 256;
		if (s->transform_y > 0 && s->stripe > 0 &&
		s->stripe < all->win->width && s->transform_y <
		all->plr->z_buffer[s->stripe])
		{
			y = s->draw_start_y;
			while (y < s->draw_end_y)
			{
				d = y * 256 - all->win->height * 128 + s->sprite_height * 128;
				s->tex_y = ((d * s->tex_height) / s->sprite_height) / 256;
				s->color = (*(int *)(all->spr->addr +
			((s->tex_x + (s->tex_y * 64)) * (all->spr->bits_per_pixel / 8))));
				if ((s->color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(all, s->stripe, y, s->color);
				y++;
			}
		}
		s->stripe++;
	}
}

void		calc_draw(t_sprt_cast *sprt, t_all *all)
{
	sprt->draw_start_y = -sprt->sprite_height / 2 + all->win->height / 2;
	if (sprt->draw_start_y < 0)
		sprt->draw_start_y = 0;
	sprt->draw_end_y = sprt->sprite_height / 2 + all->win->height / 2;
	if (sprt->draw_end_y >= all->win->height)
		sprt->draw_end_y = all->win->height - 1;
	sprt->sprite_width = abs((int)(all->win->height / sprt->transform_y));
	sprt->draw_start_x = -sprt->sprite_width / 2 + sprt->sprite_screen_x - 0.6;
	if (sprt->draw_start_x < 0)
		sprt->draw_start_x = 0;
	sprt->draw_end_x = sprt->sprite_width / 2 + sprt->sprite_screen_x - 0.6;
	if (sprt->draw_end_x >= all->win->width)
		sprt->draw_end_x = all->win->width - 1;
}

void		sprite1(t_all *all, int i)
{
	t_sprt_cast *sprt;

	sprt = all->spritecast;
	sprt->sprite_x = sprt->sprites[i].x - all->plr->player_x + 0.5;
	sprt->sprite_y = sprt->sprites[i].y - all->plr->player_y + 0.5;
	sprt->inv_det = 1.0 / (all->plr->plane_x * all->plr->dir_y -
	all->plr->dir_x * all->plr->plane_y);
	sprt->transform_x = sprt->inv_det * (all->plr->dir_y * sprt->sprite_x -
	all->plr->dir_x * sprt->sprite_y);
	sprt->transform_y = sprt->inv_det * (-all->plr->plane_y * sprt->sprite_x +
	all->plr->plane_x * sprt->sprite_y);
	sprt->sprite_screen_x = (int)((all->win->width / 2) *
	(1 + sprt->transform_x / sprt->transform_y));
	sprt->sprite_height = abs((int)(all->win->height / sprt->transform_y));
	calc_draw(sprt, all);
}

void		paint_sprites(t_all *all)
{
	int			i;
	t_sprt_cast	*sprt;

	i = 0;
	sprt = all->spritecast;
	init_sprite_order_dist(all);
	sort_sprites(all->spritecast->sprites, all->spritecast->num_sprites);
	while (i < all->spritecast->num_sprites)
	{
		sprite1(all, i);
		sprt->stripe = sprt->draw_start_x;
		calc_draw_sprt(sprt, all);
		i++;
	}
}
