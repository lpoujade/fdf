/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:46:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/15 15:54:29 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		*parse_file(char *file)
{
	int		fd;
	char	*line;
	int		count;
	int		i;
	int		*tab;

	if ((fd = open(file, O_RDONLY)) < 1)
		return (-1);
	y = 0;
	while (get_next_line(fd, &line))
	{
		while (line[i])
		{
			if (line[i] != ' ' || !ft_isdigit(line[i]))
				break ;
			if (line[i] == ' ')
				count++;
			else
				ft_atoi;
			i++;
		}
		y++;
	}
}
