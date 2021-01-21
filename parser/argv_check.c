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

static int	num_of_argc(int argc)
{
	if (argc < 2)
	{
		write(2, "ERROR: submit the map!\n", 24);
		return (ERROR);
	}
	if (argc > 3)
	{
		write(2, "ERROR: a lot of arguments!\n", 28);
		return (ERROR);
	}
	return (CORRECT);
}

static int	check_first(char *map)
{
	char *permission;

	if (!map)
		return (ERROR);
	if (ft_strlen(map) < 5)
		return (ERROR);
	if (!(permission = ft_strchr(map, '.')))
		return (ERROR);
	if (ft_strlen(++permission) > 3)
		return (ERROR);
	if (ft_strncmp("cub", permission, 3) == 0)
		return (CORRECT);
	return (ERROR);
}

int			argv_check(int argc, char **argv)
{
	if (num_of_argc(argc) == ERROR)
		return (ERROR);
	if (argc > 1)
	{
		if (check_first(argv[1]) == ERROR)
			error_handler(ARGV_ERROR, 0);
		if (argc == 3)
		{
			if ((ft_strlen(argv[2]) != 6))
				error_handler(ARGV_ERROR, 1);
			if (ft_strncmp("--save", argv[2], 6) != 0)
				error_handler(ARGV_ERROR, 1);
		}
	}
	return (CORRECT);
}
