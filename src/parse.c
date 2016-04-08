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

#include "fdf.h"

int		*parse_file(char *file)
{
	int		fd;
	char	*line;
	int		i, j;
	int		*x, *y;

	if ((fd = open(file, O_RDONLY)) < 1)
		return (NULL);
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) != i)
			return (NULL);
		i = 0; j = 0;
		while (line[i + j])
		{
			while (line[i + j] == ' ')
				if (line[i + j + 1])
					j++;
			x = ft_atoi(line[i + j]);
			y = i;
			x++;
			y++;
		}
	}
	return ();
}
