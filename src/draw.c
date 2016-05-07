/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:12:30 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/06 18:24:36 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	pix_img(char *addr)
{

	if (addr)
		*(t_pixel*)addr = 0xffffff;
}

static inline int	vh_lines(int const *coord, int *dim, t_pixel *first)
{
	int	x;
	int	y;
	int	ey;
	int	ex;
	int	pts_out;

	pts_out = 0;
	x = coord[0];
	y = coord[1];
	ex = coord[2];
	ey = coord[3];
	while (y != ey || x != ex)
	{
		if (!(x + 1 >= dim[0] || y + 1 >= dim[1] || y < 0 || x < 0))
			pix_img((char*)first + ((x * 4) + (dim[1] * (y * 4))));
		else
			pts_out++;
		if (x == ex)
			y > ey ? y-- : y++;
		else
			x > ex ? x-- : x++;
	}
	return (pts_out);
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
	int			pts_out;
	int			rev = 0;

	pts_out = 0;
	xp.x = coord[0];
	yp.x = coord[1];
	xp.y = coord[2];
	yp.y = coord[3];
	if (yp.x == yp.y || xp.x == xp.y)
		return (vh_lines(coord, dim, first));
	if ((ft_abs(yp.y - yp.x) > ft_abs(xp.y - xp.x)))
		rev = 1;
	if ((xp.x > xp.y && !rev) || (rev && yp.x > yp.y))
	{
		ft_iswap(&xp.x, &xp.y);
		ft_iswap(&yp.x, &yp.y);
	}
	yp.z = yp.x;
	xp.z = xp.x;
	while ((xp.x <= xp.y && !rev) || (rev && yp.x <= yp.y))
	{
		if (!(xp.x + 1 >= dim[0] || yp.x + 1 >= dim[1] || xp.x < 0 || yp.x < 0))
			pix_img((char*)first + ((xp.x * 4) + (dim[1] * (yp.x * 4))));
		else
			pts_out++;
		if (!rev)
		{
			xp.x++;
			yp.x = yp.z + ((yp.y - yp.z) * (xp.x - xp.z)) / (xp.y - xp.z);
		}
		else
		{
			yp.x++;
			xp.x = xp.z + ((xp.y - xp.z) * (yp.x - yp.z)) / (yp.y - yp.z);
		}
	}
	return (pts_out);
}

t_map				tr(t_map orig, int *dims)
{
	int				c;
	int				x;

	c = 0;
	(void)dims;
	while (c < orig.dims.z)
	{
		x = orig.pts[c].x;
		orig.pts[c].x = ((orig.pts[c].x - orig.pts[c].y) / 1);
		orig.pts[c].y = (-(orig.pts[c].z) + ((x + orig.pts[c].y) / 2.8));
		c++;
	}
	return (orig);
}
