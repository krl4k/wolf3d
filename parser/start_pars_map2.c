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

void	find_plr(char **map, t_pars *pars, int i)
{
	char	*dir;
	int		j;

	while (map[i])
	{
		j = 0;
		while (i < pars->map_h && map[i][j])
		{
			if ((dir = ft_strchr("NSEW", map[i][j])) != NULL)
			{
				pars->i_plr_x = j;
				pars->i_plr_y = i;
				pars->f_plr_x = j + 0.5;
				pars->f_plr_y = i + 0.5;
				map[i][j] = '0';
				if (dir != NULL && pars->dir == '\0')
					pars->dir = dir[0];
				else if (pars->dir != '\0')
					error_handler(MAP_PARS, 7);
			}
			j++;
		}
		i++;
	}
}

void	find_sprites(t_pars *pars)
{
	int i;
	int j;

	i = 0;
	pars->count_spr = 0;
	while (i < pars->map_h)
	{
		j = 0;
		while (pars->map[i][j])
		{
			if (pars->map[i][j] == '2')
				pars->count_spr++;
			j++;
		}
		i++;
	}
}

t_list	*skip_empty(t_list *list)
{
	char *s;

	while ((list))
	{
		if ((list)->content)
		{
			s = (list)->content;
			while (*s == ' ')
				s++;
			if (*s != '\0')
				break ;
		}
		(list) = (list)->next;
	}
	return (list);
}
