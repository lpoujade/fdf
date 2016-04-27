/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:12:30 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/27 17:44:56 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	pix_img(char *adddr)
{
	t_pixel *addr = (t_pixel*)adddr;
	if (addr)
		*addr = 0xffffff0;
	/*
	 *(addr + 1) = 0xff;
	 *(addr + 2) = 0xff;
	 *(addr + 3) = 0;
	 */
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
		if ((first + ((x * 4) + (dim[1] * (y * 4)))) >
				first + dim[0] * 4 + dim[1] * (dim[1] * 4) || x < 0 || y < 0)
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
	w = ft_abs(yp.y - yp.x) > ft_abs(xp.y - xp.x) ? 0 : 1;
	if ((w && xp.x > xp.y) || (!w && yp.x > yp.y))
	{
		ft_iswap(&xp.x, &xp.y);
		ft_iswap(&yp.x, &yp.y);
	}
	yp.z = yp.x;
	xp.z = xp.x;
	if (yp.x == yp.y || xp.x == xp.y)
		return (vh_lines(coord, dim, first));
	while (xp.x < xp.y && yp.x < yp.y)
	{
		if ((first + ((xp.x * 4) + (dim[1] * (yp.x * 4)))) >
				first + dim[0] * 4 + dim[1] * (dim[1] * 4))
			return (1);
		pix_img((char*)first + ((xp.x * 4) + (dim[1] * (yp.x * 4))));
		if (w)
		{
			xp.x++;
			yp.x = yp.z + ((yp.y - yp.z) * (xp.x - xp.z)) / (xp.y - xp.z);
		}
		else
		{
			ft_putendl("y increm");
			yp.x++;
			xp.x = xp.z + ((xp.y - xp.z) * (yp.x - yp.z)) / (yp.y - yp.z);
		}
	}
	return (0);
}

static inline t_map	tr(t_map orig, int *dims)
{
	int				c;

	c = 0;
	while (c < orig.dims.z)
	{
		orig.pts[c].x += 0.6 * orig.pts[c].z;
		orig.pts[c].y += 0.3 * orig.pts[c].z;
		orig.pts[c].x =
			(((100000 * orig.pts[c].x) / orig.dims.x) * (dims[0])) / 100000;
		orig.pts[c].y =
			(((100000 * orig.pts[c].y) / orig.dims.y) * (dims[1])) / 100000;
		c++;
	}
	ft_putendl("pts -> 3dified");
	return (orig);
}

void				*draw_this_line(void *img, int *dims)
{
	int		bpp;
	int		size_line;
	int		endianess;
	char	*addr;
	int coord[4];
	char *lne;
	int nl = 0;

	while (!nl)
	{
		ft_putstr("how ? ");
		get_next_line(0, &lne);
		nl = ft_atoi(lne);
	}
	ft_putendl("MLX -- mlx_get_data_addr");
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endianess);
	while (nl--)
	{
		coord[0] = 400; coord[1] = 400;
		ft_putstr("x : ");
		get_next_line(0, &lne);
		coord[2] = ft_atoi(lne);
		ft_putstr("y : ");
		get_next_line(0, &lne);
		coord[3] = ft_atoi(lne);
		if (line(coord, dims, (t_pixel*)addr))
			ft_putendl("out of screen");
	}
	return(img);
}

void				*draw_img(void *img, char *filename, int *dims)
{
	int		bpp;
	int		size_line;
	int		endianess;
	char	*addr;
	t_map	pts;

	pts = getpts(filename);
	ft_putendl("MLX -- mlx_get_data_addr");
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endianess);
	ft_putnbr(draw_lines(tr(pts, dims), dims, (t_pixel*)addr));
	ft_putendl(" lines out");
	return (img);
}
