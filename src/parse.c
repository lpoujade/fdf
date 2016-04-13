/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:46:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/13 17:53:30 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ft_putnbr(ft_atoi(line)); ft_putstr(ft_atoi(line) >= 10 ? " " : "  ");
////#include "fdf.h"
#include <fcntl.h>
#include "libft.h"

/*
** A(x, y, z) = (tab[x][A], tab[y][A], tab[z][A])
*/

int		parse_file(char *file, int ***otab)
{
	int		fd;
	char	*line;
	int		y = 0, x = 0, w = 0;
	int		**tab;

	if (!(tab = (int**)malloc(3 * sizeof(int*)))
			|| !(tab[0] = (int*)malloc(200 * sizeof(int)))
			|| !(tab[1] = (int*)malloc(200 * sizeof(int)))
			|| !(tab[2] = (int*)malloc(200 * sizeof(int)))
			|| (fd = open(file, O_RDONLY)) < 0)
		return (-1);
	while (get_next_line(fd, &line))
	{
		x = 0;
		while (*line)
		{
			tab[0][w] = x;
			tab[2][w] = ft_atoi(line);
			tab[1][w] = y;
			line += ft_getndigits(tab[2][w]);
			while (*line && *line == ' ')
				line++;
			x++;
			if (++w >= 200)
				ft_putendl("have to realloc, now will segfault!");
			*line ? line++ : 0;
		}
		y++;
	}
	*otab = tab;
	return (y * x);
}
