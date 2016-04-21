/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/fdf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 20:39:45 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/21 16:52:36 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include "libft.h"

typedef struct		s_mlx_datas
{
	void			*ident;
	void			*wndw;
	void			*next_img;
	char			*file;
	int				dims[2];
}					t_mlx_datas;

typedef struct		s_coords
{
	int				x;
	int				y;
	int				z;
}					t_coords;

/*
** (t_coords)dims : x=dim, y=dim, z=nb pts
*/

typedef struct		s_map
{
	t_coords		*pts;
	t_coords		dims;
}					t_map;

typedef unsigned long	t_pixel;

void	*draw_img(void *img, char *filename, int *dims);
int		parse_file(char *file, t_map *tofill);
void	show_parse(char *file);

#endif
