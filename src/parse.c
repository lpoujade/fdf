/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:46:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/08 16:44:59 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ft_putnbr(ft_atoi(line)); ft_putstr(ft_atoi(line) >= 10 ? " " : "  ");
////#include "fdf.h"
#include <fcntl.h>
#include "libft.h"

int		dispatch_nums(char *line, int **tab);

/*
** A(x, y, z) = (tab[x][A], tab[y][A], tab[z][A])
*/

int		parse_file(char *file, int ***otab)
{
	int		fd;
	char	*line;
	int		tsize = 0;
	int		y = 0;
	int		**tab;

	if (!(tab = (int**)malloc(3 * sizeof(int*))))
		return (-1);
	*otab = tab;
	tab[1] = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (-1);
	while (get_next_line(fd, &line))
	{
		ft_putnbr(tsize = dispatch_nums(line, tab)); ft_putchar('\n');
		if (!tab[1])
			if (!(tab[1] = (int*)malloc(tsize * sizeof(int))))
				return (-1);
		tab[1][y] = y;
		y++;
		if (y >= tsize)
		{
			ft_putendl("---------------- N O P ---------------- ");
			exit (12);
		}
	}
	return (y * y);
}

int		dispatch_nums(char *line, int **tab)
{
	int		c;

	c = 0;
	if (!(tab[2] = (int*)malloc(200 * sizeof(int)))
			|| !(tab[0] = (int*)malloc(200 * sizeof(int))))
		return (-1);
	while (*line)
	{
		tab[0][c] = c;
		tab[2][c] = ft_atoi(line);
		line += ft_getndigits(ft_atoi(line));
		while (*line && *line == ' ')
			line++;
		line ? line++ : 0;
		c++;
	}
	return (c);
}
