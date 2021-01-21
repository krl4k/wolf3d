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

static int	res_w_h(char *s, int len)
{
	int		nbr;
	char	*str;
	int		i;

	str = s;
	i = 0;
	if (len > 6)
		return (10000);
	while (str[i] == '0')
		i++;
	nbr = ft_atoi(s);
	if (nbr == 0)
		error_handler(MAP_PARS, 1);
	return (nbr);
}

void		skip_space(char **s)
{
	while (**s == ' ' && **s)
		(*s)++;
}

static int	lennbr(char *s)
{
	int len;

	len = 0;
	while (ft_isdigit(s[len]))
		len++;
	return (len);
}

static void	check_valid_res(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s) && *s != ' ')
			error_handler(MAP_PARS, 1);
		s++;
	}
}

void		pars_resolution(char *s, t_pars *pars, int len)
{
	check_valid_res(s);
	if (pars->res_height != -1 && pars->res_width != -1)
		error_handler(MAP_PARS, 1);
	skip_space(&s);
	len = lennbr(&s[len]);
	if (len < 7)
	{
		if (ft_isdigit(*s))
			pars->res_width = res_w_h(s, len);
	}
	else
		pars->res_width = 10000;
	while (ft_isdigit(*s))
		s++;
	skip_space(&s);
	len = lennbr(s);
	if (len < 7)
	{
		if (ft_isdigit(*s))
			pars->res_height = res_w_h(s, len);
	}
	else
		pars->res_height = 10000;
	if (s[len] != '\0')
		error_handler(MAP_PARS, 1);
}
