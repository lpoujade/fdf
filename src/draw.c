/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:12:30 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/24 19:01:59 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	pix_img(char *addr)
{
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

static inline void	sets(t_coords *xp, t_coords *yp, int const *coord, \
		int *pts_out)
{
	xp->x = coord[0];
	yp->x = coord[1];
	xp->y = coord[2];
	yp->y = coord[3];
	*pts_out = 0;
}

static inline void	swaps(t_coords *xp, t_coords *yp)
{
	ft_iswap(&xp->x, &xp->y);
	ft_iswap(&yp->x, &yp->y);
}

/*
** y/x p struct : yp.x = current y; yp.y = end y; yp.z = start y
** so : xp.x = X  / yp.x = Y		(y->z inclus)
**		xp.y = X1 / yp.y = Y1
**		xp.z = X2 / yp.z = Y2		(start)
*/

int					line(int const *coord, int *dim, t_pixel *first)
{
	t_coords	xp;
	t_coords	yp;
	int			pts_out;
	int			rev;

	rev = 0;
	sets(&xp, &yp, coord, &pts_out);
	if (yp.x == yp.y || xp.x == xp.y)
		return (vh_lines(coord, dim, first));
	rev = ((ft_abs(yp.y - yp.x) > ft_abs(xp.y - xp.x))) ? 1 : 0;
	if ((xp.x > xp.y && !rev) || (rev && yp.x > yp.y))
		swaps(&xp, &yp);
	yp.z = yp.x;
	xp.z = xp.x;
	while ((xp.x <= xp.y && !rev) || (rev && yp.x <= yp.y))
	{
		if (!(xp.x + 1 >= dim[0] || yp.x + 1 >= dim[1] || xp.x < 0 || yp.x < 0))
			pix_img((char*)first + ((xp.x * 4) + (dim[1] * (yp.x * 4))));
		else
			pts_out++;
		!rev ? yp.x = yp.z + ((yp.y - yp.z) * (++xp.x - xp.z)) / (xp.y - xp.z) :
			(xp.x = xp.z + ((xp.y - xp.z) * (++yp.x - yp.z)) / (yp.y - yp.z));
	}
	return (pts_out);
}
