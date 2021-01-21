/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:38:00 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/19 14:38:02 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

/*
** static unsigned char infoHeader[] = {
**		0, 0, 0, 0, /// header size
**		0, 0, 0, 0, /// image width
**		0, 0, 0, 0, /// image height
**		0, 0,     /// number of color planes
**		0, 0,     /// bits per pixel
**		0, 0, 0, 0, /// compression
**		0, 0, 0, 0, /// image size
**		0, 0, 0, 0, /// horizontal resolution
**		0, 0, 0, 0, /// vertical resolution
**		0, 0, 0, 0, /// colors in color table
**		0, 0, 0, 0, /// important color count
**
** };
*/

static void	init(t_all *all)
{
	my_mlx_init(all);
	if (!(all->win->win = mlx_new_window(all->win->mlx, all->win->width,
	all->win->height, "cub3D")))
		error_handler(MAP_PARS, 0);
	my_image_init(all);
	my_plr_init(all);
	sprites_init(all);
	read_text(all);
	draw_all0(all);
}

void		create_file_header(t_all *all, int fd)
{
	unsigned char	*file_header;
	int				i;
	int				file_size;

	file_header = (unsigned char *)malloc(14 * sizeof(unsigned char));
	i = 0;
	while (i < 14)
	{
		file_header[i] = (unsigned char)(0);
		i++;
	}
	file_size = 14 + 40 + (4 * all->win->width * all->win->height);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size % 256);
	file_header[3] = (unsigned char)(file_size / 256 % 256);
	file_header[4] = (unsigned char)(file_size / 256 / 256 % 256);
	file_header[5] = (unsigned char)(file_size / 256 / 256 / 256);
	file_header[10] = (unsigned char)(14 + 40);
	write(fd, file_header, 14);
	free(file_header);
}

void		create_info_header(t_all *all, int fd)
{
	int				i;
	unsigned char	*file_header;

	i = 0;
	file_header = (unsigned char *)malloc(40 * sizeof(unsigned char));
	while (i < 40)
	{
		file_header[i] = (unsigned char)(0);
		i++;
	}
	file_header[0] = (unsigned char)(40);
	file_header[4] = (unsigned char)(all->win->width % 256);
	file_header[5] = (unsigned char)(all->win->width / 256 % 256);
	file_header[6] = (unsigned char)(all->win->width / 256 / 256 % 256);
	file_header[7] = (unsigned char)(all->win->width / 256 / 256 / 256);
	file_header[8] = (unsigned char)(all->win->height % 256);
	file_header[9] = (unsigned char)(all->win->height / 256 % 256);
	file_header[10] = (unsigned char)(all->win->height / 256 / 256 % 256);
	file_header[11] = (unsigned char)(all->win->height / 256 / 256 / 256);
	file_header[12] = (unsigned char)(1);
	file_header[14] = (unsigned char)(32);
	write(fd, file_header, 40);
	free(file_header);
}

void		create_image_to_file(t_all *all)
{
	int y;
	int line_length;

	line_length = all->win->width * all->img->bits_per_pixel / 8;
	y = all->win->height;
	while (0 <= y)
	{
		write(all->fd, (unsigned char *)(all->img->addr +
		y * all->img->line_length), line_length);
		y--;
	}
}

void		screen_save(t_all *all)
{
	all->fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0655);
	init(all);
	create_file_header(all, all->fd);
	create_info_header(all, all->fd);
	create_image_to_file(all);
	close(all->fd);
	write(1, "Image generate!\n", 17);
	my_exit();
}
