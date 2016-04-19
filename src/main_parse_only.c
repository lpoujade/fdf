/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 19:18:17 by liums             #+#    #+#             */
/*   Updated: 2016/04/14 21:18:33 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_parse(char *file)
{
	t_coords	*tab = NULL;
	int count, c = 0;

	if ((count = parse_file(file, &tab)) < 0)
		ft_putendl("fail");

	while (c < count)
	{
		ft_putnbr(tab[c].x); ft_putchar(' ');
		ft_putnbr(tab[c].y); ft_putchar(' ');
		ft_putnbr(tab[c].z); ft_putchar('\n');
		c++;
	}
	return (0);
}
