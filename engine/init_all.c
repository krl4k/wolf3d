/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:10 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/24 13:50:17 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		sprites_init(t_all *all)
{
	if (!(all->spritecast = (t_sprt_cast *)malloc(sizeof(t_sprt_cast))))
		error_handler(MAP_PARS, 0);
	all->spritecast->num_sprites = all->pars->count_spr;
	sprites_to_array(all);
}

static void	init_w_e(t_all *all)
{
	all->plr->dir_x = -1;
	all->plr->dir_y = 0;
	all->plr->plane_x = 0;
	all->plr->plane_y = 0.66;
	if (all->pars->dir == 'E')
	{
		all->plr->dir_x = 1.0;
		all->plr->plane_y = -0.66;
	}
}

void		dir_init(t_all *all)
{
	if (all->pars->dir == 'S' || all->pars->dir == 'N')
	{
		all->plr->dir_x = 0;
		all->plr->dir_y = 1;
		all->plr->plane_x = 0.66;
		all->plr->plane_y = 0;
		if (all->pars->dir == 'N')
		{
			all->plr->dir_y = -1.0;
			all->plr->plane_x = -0.66;
		}
	}
	else if (all->pars->dir == 'W' || all->pars->dir == 'E')
	{
		init_w_e(all);
	}
}

void		my_plr_init(t_all *all)
{
	if (!(all->plr = (t_plr *)malloc(sizeof(t_plr))))
		error_handler(MAP_PARS, 0);
	all->plr->player_x = all->pars->f_plr_y;
	all->plr->player_y = all->pars->f_plr_x;
	dir_init(all);
	all->map = all->pars->map;
	if (!(all->plr->z_buffer = (double *)malloc(
			(all->win->width + 1) * sizeof(double))))
		error_handler(MAP_PARS, 0);
}

void		start_init(t_all *all, int x)
{
	t_plr *plr;

	plr = all->plr;
	all->screen_save = 0;
	plr->camera_x = 2 * x / (double)all->win->width - 1;
	plr->ray_dir_x = plr->dir_x + plr->plane_x * plr->camera_x;
	plr->ray_dir_y = plr->dir_y + plr->plane_y * plr->camera_x;
	plr->map_x = (int)plr->player_x;
	plr->map_y = (int)plr->player_y;
	if (plr->ray_dir_y == 0)
		plr->dlt_dist_x = 0;
	else
		plr->dlt_dist_x = (plr->ray_dir_x == 0) ? 1 : fabs(1 / plr->ray_dir_x);
	if (plr->ray_dir_x == 0)
		plr->dlt_dist_y = 0;
	else
		plr->dlt_dist_y = (plr->ray_dir_y == 0) ? 1 : fabs(1 / plr->ray_dir_y);
	all->plr->hit = 0;
	plr->perp_wall_dist = 0;
}
