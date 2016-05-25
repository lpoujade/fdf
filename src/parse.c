/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:46:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/25 14:36:35 by lpoujade         ###   ########.fr       */
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
		quit_error("MALLOC FAIL : ", errno, NULL);
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

static inline int	get_nums(char *line, t_map *tofill, int varx, int varz)
{
	tofill->pts[varz].x = varx;
	tofill->pts[varz].y = tofill->dims.y;
	tofill->pts[varz].z = ft_atoi(line);
	return (ft_getndigits(tofill->pts[varz].z));
}

static inline void	shame(int *to_init, char **this, char **to_this)
{
	*to_init = 0;
	*to_this = *this;
}

int					parse_file(int fd, t_map *tofill)
{
	int			gnl_ret;
	char		*line;
	char		*andise;
	t_coords	vars;

	vars.z = 0;
	while ((gnl_ret = get_next_line(fd, &line)) > 0)
	{
		shame(&vars.x, &line, &andise);
		while (*line)
		{
			line += get_nums(line, tofill, vars.x, vars.z);
			while (*line && !((ft_isdigit(*line) || *line == '-')
						&& ((*(line - 1) == ' ') || *(line + 1) == ' ')))
				++line;
			++vars.x;
			if (++vars.z >= tofill->dims.z)
				resize(&tofill->pts, &tofill->dims.z, tofill->dims.z * 2);
		}
		++tofill->dims.y;
		vars.x > tofill->dims.x ? tofill->dims.x = vars.x : 0;
		free(andise);
	}
	tofill->dims.z = (!(gnl_ret < 0)) ? vars.z : -1;
	return (gnl_ret < 0 ? -1 : tofill->dims.y * tofill->dims.x);
}
