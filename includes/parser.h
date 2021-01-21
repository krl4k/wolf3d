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

#ifndef PARSER_H
# define PARSER_H
# include "cub3d.h"
# define OPEN 666
# define READ 777
# define MAP_PARS 888
# define MLX_ERROR 999
# define ARGV_ERROR 88

int		argv_check(int argc, char **argv);
t_all	*ft_parser_all(char *filename);
int		open_file(char *filename);
t_list	*read_file(int fd);
t_pars	*pars_file(t_list **file);
t_pars	*pars_lines(t_list **head);
void	ft_all_init(t_pars *pars);
int		struct_is_full(t_pars *pars);
void	skip_space(char **s);
void	pars_resolution(char *s, t_pars *pars, int len);
void	pars_textures(char *s, t_pars *pars, int side);
void	pars_color(char *s, t_pars *pars, int type);
void	check_trash(char *s);
void	start_pars_map(t_list *tmp, t_pars *pars);
void	load_image(t_data *texture, t_all *all, char *filename);
void	error_handler(int type_error, int error_code);
void	to_zero(t_pars *pars);
void	map_map(t_pars *pars, t_list *tmp, int i);
void	check_bound(t_pars *pars);
void	max_width_map(t_pars *p);
char	**copy_map(t_pars *pars);
void	free_new_map(t_pars *pars, char **new_map);
t_list	*skip_empty(t_list *list);
void	find_plr(char **map, t_pars *pars, int i);
void	find_sprites(t_pars *pars);
void	check_valid(t_pars *p, int i, int j, char dir_plr);
void	flood(t_pars *pars);
void	flood_fill(char **map, t_pars *pars, int x, int y);

#endif
