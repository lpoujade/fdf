/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/fdf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 20:39:45 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/19 11:34:30 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
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

typedef unsigned long	t_pixel;

void	*draw_img(void *img, char *filename, int *dims);
int		parse_file(char *file, t_coords **tab);

#endif
