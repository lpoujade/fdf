/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/nd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 22:30:10 by liums             #+#    #+#             */
/*   Updated: 2016/04/28 10:58:37 by lpoujade         ###   ########.fr       */
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

int		draw_lines(t_map pts, int *dims, t_pixel *addr)
{
	int		c;
	int		outof;
	int		coord[4];

	c = 0;
	outof = 0;
	ft_putendl("\nDRAWING --");
	while (c + 1 < pts.dims.z)
	{
		coord[0] = pts.pts[c].x;
		coord[1] = pts.pts[c].y;
		coord[2] = pts.pts[c + 1].x;
		coord[3] = pts.pts[c + 1].y;
		if (coord[2])
			outof += line(coord, dims, addr);
		if (c + pts.dims.y < pts.dims.z)
		{
			coord[2] = pts.pts[c + pts.dims.x].x;
			coord[3] = pts.pts[c + pts.dims.y].y;
			outof += line(coord, dims, addr);
		}
		c++;
	}
	ft_putendl("DRAWING -- OK");
	return (outof);
}
