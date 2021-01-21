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

int		str_is_empty(char *line)
{
	if (!*line)
		return (1);
	while (*line)
	{
		if (*line != ' ')
			return (0);
		line++;
	}
	return (0);
}

void	check_trash_after_map(t_list *map)
{
	int count;

	count = 0;
	if (map)
	{
		while (map)
		{
			map = map->next;
			count++;
		}
	}
	else
		return ;
	if (count > 1 || count == 0)
		error_handler(MAP_PARS, 5);
}

void	map_map(t_pars *pars, t_list *tmp, int i)
{
	t_list *map_list;

	map_list = tmp;
	pars->map_h = 0;
	while (tmp)
	{
		if (tmp->content)
		{
			tmp = tmp->next;
			pars->map_h++;
			if (!tmp || str_is_empty(tmp->content))
				break ;
		}
		else
			break ;
	}
	check_trash_after_map(tmp);
	pars->map = (char **)ft_calloc(pars->map_h + 1, sizeof(char*));
	while (map_list)
	{
		pars->map[i] = ft_strdup(map_list->content);
		map_list = map_list->next;
		i++;
	}
}

void	start_pars_map(t_list *tmp, t_pars *pars)
{
	tmp = skip_empty(tmp);
	map_map(pars, tmp, 0);
	check_valid(pars, 0, 0, '\0');
	check_bound(pars);
	find_plr(pars->map, pars, 0);
	flood(pars);
	find_sprites(pars);
	to_zero(pars);
}
