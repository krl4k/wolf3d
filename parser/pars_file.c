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

void	check_identifier(char *line, t_pars *pars)
{
	if (line)
	{
		if (ft_strncmp("R ", line, 2) == 0)
			pars_resolution(line + 2, pars, 0);
		else if (ft_strncmp("NO ", line, 3) == 0)
			pars_textures(line + 3, pars, 1);
		else if (ft_strncmp("SO ", line, 3) == 0)
			pars_textures(line + 3, pars, 2);
		else if (ft_strncmp("WE ", line, 3) == 0)
			pars_textures(line + 3, pars, 3);
		else if (ft_strncmp("EA ", line, 3) == 0)
			pars_textures(line + 3, pars, 4);
		else if (ft_strncmp("S ", line, 2) == 0)
			pars_textures(line + 2, pars, 6);
		else if (ft_strncmp("F ", line, 2) == 0)
			pars_color(line + 2, pars, 1);
		else if (ft_strncmp("C ", line, 2) == 0)
			pars_color(line + 2, pars, 2);
		else
			check_trash(line);
	}
}

int		pars_line(char *s, t_pars *pars)
{
	if (!struct_is_full(pars))
		check_identifier(s, pars);
	else
		return (1);
	return (0);
}

t_pars	*pars_lines(t_list **head)
{
	t_pars *pars;
	t_list *tmp;

	tmp = *head;
	if (!(pars = (t_pars *)malloc(sizeof(t_pars))))
		error_handler(MAP_PARS, 0);
	ft_all_init(pars);
	while (tmp)
	{
		if (pars_line(tmp->content, pars) == 0)
			tmp = tmp->next;
		else
			break ;
	}
	if (!struct_is_full(pars))
	{
		ft_lstclear(head, ft_lstfree_cont);
		error_handler(MAP_PARS, 7);
	}
	start_pars_map(tmp, pars);
	return (pars);
}

t_pars	*pars_file(t_list **file)
{
	t_pars *pars;

	pars = pars_lines(file);
	ft_lstclear(file, ft_lstfree_cont);
	return (pars);
}
