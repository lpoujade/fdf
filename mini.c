/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 19:18:17 by liums             #+#    #+#             */
/*   Updated: 2016/04/14 21:09:44 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

typedef struct		s_coords
{
	int				x;
	int				y;
	int				z;
}					t_coords;

int		parse_file(char *file, t_coords **tab);

int	main(int ac, char **av)
{
	(void)ac;
	t_coords	*tab = NULL;
	int count, c = 0;

	if ((count = parse_file(av[1], &tab)) < 0)
		ft_putendl("fail");

	while (c < count)
	{
		//ft_putnbr(count);ft_putstr("\t:");
		ft_putnbr(tab[c].x); ft_putchar(' ');
		ft_putnbr(tab[c].y); ft_putchar(' ');
		ft_putnbr(tab[c].z); ft_putchar('\n');
		//printf("x: %d| y: %d| z: %d\n", tab[0][c], tab[1][c], tab[2][c]);
		c++;
	}
	return (0);
}
