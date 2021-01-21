/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:50:10 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/24 13:50:17 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	check_type(t_pars *pars, int type)
{
	if (type == 1)
		if (pars->c_floor != -1)
			error_handler(MAP_PARS, 3);
	if (type == 2)
		if (pars->c_celling != -1)
			error_handler(MAP_PARS, 3);
}

int			len_nbr(char *s)
{
	int len;

	len = 0;
	while (ft_isdigit(s[len]))
		len++;
	if (len == 3)
	{
		if (ft_atoi(s) > 255)
			error_handler(MAP_PARS, 4);
	}
	if (len > 3)
		error_handler(MAP_PARS, 4);
	return (len);
}

int			check_count_int_word(char **s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (s[i])
	{
		tmp = s[i];
		while (*tmp)
		{
			if (ft_isdigit(*tmp) == 0)
				error_handler(MAP_PARS, 4);
			tmp++;
		}
		i++;
	}
	return (i);
}

void		check_rgb(char **rgb)
{
	int i;

	i = 0;
	if (check_count_int_word(rgb) == 3)
	{
		while (rgb[i])
		{
			len_nbr(rgb[i]);
			i++;
		}
	}
	else
		error_handler(MAP_PARS, 4);
}

void		pars_color(char *s, t_pars *pars, int type)
{
	char	**rgb;
	int		i;

	i = 0;
	rgb = NULL;
	check_type(pars, type);
	skip_space(&s);
	rgb = ft_split(s, ',');
	check_rgb(rgb);
	if (type == 1)
		pars->c_floor = create_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]),
							ft_atoi(rgb[2]));
	if (type == 2)
		pars->c_celling = create_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]),
									ft_atoi(rgb[2]));
	while (i < 3)
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}
