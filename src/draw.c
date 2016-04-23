/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:12:30 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/23 12:24:48 by lpoujade         ###   ########.fr       */
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
		while (y != ey)
		{
			if (y > dim[1] || x > dim[0] || y < 0 || x < 0)
				return (1);
			pix_img((char*)first + ((x * 4) + (dim[1] * (y * 4))));
			y > ey ? y-- : y++;
		}
	else if (y == ey)
		while (x != ex)
		{
			if (y > dim[1] || x > dim[0] || y < 0 || x < 0)
				return (1);
			pix_img((char*)first + ((x * 4) + (dim[1] * (y * 4))));
			x > ex ? x-- : x++;
		}
	else if (!(y > dim[1] || x > dim[0] || y < 0 || x < 0))
		pix_img((char*)first + ((x * 4) + (dim[1] * (y * 4))));
	return (0);
}

/*
** y/x p struct : yp.x = current y; yp.y = end y; yp.z = start y
** so : xp.x = x	/ yp.x = y		(y->z inclus)
**		xp.y = xend / yp.y = yend
**		xp.z = xs	/ yp.z = ys		(start)
*/

int					line(int const *coord, int *dim, t_pixel *first)
{
	int			tmp;
	t_coords	xp;
	t_coords	yp;

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
		if (vh_lines(coord, dim, first))
			return (1);
	while (xp.x <= xp.y && !(yp.x == yp.y || xp.x == xp.y))
	{
		if (yp.x > dim[1] || xp.x > dim[0] || yp.x < 0 || xp.x < 0)
			return (1);
		pix_img((char*)first + ((xp.x * 4) + (dim[1] * (yp.x * 4))));
		yp.x = yp.z + ((yp.y - yp.z) * (xp.x - xp.z)) / (xp.y - xp.z);
		xp.x++;
	}
	return (0);
}

static inline int	tr(int a, int amax, int bmax)
{
	unsigned int b;

	ft_putstr("translating "); ft_putnbr(a);
	b = (((10000 * a) / amax) * bmax) / 10000;
	ft_putendl(ft_strjoin(" to ", ft_itoa(b)));
	return (b);
}

void				*draw_img(void *img, char *filename, int *dims)
{
	int		bpp;
	int		size_line;
	int		endianess;
	char	*addr;
	int		coord[4];
	t_map	pts;
	int		size;
	int		c = 0;

	pts.dims.z = 100000;
	ft_putendl("MLX -- mlx_get_data_addr");
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endianess);
	ft_putstr("PARSING -- ");
	ft_putendl(filename);
	if ((size = parse_file(filename, &pts)) < 0)
	{
		if (errno)
			perror("fdf: parsing: ");
		exit(13);
	}
	ft_putendl("PARSING -- parsed\n\nDRAWING --");
	while (c + 1 < pts.dims.z)
	{
		coord[0] = tr(pts.pts[c].x, pts.dims.x, dims[0]);
		coord[1] = tr(pts.pts[c].y, pts.dims.y, dims[1]);
		coord[2] = tr(pts.pts[c + 1].x, pts.dims.x, dims[0]);
		coord[3] = tr(pts.pts[c + 1].y, pts.dims.y, dims[1]);

		if (coord[3] == coord[1])
		{
			ft_putstr("H line ("); ft_putnbr(coord[0]); ft_putchar(';');
			ft_putnbr(coord[1]); ft_putstr(") to ("); ft_putnbr(coord[2]); ft_putchar(';');
			ft_putnbr(coord[3]); ft_putstr(")\n");
			if (line(coord, dims, (t_pixel*)addr))
				ft_putendl("out of screen");
		}
		if (pts.pts[c].y + 1 < pts.dims.y)
		{
			coord[2] = tr(pts.pts[c].x, pts.dims.x, dims[0]);
			coord[3] = tr(pts.pts[c].y + 1, pts.dims.y, dims[1]);
			if (line(coord, dims, (t_pixel*)addr))
				ft_putendl("out of screen");

		ft_putstr("V line ("); ft_putnbr(coord[0]); ft_putchar(';');
		ft_putnbr(coord[1]); ft_putstr(") to ("); ft_putnbr(coord[2]); ft_putchar(';');
		ft_putnbr(coord[3]); ft_putstr(")\n");

		}
		c++;
	}
	ft_putendl("DRAWING -- OK");
	return (img);
}
