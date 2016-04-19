/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:46:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/19 16:35:29 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

static inline void	resize(t_coords **tab, size_t *act_size, size_t nsize)
{
	t_coords		*new;

	if (*act_size >= nsize)
		exit(2);
	ft_putendl_fd("WILL PROBABLY SEGFAULT", 2);
	if (!(new = malloc(nsize * sizeof(t_coords))))
		exit(12);
	ft_memcpy(new, *tab, *act_size);
	//ft_swap(tab, &new);
	*tab = new;
	//free(new);
	*act_size = nsize;
}

/*
** A(x, y, z) = (tab[A].x, tab[A].y, tab[A].z)
*/

int					parse_file(char *file, t_coords **tab)
{
	int				fd;
	char			*line;
	t_coords		vars;
	size_t			ts;
	int				mx;

	ts = 10000;
	vars.z = 0;
	vars.y = 0;
	mx = 0;
	if (!(*tab = malloc(ts * sizeof(t_coords))) ||
			(fd = open(file, 0)) < 0)
		return (-1);
	while (get_next_line(fd, &line) && !(vars.x = 0))
	{
		while (*line)
		{
			(*tab)[vars.z].x = vars.x;
			(*tab)[vars.z].y = vars.y;
			(*tab)[vars.z].z = ft_atoi(line);
			line += ft_getndigits((*tab)[vars.z].z);
			*line ? line++ : 0;
			while (*line && !((ft_isdigit(*line) || *line == '-')
						&& ((*(line - 1) == ' ') || *(line + 1) == ' ')))
				line++;
			vars.x++ > mx ? mx = vars.x : 0;
			if (++vars.z >= (int)ts)
				resize(tab, &ts, ts * 2);
		}
		vars.y++;
	}
	close(fd);
	return (vars.y * mx);
}
