/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:38:00 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/19 14:38:02 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_step(t_plr *plr)
{
	if (plr->ray_dir_x < 0)
	{
		plr->step_x = -1;
		plr->side_dist_x = (plr->player_x - plr->map_x) * plr->dlt_dist_x;
	}
	else
	{
		plr->step_x = 1;
		plr->side_dist_x = (plr->map_x + 1.0 - plr->player_x) * plr->dlt_dist_x;
	}
	if (plr->ray_dir_y < 0)
	{
		plr->step_y = -1;
		plr->side_dist_y = (plr->player_y - plr->map_y) * plr->dlt_dist_y;
	}
	else
	{
		plr->step_y = 1;
		plr->side_dist_y = (plr->map_y + 1.0 - plr->player_y) * plr->dlt_dist_y;
	}
}

void		check_hit(t_all *all, t_plr *p)
{
	while (p->hit == 0)
	{
		if (p->side_dist_x < p->side_dist_y)
		{
			p->side_dist_x += p->dlt_dist_x;
			p->map_x += p->step_x;
			p->wall_side = 0;
		}
		else
		{
			p->side_dist_y += p->dlt_dist_y;
			p->map_y += p->step_y;
			p->wall_side = 1;
		}
		if (all->map[p->map_x][p->map_y] == '1')
			p->hit = 1;
	}
	if (p->wall_side == 0)
		p->perp_wall_dist = (p->map_x - p->player_x + (1 - p->step_x) / 2) /
				p->ray_dir_x;
	else
		p->perp_wall_dist = (p->map_y - p->player_y + (1 - p->step_y) / 2) /
				p->ray_dir_y;
}

void		check_textures2(t_all *all, t_plr *p)
{
	p->draw_height = (int)(all->win->height / p->perp_wall_dist);
	p->draw_start = -p->draw_height / 2 + all->win->height / 2;
	p->tex_width = 64;
	p->tex_height = 64;
	if (p->draw_start < 0)
		p->draw_start = 0;
	p->draw_end = p->draw_height / 2 + all->win->height / 2;
	if (p->draw_end >= all->win->height)
		p->draw_end = all->win->height - 1;
	if (p->wall_side == 0)
		p->wall_x = p->player_y + p->perp_wall_dist * p->ray_dir_y;
	else
		p->wall_x = p->player_x + p->perp_wall_dist * p->ray_dir_x;
	p->wall_x -= floor((p->wall_x));
	p->tex_x = (int)(p->wall_x * (double)(p->tex_width));
	if (p->wall_side == 0 && p->ray_dir_x > 0)
		p->tex_x = p->tex_width - p->tex_x - 1;
	if (p->wall_side == 1 && p->ray_dir_y < 0)
		p->tex_x = p->tex_width - p->tex_x - 1;
	p->step = 1.0 * p->tex_height / p->draw_height;
	p->tex_pos = (p->draw_start - all->win->height / 2 + p->draw_height / 2) *
			p->step;
}

void		draw_line(t_all *all, int x, int *y, int end)
{
	while ((*y) < end)
	{
		my_mlx_pixel_put(all, x, *y, all->current_color);
		(*y)++;
	}
}

/*
** y variable  always = 0
*/

void		paint_wall(t_all *all, int x, int y, t_plr *p)
{
	check_textures2(all, all->plr);
	all->current_color = all->pars->c_celling;
	draw_line(all, x, &y, p->draw_start);
	while (y < p->draw_end)
	{
		p->tex_y = (int)p->tex_pos & (p->tex_height - 1);
		p->tex_pos += p->step;
		if (p->wall_side == 0 && (p->ray_dir_x < 0))
			p->color = (*(int *)(all->so->addr + ((p->tex_x + (p->tex_y *
		all->so->width)) * (all->so->bits_per_pixel / 8))));
		if (p->wall_side == 0 && (p->ray_dir_x > 0))
			p->color = (*(int *)(all->ea->addr + ((p->tex_x + (p->tex_y *
		all->ea->width)) * (all->ea->bits_per_pixel / 8))));
		if (p->wall_side == 1 && (p->ray_dir_y < 0))
			p->color = (*(int *)(all->no->addr + ((p->tex_x + (p->tex_y *
		all->no->width)) * (all->no->bits_per_pixel / 8))));
		else if (p->wall_side == 1 && (p->ray_dir_y > 0))
			p->color = (*(int *)(all->we->addr + ((p->tex_x + (p->tex_y *
		all->we->width)) * (all->we->bits_per_pixel / 8))));
		my_mlx_pixel_put(all, x, y, p->color);
		y++;
	}
	all->current_color = all->pars->c_floor;
	draw_line(all, x, &y, all->win->height);
	all->plr->z_buffer[x] = all->plr->perp_wall_dist;
}
