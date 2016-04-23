/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 19:18:17 by liums             #+#    #+#             */
/*   Updated: 2016/04/22 14:20:00 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_parse(char *file)
{
	t_map	tab;
	int		count;
	int		c;

	c = 0;
	tab.dims.z = 100;
	if ((count = parse_file(file, &tab)) < 0)
		ft_putendl("fail");
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