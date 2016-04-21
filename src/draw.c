/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 13:12:30 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/21 19:56:50 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	/*
	t_pixel	*p;
	p = (t_pixel*)addr;
	*p = 0xffffff00;
	*/

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
			if (y >= dim[1] || x >= dim[0] || y < 0 || x < 0)
				return (1);
			pix_img((char*)first + ((x*4) + (dim[1] * (y * 4))));
			y > ey ? y-- : y++;
		}
	else if (y == ey)
		while (x != ex && x > 0)
		{
			if (y >= dim[1] || x >= dim[0] || y < 0 || x < 0)
				return (1);
			pix_img((char*)first + ((x*4) + (dim[1] * (y * 4))));
			x > ex ? x-- : x++;
		}
	else
		pix_img((char*)first + ((x*4) + (dim[1] * (y * 4))));
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
		if (vh_lines(coord, dim, first))
			return (1);
	while (xp.x <= xp.y && !(yp.x == yp.y || xp.x == xp.y))
	{
		pix_img((char*)first + ((xp.x * 4) + (dim[1] * (yp.x * 4))));			// 4 -> mlx bpp
		yp.x = yp.z + ((yp.y - yp.z) * (xp.x - xp.z))/(xp.y - xp.z);
		xp.x++;
		if (yp.x > dim[1] || xp.x > dim[0] || yp.x < 0 || xp.x < 0)
			return (1);
		if (xp.x == xp.y && yp.x == yp.y)
			break ;
	}
	return (0);
}

static inline int	translate(int a, int amax, int bmax)
{
	unsigned int b;

	b = (((1000*a) / amax) * bmax) / 1000;
	return (b);
}

void				*draw_img(void *img, char *filename, int *dims)
{
	int		bpp, size_line, endianess;
	char	*addr;
	int		coord[4];
	t_map	pts;
	int		size, c = 0;

	pts.dims.z = 100000;
	ft_putendl("MLX -- mlx_get_data_addr");
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endianess);
	ft_putstr("PARSING -- ");
	ft_putendl(filename);
	if ((size = parse_file(filename, &pts)) < 0)
	{
		if (errno)
			perror("fdf: parsing: ");
		exit (13);
	}
	ft_putendl("PARSING -- parsed\n\nDRAWING --");
	while (c + 1 < pts.dims.z)
	{
		coord[0] = translate(pts.pts[c].x, pts.dims.x, dims[0]);
		coord[1] = translate(pts.pts[c].y, pts.dims.y, dims[1]);
		coord[2] = translate(pts.pts[c + 1].x, pts.dims.x, dims[0]);
		coord[3] = translate(pts.pts[c + 1].y, pts.dims.y, dims[1]);
		if (coord[2] > 1)
			if (line(coord, dims, (t_pixel*)addr))
				ft_putendl("out of screen");
		if (c + pts.dims.z/pts.dims.x < pts.dims.z)
		{
			coord[2] = translate(pts.pts[c + pts.dims.z/pts.dims.x].x, pts.dims.x, dims[0]);
			coord[3] = translate(pts.pts[c + pts.dims.z/pts.dims.x].y, pts.dims.y, dims[1]);
			if (line(coord, dims, (t_pixel*)addr))
				ft_putendl("out of screen");
		}
		c++;
	}
	ft_putendl("DRAWING -- OK");
	return (img);
}
