/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:46:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/14 21:09:30 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ft_putnbr(ft_atoi(line)); ft_putstr(ft_atoi(line) >= 10 ? " " : "  ");
////#include "fdf.h"
#include <fcntl.h>
#include "libft.h"

typedef struct		s_coords
{
	int				x;
	int				y;
	int				z;
}					t_coords;

static inline void	resize(t_coords **tab, size_t act_size, size_t nsize)
{
	t_coords		*new;

	if (act_size >= nsize)
		exit (2);
	ft_putendl_fd("WILL PROBABLY SEGFAULT", 2);
	if (!(new = malloc(nsize * sizeof(t_coords))))
		exit(12);
	ft_memcpy(new, tab, act_size);
	//tab = new;
	ft_swap(&tab, &new);
}

/*
** A(x, y, z) = (tab[0][A], tab[1][A], tab[2][A])
*/

int					parse_file(char *file, t_coords **f)
{
	int		fd;
	char	*line;
	t_coords *tab;
	int		x;
	int		y;
	int		w;
	int		ts;

	ts = 200;
	y = 0;
	w = 0;
	if (!(tab = malloc(ts * sizeof(t_coords)))
			|| (fd = open(file, O_RDONLY)) < 0)
		return (-1);
	while (get_next_line(fd, &line))
	{
		x = 0;
		while (*line)
		{
			tab[w].x = x;
			tab[w].y = y;
			tab[w].z = ft_atoi(line);

			line += ft_getndigits(tab[w].z);
			*line ? line++ : 0;
			while (*line && !(ft_isdigit(*line) && *(line - 1) == ' '))
				line++;
			x++;
			if (++w >= ts)
			{
				resize(&tab, ts, ts * 2);
				ts *= 2;
			}
		}
		y++;
	}
	*f = tab;
	return (y * x);
}
