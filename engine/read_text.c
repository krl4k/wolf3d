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

#include <parser.h>

void		load_image(t_data *texture, t_all *all, char *filename)
{
	if (!texture)
		error_handler(MAP_PARS, 0);
	if ((texture->img = mlx_xpm_file_to_image(all->win->mlx, filename,
		&texture->width,
		&texture->height)))
		texture->addr = (char *)mlx_get_data_addr(texture->img,
		&texture->bits_per_pixel,
		&texture->line_length,
		&texture->endian);
	else
		error_handler(MLX_ERROR, -1);
	free(filename);
}

void		read_text(t_all *all)
{
	int x;

	x = 1;
	if (!((all->so = (t_data *)malloc(x * sizeof(t_data))) &&
		(all->no = (t_data *)malloc(x * sizeof(t_data))) &&
		(all->we = (t_data *)malloc(x * sizeof(t_data))) &&
		(all->ea = (t_data *)malloc(x * sizeof(t_data))) &&
		(all->spr = (t_data *)malloc(x * sizeof(t_data)))))
	{
		error_handler(MAP_PARS, 0);
	}
	load_image((all->so), all, all->pars->text_so);
	load_image((all->no), all, all->pars->text_no);
	load_image((all->we), all, all->pars->text_we);
	load_image((all->ea), all, all->pars->text_ea);
	load_image((all->spr), all, all->pars->text_spr);
}
