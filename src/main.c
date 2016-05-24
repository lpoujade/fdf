/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 19:17:11 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/24 19:17:33 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			pusage(void)
{
	ft_putendl("Usage : fdf [dim] <map1.fdf [map2.fdf map3.fdf ...]");
	exit(0);
}

int					main(int ac, char **av)
{
	t_mlx_datas		con;

	if (ac < 2)
		pusage();
	if (*av[1] == '-')
	{
		if (!ft_strcmp(av[1], "-p"))
			show_parse(av[2]);
		con.dims[0] = ft_atoi(av[1] + 1);
		con.dims[1] = con.dims[0];
		con.files = av + 3;
	}
	else
	{
		con.files = av + 1;
		con.dims[0] = 1500;
		con.dims[1] = 1500;
	}
	if (!(con.ident = mlx_init()))
		quit_error("fdf: mlx_init error ", errno, NULL);
	con.wndw = mlx_new_window(con.ident, con.dims[0], con.dims[1], "fdf");
	mlx_hook(con.wndw, 2, 0, key_event, (void*)&con);
	mlx_loop(con.ident);
	return (0);
}
