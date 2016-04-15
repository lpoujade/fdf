/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:12:30 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/15 17:03:43 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	pix_img(char *addr)
{
	*addr = 0xff;
	*(addr + 1) = 0xff;
	*(addr + 2) = 0xff;
	*(addr + 3) = 0;
}

static inline int	vh_lines(int const *coord, int *dim, t_pixel *first)
{
	int	x;
	int	y;
	int	ey;
	int	ex;

	x = coord[0];
	y = coord[1];
	ex = coord[2];
	ey = coord[3];
	if (x == ex)
		while (y != ey && y > 0)
		{
			if (y > dim[1] || x > dim[0] || y < 1 || x < 1)
				return (1);
			pix_img((char*)first + ((x*4) + (dim[1] * (y * 4))));
			y > ey ? y-- : y++;
		}
	else if (y == ey)
		while (x != ex && x > 0)
		{
			if (y > dim[1] || x > dim[0])
				return (1);
			pix_img((char*)first + ((x*4) + (dim[1] * (y * 4))));
			x > ex ? x-- : x++;
		}
	return (0);
}

/*
** y/x p struct : yp.x = current y; yp.y = end y; yp.z = start y
** so : xp.x = x 	/ yp.x = y		(y->z inclus)
** 		xp.y = xend / yp.y = yend
**		xp.z = xs	/ yp.z = ys 	(start)
*/

int					line(int const *coord, int *dim, t_pixel *first)
{
	int tmp;
	t_coords xp;
	t_coords yp;

	xp.x = coord[0];
	yp.x = coord[1];
	xp.y = coord[2];
	yp.y = coord[3];
	if (xp.x > xp.y)
	{
		tmp = xp.x;
		xp.x = xp.y;
		xp.y = tmp;
		tmp = yp.x;
		yp.x = yp.y;
	 	yp.y = tmp;
	}
	yp.z = yp.x;
	xp.z = xp.x;
	if (yp.x == yp.y || xp.x == xp.y)
	{
		if (vh_lines(coord, dim, first))
			return (1);
	}
	else
		while (xp.x <= xp.y && yp.x != yp.y)
		{
			pix_img((char*)first + ((xp.x * 4) + (dim[1] * (yp.x * 4))));			// 4 -> mlx bpp
			yp.x = yp.z + ((yp.y - yp.z) * (xp.x - xp.z))/(xp.y - xp.z);
			xp.x++;
			if (xp.x > dim[0] || yp.x > dim[1])
				return (1);
			if (xp.x == xp.y && yp.x == yp.y)
				break ;
		}
	return (0);
}

void				*draw_img(void *img, char *filename)
{
	int		bpp, size_line, endianess;
	char	*addr;
	int		coord[4];
	t_coords *pts;
	int		size, c = 0;
	int		dim[2] = {800, 800};

	ft_putendl("MLX -- mlx_get_data_addr");
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endianess);

	ft_putstr("PARSING -- start with "); ft_putendl(filename);
	if ((size = parse_file(filename, &pts)) < 0)
		exit (12);
	ft_putendl("PARSING -- parsed");

	while (c < size)
	{
		coord[0] = pts[c].x * 10;
		coord[1] = pts[c].y * 10;
		coord[2] = (c + 1 < size ? (pts[c + 1].x * 10) : coord[0]);
		coord[3] = (c + 1 < size ? (pts[c + 1].y * 10) : coord[1]);
		if (line(coord, dim, (t_pixel*)addr))
			ft_putendl("out of screen");
		c++;
	}
	/*
	ft_putstr("x : ");
	get_next_line(0, &lne);
	coord[2] = ft_atoi(lne);
	ft_putstr("y : ");
	get_next_line(0, &lne);
	coord[3] = ft_atoi(lne);
	if (line(coord, dim, (t_pixel*)addr))
		ft_putendl("out of screen");
		*/
	return (img);
}

