/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:46:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/14 20:53:47 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ft_putnbr(ft_atoi(line)); ft_putstr(ft_atoi(line) >= 10 ? " " : "  ");
////#include "fdf.h"
#include <fcntl.h>
#include "libft.h"

static inline void	resize(int **tab, size_t act_size, size_t nsize)
{
	int		*new;
	int		c;

	if (act_size >= nsize)
		exit (2);
	ft_putendl_fd("WILL PROBABLY SEGFAULT", 2);
	c = 2;
	while (c + 1)
	{
		if (!(new = (int*)malloc(nsize * sizeof(int))))
			exit(12);
		ft_memcpy(new, (tab + c), act_size);
		//*(tab + c) = new;
		tab[c] = new;
		c--;
	}
}

/*
** A(x, y, z) = (tab[0][A], tab[1][A], tab[2][A])
*/

int					parse_file(char *file, int ***otab)
{
	int		fd;
	char	*line;
	int		**tab;
	int		x;
	int		y;
	int		w;
	int		ts = 600;

	y = 0;
	w = 0;
	if (!(tab = (int**)malloc(3 * sizeof(int*)))
			|| !(tab[0] = (int*)malloc(ts * sizeof(int)))
			|| !(tab[1] = (int*)malloc(ts * sizeof(int)))
			|| !(tab[2] = (int*)malloc(ts * sizeof(int)))
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
			*line ? line++ : 0;
			while (*line && !(ft_isdigit(*line) && *(line - 1) == ' '))
				line++;
			x++;
			if (++w >= ts)
			{
				resize(tab, ts, ts * 2);
				ts *= 2;
			}
		}
		y++;
	}
	*otab = tab;
	return (y * x);
}
