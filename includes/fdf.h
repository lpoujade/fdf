/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/fdf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 20:39:45 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/10 11:18:35 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include "libft.h"

# define	SUP_PTS_NB 1000

/*
** KEYCODES (to defines)
** (key == 65363 || key == 65361 || key == 65364 || key == 65362))
** sp 32 // esc 65307
*/

typedef unsigned long	t_pixel;

typedef struct		s_coords
{
	int				x;
	int				y;
	int				z;
}					t_coords;

/*
** (t_coords)dims : x dim, y dim, z=nb pts
*/

typedef struct		s_map
{
	t_coords		*pts;
	t_coords		dims;
}					t_map;


typedef struct		s_mlx_datas
{
	void			*ident;
	void			*wndw;
	void			*next_img;
	t_pixel			*addr;
	t_map			pts;
	char			**files;
	int				dims[2];
}					t_mlx_datas;

void	quit_error(char *str, int error, void (exit_func)(void));
void	*init_img(void *con, char *filename);
void	redraw_img(t_mlx_datas *con, int dec[2]);
int		draw_lines(t_map pts, int *dims, t_pixel *addr, int dec[2]);
t_map	tr(t_map orig, int *dims);
int		line(int const *coord, int *dim, t_pixel *first);
int		parse_file(int fd, t_map *tofill);
void	show_parse(char *file);
t_map	getpts(char *filename);

#endif
