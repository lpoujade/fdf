/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 19:18:17 by liums             #+#    #+#             */
/*   Updated: 2016/05/04 18:20:18 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_parse(char *file)
{
	t_map	tab;
	int		count;
	int		fd;
	int		c;

	c = 0;
	if (!(fd = open(file, 0)))
	{
		ft_putendl("fail");
		return ;
	}
	tab.dims.z = SUP_PTS_NB;
	if ((count = parse_file(fd, &tab)) < 0)
	{
		ft_putendl("fail");
		return ;
	}
	close(fd);
	while (c < tab.dims.z)
	{
		ft_putnbr(tab.pts[c].x);
		ft_putchar(' ');
		ft_putnbr(tab.pts[c].y);
		ft_putchar(' ');
		ft_putnbr(tab.pts[c].z);
		ft_putchar('\n');
		c++;
	}
}
