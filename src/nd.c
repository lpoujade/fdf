/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/nd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 22:30:10 by liums             #+#    #+#             */
/*   Updated: 2016/05/08 11:44:39 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*draw_img(void *o_con, char *filename)
{
	int			bpp;
	int			size_line;
	int			ed;
	t_mlx_datas	*con;
	t_pixel		*addr;

	con = (t_mlx_datas*)o_con;
	ft_putendl("MLX -- new img");
	con->next_img = mlx_new_image(con->ident, con->dims[0], con->dims[1]);
	ft_putendl("MLX -- mlx_get_data_addr");
	addr = (t_pixel*)mlx_get_data_addr(con->next_img, &bpp, &size_line, &ed);
	ft_putnbr(draw_lines(tr(getpts(filename), con->dims), con->dims, addr));
	ft_putendl(" pts out");
	return (con->next_img);
}

t_map	getpts(char *filename)
{
	t_map	pts;
	int		fd;

	pts.dims.z = SUP_PTS_NB;
	if (!(pts.pts = malloc(pts.dims.z * sizeof(t_coords))))
		exit(10);
	if ((fd = open(filename, 0)) < 0)
	{
		perror(filename);
		exit(11);
	}
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
		if (coord[2] > coord[0])
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
