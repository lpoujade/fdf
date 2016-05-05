/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:12:30 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/05 19:00:44 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	pix_img(char *addr)
{

	if (addr)
		*(t_pixel*)addr = 0xffffff0;
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
	while (y != ey || x != ex)
	{
		if (x >= dim[0] || y >= dim[1] || y < 0 || x < 0)
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

	xp.x = coord[0];
	yp.x = coord[1];
	xp.y = coord[2];
	yp.y = coord[3];
	if (yp.x == yp.y || xp.x == xp.y)
		return (vh_lines(coord, dim, first));
	if ((ft_abs(yp.y - yp.x) > ft_abs(xp.y - xp.x)) && 0) // --- 
		ft_swap(&xp, &yp);
	if (xp.x > xp.y)
	{
		ft_iswap(&xp.x, &xp.y);
		ft_iswap(&yp.x, &yp.y);
	}
	yp.z = yp.x;
	xp.z = xp.x;
	while (xp.x <= xp.y)
	{
		if (xp.x >= dim[0] || yp.x >= dim[1] || xp.x < 0 || yp.x < 0)
			return (1);
		pix_img((char*)first + ((xp.x * 4) + (dim[1] * (yp.x * 4))));
		xp.x++;
		yp.x = yp.z + ((yp.y - yp.z) * (xp.x - xp.z)) / (xp.y - xp.z);
	}
	return (0);
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
		orig.pts[c].x = (x - orig.pts[c].y) / 2;
		orig.pts[c].y = orig.pts[c].z + ((x + orig.pts[c].y) / 1.5);
		/*
		orig.pts[c].x *= 10;
		orig.pts[c].y *= 10;
			*/
		orig.pts[c].x += orig.dims.x/4;
		orig.pts[c].y += orig.dims.y/4;
		if (orig.pts[c].x < 0 || orig.pts[c].y < 0)
			ft_putendl("NEGATIVE POINTS !");
		orig.pts[c].x =
			(((10000 * orig.pts[c].x) / orig.dims.x) * (dims[0])) / 10000;
		orig.pts[c].y =
			(((10000 * orig.pts[c].y) / orig.dims.y) * (dims[1])) / 10000;
		if (orig.pts[c].x > dims[0] || orig.pts[c].y > dims[1])
			ft_putendl("WRONG CALC");
		c++;
	}
	ft_putendl("pts -> 3dified");
	return (orig);
}
