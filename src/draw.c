/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:12:30 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/26 22:31:40 by lpoujade         ###   ########.fr       */
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
		ft_putstr("V line ("); ft_putnbr(coord[0]); ft_putchar(';');
		ft_putnbr(coord[1]); ft_putstr(") to ("); ft_putnbr(coord[2]); ft_putchar(';');
		ft_putnbr(coord[3]); ft_putstr(")\n");
	while (y != ey || x != ex)
	{
		if (y > dim[1] || x > dim[0] || y < 0 || x < 0)
			return (1);
		pix_img((char*)first + ((x * 4) + (dim[1] * (y * 4))));
		if (x == ex)
			y > ey ? y-- : y++;
		else
			x > ex ? x-- : x++;
	}
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
	t_coords	xp;
	t_coords	yp;
	int		w;

	xp.x = coord[0];
	yp.x = coord[1];
	xp.y = coord[2];
	yp.y = coord[3];
	if (xp.x > xp.y)
	{
		ft_iswap(&xp.x, &xp.y);
		ft_iswap(&yp.x, &yp.y);
	}
	yp.z = yp.x;
	xp.z = xp.x;
	w = ft_abs(yp.z - yp.y) > (unsigned int)(xp.y - xp.z) ? 0 : 1;
	if (yp.x == yp.y || xp.x == xp.y)
	{
		if (vh_lines(coord, dim, first))
			return (1);
	}
	else
	{
		ft_putstr("H line ("); ft_putnbr(coord[0]); ft_putchar(';');
		ft_putnbr(coord[1]); ft_putstr(") to ("); ft_putnbr(coord[2]); ft_putchar(';');
		ft_putnbr(coord[3]); ft_putstr(")\n");
	}
	while ((w && yp.x < yp.y) || (!w && xp.x < xp.y))
	{
		if (yp.x > dim[1] || xp.x > dim[0] || yp.x < 0 || xp.x < 0)
			return (1);
		if (w)
		{
		pix_img((char*)first + ((xp.x * 4) + (dim[1] * (yp.x * 4))));
			xp.x++;
			yp.x = yp.z + ((yp.y - yp.z) * (xp.x - xp.z)) / (xp.y - xp.z);
		}
		else
		{
		pix_img((char*)first + ((xp.x * 4) + (dim[0] * (yp.x * 4))));
			yp.x++;
			xp.x = xp.z + ((xp.y - xp.z) * (yp.x - yp.z)) / (yp.y - yp.z);
		}
	}
	return (0);
}

static inline int	tr(int a, int amax, int bmax)
{
	unsigned int b;

	b = (((100000 * a) / amax) * (bmax/1.5)) / 100000;
	return (b);
}

/*
static inline void	to3d(t_coords *pts, unsigned int nbpts)
{
	double rap = 0.6;
	unsigned int	c = 0;

	while (c < nbpts)
	{
		pts[c].x += ((rap * 2) * pts[c].z);
		pts[c].y += (rap * pts[c].z);
		c++;
	}
}
*/

void				*draw_img(void *img, char *filename, int *dims)
{
	int		bpp;
	int		size_line;
	int		endianess;
	char	*addr;
	int		coord[4];
	t_map	pts;
	int		c = 0;

	pts = getpts(filename);
	ft_putendl("MLX -- mlx_get_data_addr");
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endianess);
	ft_putendl("\nDRAWING --");
	while (c < pts.dims.z)
	{
//		while (c < pts.dims.z && pts.pts[c].z <= 0)
//			c++;
		coord[0] = tr(pts.pts[c].x, pts.dims.x, dims[0]) + 0.6 * pts.pts[c].z;
		coord[1] = tr(pts.pts[c].y, pts.dims.y, dims[1]) + 0.3 * pts.pts[c].z;
		coord[2] = tr(pts.pts[c + 1].x, pts.dims.x, dims[0]) + 0.6 * pts.pts[c + 1].z;
		coord[3] = tr(pts.pts[c + 1].y, pts.dims.y, dims[1]) + 0.3 * pts.pts[c + 1].z;
		if (coord[2])
		{
			if (line(coord, dims, (t_pixel*)addr))
				ft_putendl("out of screen");
		}
		if (c + pts.dims.y < pts.dims.z)
		{
			coord[2] = tr(pts.pts[c + pts.dims.y].x, pts.dims.x, dims[0])+ 0.6 * pts.pts[c + pts.dims.y].z;
			coord[3] = tr(pts.pts[c + pts.dims.y].y, pts.dims.y, dims[1])+ 0.3 * pts.pts[c + pts.dims.y].z;
			if (line(coord, dims, (t_pixel*)addr))
				ft_putendl("out of screen");
		}
		else
			ft_putendl("NO V LINE");
		c++;
	}
	ft_putendl("DRAWING -- OK");
	return (img);
}
