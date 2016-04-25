/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/nd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 22:30:10 by liums             #+#    #+#             */
/*   Updated: 2016/04/25 22:30:10 by liums            ###   ######## fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Call to parse_file()
*/
t_map	getpts(char *filename)
{
	t_map	pts;

	pts.dims.z = SUP_PTS_NB;
	ft_putstr("PARSING -- ");
	ft_putendl(filename);
	if (parse_file(filename, &pts) < 0)
	{
		if (errno)
			perror("fdf: parsing: ");
		exit(13);
	}
	ft_putendl("PARSING -- parsed\n");
	return (pts);
}
