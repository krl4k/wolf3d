/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:10 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/24 13:50:17 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

static void	right(t_all *all)
{
	double old_dir_x;
	double old_plane_x;
	double speed;

	speed = 0.1;
	old_dir_x = all->plr->dir_x;
	all->plr->dir_x = all->plr->dir_x * cos(speed) -
	all->plr->dir_y * sin(speed);
	all->plr->dir_y =
			old_dir_x * sin(speed) + all->plr->dir_y * cos(speed);
	old_plane_x = all->plr->plane_x;
	all->plr->plane_x = all->plr->plane_x * cos(speed) -
	all->plr->plane_y * sin(speed);
	all->plr->plane_y = old_plane_x * sin(speed) + all->plr->plane_y
			* cos(speed);
}

void		rotate(t_all *all, int key)
{
	double old_dir_x;
	double old_plane_x;
	double speed;

	speed = 0.1;
	if (key == R_RIGHT)
	{
		old_dir_x = all->plr->dir_x;
		all->plr->dir_x = all->plr->dir_x * cos(-speed) -
			all->plr->dir_y * sin(-speed);
		all->plr->dir_y =
			old_dir_x * sin(-speed) + all->plr->dir_y * cos(-speed);
		old_plane_x = all->plr->plane_x;
		all->plr->plane_x = all->plr->plane_x * cos(-speed) -
			all->plr->plane_y * sin(-speed);
		all->plr->plane_y = old_plane_x * sin(-speed) +
			all->plr->plane_y * cos(-speed);
	}
	if (key == R_LEFT)
		right(all);
}

void		right_left(t_all *all, int key, double move_speed, double r)
{
	if (key == RIGHT)
	{
		if (all->map[(int)(all->plr->player_x + all->plr->dir_y * (move_speed +
		r))][(int)(all->plr->player_y)] == '0')
			all->plr->player_x += all->plr->dir_y * move_speed;
		if (all->map[(int)all->plr->player_x][(int)(all->plr->player_y -
		all->plr->dir_x * (move_speed + r))] == '0')
			all->plr->player_y -= all->plr->dir_x * move_speed;
	}
	if (key == LEFT)
	{
		if (all->map[(int)(all->plr->player_x - all->plr->dir_y * (move_speed +
		r))][(int)(all->plr->player_y)] == '0')
			all->plr->player_x -= all->plr->dir_y * move_speed;
		if (all->map[(int)all->plr->player_x][(int)(all->plr->player_y +
		all->plr->dir_x * (move_speed + r))] == '0')
			all->plr->player_y += all->plr->dir_x * move_speed;
	}
}

void		up_down(t_all *all, int key, double move_speed, double r)
{
	if (key == UP)
	{
		if (all->map[(int)(all->plr->player_x + all->plr->dir_x * (move_speed +
		r))][(int)(all->plr->player_y)] == '0')
			all->plr->player_x += all->plr->dir_x * move_speed;
		if (all->map[(int)(all->plr->player_x)][(int)(all->plr->player_y +
		all->plr->dir_y * (move_speed + r))] == '0')
			all->plr->player_y += all->plr->dir_y * move_speed;
	}
	if (key == DOWN)
	{
		if (all->map[(int)(all->plr->player_x - all->plr->dir_x * (move_speed +
		0.01))][(int)(all->plr->player_y)] == '0')
			all->plr->player_x -= all->plr->dir_x * move_speed;
		if (all->map[(int)all->plr->player_x][(int)(all->plr->player_y -
		all->plr->dir_y * (move_speed + 0.01))] == '0')
			all->plr->player_y -= all->plr->dir_y * move_speed;
	}
}

int			key_press_l(int key, t_all *all)
{
	double move_speed;
	double r;

	r = 0.3;
	move_speed = 0.15;
	if (key == UP || key == DOWN)
		up_down(all, key, move_speed, r);
	if (key == RIGHT || key == LEFT)
		right_left(all, key, move_speed, r);
	if (key == R_LEFT || key == R_RIGHT)
		rotate(all, key);
	if (key == 53)
		my_exit();
	draw_all0(all);
	return (0);
}
