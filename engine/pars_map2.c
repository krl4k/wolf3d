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

/*
** i = 0;
** j = 0;
*/

void	check_valid(t_pars *p, int i, int j, char dir_plr)
{
	dir_plr = '\0';
	if (!p->map)
		error_handler(MAP_PARS, 5);
	while (p->map[i] && i < p->map_h)
	{
		j = 0;
		while (p->map[i][j])
		{
			if (ft_strchr(" WSEN012", p->map[i][j]) == NULL)
				error_handler(MAP_PARS, 5);
			else if (p->map[i][j] == 'W' || p->map[i][j] == 'S' ||
			p->map[i][j] == 'E' || p->map[i][j] == 'N')
			{
				if (dir_plr == '\0')
					dir_plr = p->map[i][j];
				else
					error_handler(MAP_PARS, 3);
			}
			j++;
		}
		i++;
	}
	if (dir_plr == '\0')
		error_handler(MAP_PARS, 8);
}

void	first_last(t_pars *pars, int i)
{
	while (pars->map[0][i])
		if (pars->map[0][i] == '1' || pars->map[0][i] == ' ')
			i++;
		else
			error_handler(MAP_PARS, 5);
	i = 0;
	while (pars->map[pars->map_h - 1][i])
		if (pars->map[pars->map_h - 1][i] == ' ' ||
			pars->map[pars->map_h - 1][i] == '1')
		{
			i++;
		}
		else
			error_handler(MAP_PARS, 5);
}

void	check_bound(t_pars *pars)
{
	int i;

	i = 0;
	first_last(pars, i);
	while (pars->map[i][0] && i < pars->map_h - 1)
		if (pars->map[i][0] == ' ' || pars->map[i][0] == '1')
			i++;
		else
			error_handler(MAP_PARS, 5);
	i = 0;
	while (pars->map[i] && i < pars->map_h)
		if (pars->map[i][ft_strlen(pars->map[i]) - 1] == ' ' ||
			pars->map[i][ft_strlen(pars->map[i]) - 1] == '1')
			i++;
		else
			error_handler(MAP_PARS, 5);
}

void	to_zero(t_pars *pars)
{
	int i;
	int j;

	i = 0;
	while (pars->map[i] && i < pars->map_h - 1)
	{
		j = 0;
		while (pars->map[i][j])
		{
			if (pars->map[i][j] == '*')
				pars->map[i][j] = '0';
			j++;
		}
		i++;
	}
}

void	flood(t_pars *pars)
{
	int		i;
	int		j;
	char	**new_map;

	i = 1;
	max_width_map(pars);
	new_map = copy_map(pars);
	while (new_map[i] && i < pars->map_h + 2)
	{
		j = 0;
		while (new_map[i][j])
		{
			if (new_map[i][j] == '0' || new_map[i][j] == '2')
				flood_fill(new_map, pars, j, i);
			j++;
		}
		i++;
	}
	free_new_map(pars, new_map);
}
