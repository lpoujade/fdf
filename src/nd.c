/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/nd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 22:30:10 by liums             #+#    #+#             */
/*   Updated: 2016/04/27 13:57:08 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Call to parse_file()
*/
t_map	getpts(char *filename)
{
	t_map	pts;

	pts.dims.z = SUP_PTS_NB;
	ft_putstr("PARSING -- ");
	ft_putendl(filename);
	if (parse_file(filename, &pts) < 0)
	{
		if (errno)
			perror("fdf: parsing: ");
		exit(13);
	}
	ft_putendl("PARSING -- parsed\n");
	return (pts);
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

int		draw_lines(t_map pts, int *dims, t_pixel *addr)
{
	int		c;
	int		outof;
	int		coord[4];

	c = 0;
	outof = 0;
	ft_putendl("\nDRAWING --");
	while (c < pts.dims.z)
	{
		coord[0] = pts.pts[c].x + 0.6 * pts.pts[c].z;
		coord[1] = pts.pts[c].y + 0.3 * pts.pts[c].z;
		coord[2] = pts.pts[c + 1].x + 0.6 * pts.pts[c + 1].z;
		coord[3] = pts.pts[c + 1].y + 0.3 * pts.pts[c + 1].z;
		if (coord[2])
		{
			if (line(coord, dims, addr))
				outof++;
		}
		if (c + pts.dims.y < pts.dims.z)
		{
			coord[2] = pts.pts[c + pts.dims.y].x + 0.6 * pts.pts[c + pts.dims.y].z;
			coord[3] = pts.pts[c + pts.dims.y].y + 0.3 * pts.pts[c + pts.dims.y].z;
			if (line(coord, dims, addr))
				outof++;
		}
		c++;
	}
	ft_putendl("DRAWING -- OK");
	return (outof);
}
