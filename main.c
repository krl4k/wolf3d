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

int		start(int argc, char **argv)
{
	t_all *all;

	if (!(all = ft_parser_all(argv[1])))
		error_handler(MAP_PARS, 0);
	if (argc == 3)
		screen_save(all);
	my_mlx_init(all);
	read_text(all);
	if (!(all->win->win = mlx_new_window(all->win->mlx, all->win->width,
		all->win->height, "cub3D")))
		error_handler(MLX_ERROR, 0);
	my_image_init(all);
	game(all, argc);
	mlx_hook(all->win->win, 17, (1L << 0), &my_exit, all);
	mlx_hook(all->win->win, 2, (1L << 0), &key_press_l, all);
	mlx_loop(all->win->mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argv_check(argc, argv) == ERROR)
		error_handler(ARGV_ERROR, 0);
	if (start(argc, argv) == ERROR)
		return (0);
}
