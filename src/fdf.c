/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 13:17:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/15 15:28:25 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

static void	usage(void)
{
	ft_putendl("Usage : fdf <map file>");
	exit (0);
}

static int	key_event(int key, void *infos)
{
	t_mlx_datas	*con;
	con = (t_mlx_datas *)infos;
	if (key == 53)
	{
		mlx_destroy_window(con->ident, con->wndw);
		exit (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx_datas		connection;

	if (ac < 2)
		usage();
	connection.ident = mlx_init();
	parse_file(av[1])
	connection.wndw = mlx_new_window(connection.ident, 200, 200, "Hello World?");
	mlx_key_hook(connection.wndw, key_event, (void*)&connection);
	mlx_loop(connection.ident);
	return (0);
}
