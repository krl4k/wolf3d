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

static void	check_sides(t_pars *pars, int side)
{
	if (side == 1)
		if (pars->text_no != NULL)
			error_handler(MAP_PARS, 3);
	if (side == 2)
		if (pars->text_so != NULL)
			error_handler(MAP_PARS, 3);
	if (side == 3)
		if (pars->text_we != NULL)
			error_handler(MAP_PARS, 3);
	if (side == 4)
		if (pars->text_ea != NULL)
			error_handler(MAP_PARS, 3);
	if (side == 6)
		if (pars->text_spr != NULL)
			error_handler(MAP_PARS, 3);
}

static void	check_xpm(char *s)
{
	int len;

	len = 0;
	while (s[len] && s[len] != ' ')
		len++;
	if (len < 5)
		error_handler(MAP_PARS, 2);
	if (ft_strncmp(".xpm", &s[len - 4], 4) != 0)
		error_handler(MAP_PARS, 2);
}

void		check_trash(char *s)
{
	while (*s)
	{
		if (*s != ' ')
		{
			error_handler(MAP_PARS, 5);
		}
		s++;
	}
}

void		pars_textures(char *s, t_pars *pars, int side)
{
	int len;

	len = 0;
	check_sides(pars, side);
	skip_space(&s);
	check_xpm(s);
	while (s[len] && s[len] != ' ')
		len++;
	if (s[len] != '\0')
		error_handler(MAP_PARS, 5);
	if (side == 1)
		pars->text_no = ft_substr(s, 0, len);
	else if (side == 2)
		pars->text_so = ft_substr(s, 0, len);
	else if (side == 3)
		pars->text_we = ft_substr(s, 0, len);
	else if (side == 4)
		pars->text_ea = ft_substr(s, 0, len);
	else if (side == 6)
		pars->text_spr = ft_substr(s, 0, len);
}
