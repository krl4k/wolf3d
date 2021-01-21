/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:57:20 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/20 14:57:56 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define R_RIGHT 124
# define R_LEFT 123
# define ERROR 0
# define CORRECT 1

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}				t_data;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
}				t_vars;

typedef struct	s_pars
{
	int			res_width;
	int			res_height;
	char		*text_no;
	char		*text_so;
	char		*text_we;
	char		*text_ea;
	char		*text_spr;
	int			c_floor;
	int			c_celling;
	char		**map;
	int			map_h;
	int			map_w;
	float		f_plr_x;
	float		f_plr_y;
	int			i_plr_x;
	int			i_plr_y;
	char		dir;
	int			count_spr;
}				t_pars;

typedef struct	s_plr
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		dlt_dist_x;
	double		dlt_dist_y;
	double		perp_wall_dist;
	double		ray_dir_x;
	double		ray_dir_y;
	double		player_x;
	double		player_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			wall_side;
	double		side_dist_x;
	double		side_dist_y;
	int			draw_height;
	int			draw_start;
	int			draw_end;
	int			hit;
	double		wall_x;
	int			color;
	double		step;
	int			tex_x;
	int			tex_y;
	int			tex_width;
	int			tex_height;
	double		tex_pos;
	double		*z_buffer;

}				t_plr;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
}				t_sprite;

typedef struct	s_spritecast
{
	t_sprite	*sprites;
	int			num_sprites;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			tex_height;
	int			tex_width;
	int			sprite_height;
	int			sprite_width;
	int			draw_start_x;
	int			draw_start_y;
	int			draw_end_x;
	int			draw_end_y;
	int			stripe;
	int			tex_x;
	int			tex_y;
	int			color;
}				t_sprt_cast;

typedef struct	s_all
{
	t_vars		*win;
	t_data		*img;
	t_pars		*pars;
	t_plr		*plr;
	t_data		*no;
	t_data		*so;
	t_data		*we;
	t_data		*ea;
	t_data		*spr;
	t_sprt_cast	*spritecast;
	char		**map;
	int			current_color;
	int			screen_save;
	int			fd;
}				t_all;

int				start(int argc, char **argv);
void			game(t_all *all, int argc);
int				my_exit(void);
void			my_mlx_init(t_all *all);
void			sprites_init(t_all *all);
void			my_plr_init(t_all *all);
void			dir_init(t_all *all);
void			start_init(t_all *all, int x);
void			sprites_to_array(t_all *all);
void			sort_sprites(t_sprite *sprites, int count);
void			read_text(t_all *all);
void			draw_all0(t_all *all);
void			check_step(t_plr *plr);
void			check_hit(t_all *all, t_plr *plr);
void			paint_wall(t_all *all, int x, int y, t_plr *p);
void			paint_sprites(t_all *all);
void			my_mlx_pixel_put(t_all *all, int x, int y, int color);
int				create_rgb(int r, int g, int b);
int				key_press_l(int key, t_all *all);
void			screen_save(t_all *all);
void			my_image_init(t_all *all);
void			draw_line(t_all *all, int x, int *y, int end);

#endif
