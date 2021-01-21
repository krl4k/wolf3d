/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:38:00 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/19 14:38:02 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include "cub3d.h"

int		struct_is_full(t_pars *pars)
{
	return (pars->res_width != -1 && pars->res_height != -1 &&
	pars->text_no != NULL && pars->text_so != NULL &&
	pars->text_we != NULL && pars->text_ea != NULL &&
	pars->text_spr != NULL && pars->c_floor != -1 &&
	pars->c_celling != -1);
}

void	ft_all_init(t_pars *pars)
{
	pars->res_width = -1;
	pars->res_height = -1;
	pars->text_no = NULL;
	pars->text_so = NULL;
	pars->text_we = NULL;
	pars->text_ea = NULL;
	pars->text_spr = NULL;
	pars->c_floor = -1;
	pars->c_celling = -1;
	pars->dir = '\0';
}

t_all	*ft_parser_all(char *filename)
{
	int		fd;
	t_list	*file;
	t_all	*all;

	if (!(all = (t_all *)malloc(sizeof(t_all))))
		error_handler(MAP_PARS, 0);
	if ((fd = open_file(filename)) < 0)
		error_handler(OPEN, 0);
	if (!(file = read_file(fd)))
		error_handler(READ, 0);
	if (!(all->pars = pars_file(&file)))
		error_handler(MAP_PARS, 0);
	return (all);
}
