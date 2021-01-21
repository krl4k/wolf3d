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

#include "parser.h"

void	check_screen_size(t_all *all)
{
	int r_h;
	int r_w;

	all->win->width = all->pars->res_width;
	all->win->height = all->pars->res_height;
	mlx_get_screen_size(all->win->mlx, &r_w, &r_h);
	if (all->pars->res_width > r_w)
		all->win->width = r_w;
	if (all->pars->res_height > r_h)
		all->win->height = r_h;
}

void	my_mlx_init(t_all *all)
{
	if (!(all->win = (t_vars *)malloc(sizeof(t_vars))))
		error_handler(MAP_PARS, 0);
	all->win->mlx = mlx_init();
	check_screen_size(all);
}
