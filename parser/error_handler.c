/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:10 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/24 13:50:17 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	map_pars_error(int code)
{
	if (code == -1)
		write(2, "ERROR:\nminilibx error!\n", 23);
	if (code == 0)
		write(2, "ERROR:\nmalloc is incorrect!\n", 28);
	else if (code == 1)
		write(2, "ERROR:\nresolution is incorrect!\n", 33);
	else if (code == 2)
		write(2, "ERROR:\npath to file or extension is not correct!\n", 49);
	else if (code == 3)
		write(2, "ERROR:\nduplicate data!\n", 23);
	else if (code == 4)
		write(2, "ERROR:\nwrong color!\n", 20);
	else if (code == 5)
		write(2, "ERROR:\ntrash in file\n", 21);
	else if (code == 6)
		write(2, "ERROR:\nspaces in map\n", 21);
	else if (code == 7)
		write(2, "ERROR:\ninsufficient data\n", 25);
	else if (code == 8)
		write(2, "ERROR:\nplayer not found\n", 24);
	else
		;
}

void		error_handler(int type_error, int error_code)
{
	if (type_error == OPEN)
		write(2, "ERROR:\nopening error!\n", 24);
	if (type_error == READ)
		write(2, "ERROR:\nreading error!\n", 24);
	if (type_error == MAP_PARS)
		map_pars_error(error_code);
	if (type_error == MLX_ERROR)
		write(2, "ERROR:\nmlx_lib error!\n", 22);
	if (type_error == ARGV_ERROR && error_code == 0)
		write(2, "ERROR:\nargv error!\n", 20);
	if (type_error == ARGV_ERROR && error_code == 1)
		write(2, "ERROR: invalid third argument\n", 31);
	exit(2);
}
