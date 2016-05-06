/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/nd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 22:30:10 by liums             #+#    #+#             */
/*   Updated: 2016/05/06 17:47:49 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*draw_img(void *img, char *filename, int *dims)
{
	int		bpp;
	int		size_line;
	int		endianess;
	t_pixel	*addr;
	t_map	pts;

	pts = getpts(filename);
	ft_putendl("MLX -- mlx_get_data_addr");
	addr = (t_pixel*)mlx_get_data_addr(img, &bpp, &size_line, &endianess);
	ft_putnbr(draw_lines(tr(pts, dims), dims, addr));
	ft_putendl(" pts out");

	/* limits
	int coord[4] = {1,1,dims[0] - 1,dims[1] - 1};
	if (line(coord, dims, (t_pixel*)addr))
		ft_putendl("OUT");
	coord[0] = dims[0] - 1; coord[1] = 1; coord[2] = 1; coord[3] = dims[1] - 1;
	if (line(coord, dims, (t_pixel*)addr))
		ft_putendl("OUT 2");
	*//* limits */
	return (img);
}

t_map	getpts(char *filename)
{
	t_map	pts;
	int		fd;

	pts.dims.z = SUP_PTS_NB;
	if (!(pts.pts = malloc(pts.dims.z * sizeof(t_coords))))
		exit(10);
	if ((fd = open(filename, 0)) < 0)
		exit(11);
	ft_putstr("PARSING -- ");
	ft_putendl(filename);
	if (parse_file(fd, &pts) < 0)
	{
		if (errno)
			perror("fdf: parsing: ");
		exit(13);
	}
	close(fd);
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
		if (c + pts.dims.x < pts.dims.z)
		{
			coord[2] = pts.pts[c + pts.dims.x].x;
			coord[3] = pts.pts[c + pts.dims.x].y;
			outof += line(coord, dims, addr);
	}
		c++;
	}
	ft_putendl("DRAWING -- OK");
	return (outof);
}
