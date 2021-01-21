/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:38:00 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/19 14:38:02 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		my_image_init(t_all *all)
{
	if (!(all->img = (t_data *)ft_calloc(1, sizeof(t_data))))
		error_handler(MAP_PARS, 0);
	all->img->img = (char *)mlx_new_image(all->win->mlx, all->win->width,
	all->win->height);
	all->img->addr = (char *)mlx_get_data_addr(all->img->img,
	&all->img->bits_per_pixel, &all->img->line_length, &all->img->endian);
}

void		draw_all0(t_all *all)
{
	t_plr	*plr;
	int		x;

	plr = all->plr;
	x = 0;
	mlx_clear_window(all->win->mlx, all->win->win);
	while (x < all->win->width)
	{
		start_init(all, x);
		check_step(plr);
		check_hit(all, all->plr);
		paint_wall(all, x, 0, all->plr);
		x++;
	}
	paint_sprites(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->img->img, 0, 0);
}

int			my_exit(void)
{
	write(1, "Goodbye!!!\n", 11);
	exit(0);
}

void		game(t_all *all, int argc)
{
	my_plr_init(all);
	sprites_init(all);
	if (argc == 3)
		all->screen_save = 1;
	draw_all0(all);
}
