/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:46:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/25 14:38:50 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

static inline void	resize(t_coords **tab, int *act_size, int nsize)
{
	t_coords		*new_tab;
	t_coords		*todel;
	int				count;

	count = 0;
	if (*act_size >= nsize)
		exit(2);
	ft_putstr_fd("POSSIBLE MEMLEAK (+pasts) : ", 2);
	ft_putnbr_fd(sizeof(t_coords) * *act_size, 2);
	ft_putchar('\n');
	if (!(new_tab = malloc(nsize * sizeof(t_coords))))
		exit(12);
	while (count < *act_size)
	{
		new_tab[count] = (*tab)[count];
		count++;
	}
	todel = *tab;
	*tab = new_tab;
	free(todel);
	*act_size = nsize;
}

/*
** A(x, y, z) = (tab[A].x, tab[A].y, tab[A].z)
*/

int					parse_file(char *file, t_map *tofill)
{
	int			fd;
	int			gnl_ret;
	char		*line;
	t_coords	vars;

	vars.z = 0;
	tofill->dims.y = 0;
	tofill->dims.x = 0;
	if (!(tofill->pts = malloc(tofill->dims.z * sizeof(t_coords))) ||
			(fd = open(file, 0)) < 0)
		return (-1);
	while ((gnl_ret = get_next_line(fd, &line)) > 0)
	{
		vars.x = 0;
		while (*line)
		{
			tofill->pts[vars.z].x = vars.x;
			tofill->pts[vars.z].y = tofill->dims.y;
			tofill->pts[vars.z].z = ft_atoi(line) + 1;
			line += ft_getndigits(tofill->pts[vars.z].z);
			*line ? line++ : 0;
			while (*line && !((ft_isdigit(*line) || *line == '-')
						&& ((*(line - 1) == ' ') || *(line + 1) == ' ')))
				line++;
			vars.x++;
			if (++vars.z >= tofill->dims.z)
				resize(&tofill->pts, &tofill->dims.z, tofill->dims.z * 2);
		}
		tofill->dims.y++;
		vars.x > tofill->dims.x ? tofill->dims.x = vars.x : 0;
	}
	if (gnl_ret < 0)
	{
		ft_putendl("READ ERROR");
		return (-1);
	}
	close(fd);
	tofill->dims.z = vars.z;
	return (tofill->dims.y * tofill->dims.x);
}
