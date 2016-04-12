/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 19:18:17 by liums             #+#    #+#             */
/*   Updated: 2016/04/11 19:18:17 by liums            ###   ######## fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int		parse_file(char *file, int ***otab);

int	main(int ac, char **av)
{
	(void)ac;
	int **tab = NULL;
	int count, c = 0;

	if (!(count = parse_file(av[1], &tab)))
		ft_putendl("fail");
	while (c < count)
	{
		//ft_putnbr(count);ft_putstr("\t:");
		ft_putnbr(tab[0][c]); ft_putchar(' ');
		ft_putnbr(tab[1][c]); ft_putchar(' ');
		ft_putnbr(tab[2][c]); ft_putchar('\n');
		//printf("x: %d| y: %d| z: %d\n", tab[0][c], tab[1][c], tab[2][c]);
		c++;
	}
	return (0);
}
