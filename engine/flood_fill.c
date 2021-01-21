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

void		flood_fill(char **map, t_pars *pars, int x, int y)
{
	char new_color;

	new_color = '*';
	if (x > 0 && x < pars->map_w && y > 0 && y < pars->map_h + 2 &&
		(map[y][x] == ' ' || map[y][x] == '^'))
		error_handler(MAP_PARS, 6);
	if ((x >= 0 && x < pars->map_w) && (y >= 0 && y < pars->map_h) &&
		((map[y][x] == '0' || map[y][x] == '2') && map[y][x] != new_color))
	{
		map[y][x] = new_color;
		flood_fill(map, pars, x + 1, y);
		flood_fill(map, pars, x - 1, y);
		flood_fill(map, pars, x, y + 1);
		flood_fill(map, pars, x, y - 1);
	}
}

void		max_width_map(t_pars *p)
{
	int i;
	int j;

	i = 0;
	p->map_w = 0;
	while (i < p->map_h && p->map[i])
	{
		j = 0;
		while (p->map[i][j])
			j++;
		if (p->map_w < j)
			p->map_w = j;
		i++;
	}
}

static int	copy_main_map(t_pars *pars, char **new_map, int i)
{
	int		k;
	char	new_symbol;
	int		j;

	k = 0;
	new_symbol = '^';
	while (k < pars->map_h)
	{
		new_map[i] = (char *)ft_calloc(pars->map_w + 1, sizeof(char));
		ft_strcpy(new_map[i], pars->map[k]);
		if ((int)ft_strlen(pars->map[k]) < pars->map_w)
		{
			j = ft_strlen(pars->map[k]);
			while (j < pars->map_w)
			{
				new_map[i][j] = new_symbol;
				j++;
			}
		}
		k++;
		i++;
	}
	return (i);
}

char		**copy_map(t_pars *pars)
{
	char	**new_map;
	int		i;
	char	new_symbol;

	new_symbol = '^';
	i = 0;
	new_map = (char **)ft_calloc((pars->map_h + 3), sizeof(char *));
	new_map[i] = (char *)ft_calloc(pars->map_w + 1, sizeof(char));
	ft_memset(new_map[i++], new_symbol, pars->map_w);
	i = copy_main_map(pars, new_map, i);
	new_map[i] = (char *)ft_calloc(pars->map_w + 1, sizeof(char));
	ft_memset(new_map[i], new_symbol, pars->map_w);
	return (new_map);
}

void		free_new_map(t_pars *pars, char **new_map)
{
	int l;

	l = 0;
	while (l < pars->map_h + 2)
	{
		free(new_map[l]);
		l++;
	}
	free(new_map);
}
