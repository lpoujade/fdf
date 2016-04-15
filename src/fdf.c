/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 13:17:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/15 16:27:13 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_putendl("KEY -- esc -- exiting");
		mlx_destroy_window(con->ident, con->wndw);
		exit (1);
	}
	if (key == 49)
	{
		ft_putendl("KEY -- space -- putting new image");
		draw_img(con->next_img, con->file);
		mlx_put_image_to_window(con->ident, con->wndw, con->next_img, 0, 0);
	}
	return (0);
}

int		main(int ac, char **av)
{
	(void)av; int width = 800, height = 800;
	t_mlx_datas		connection;

	if (ac < 2)
		usage();
	connection.file = av[1];

	connection.ident = mlx_init();
	ft_putendl("MLX -- init");
	connection.wndw = mlx_new_window(connection.ident, width, height, "Hello World?");
	connection.next_img = mlx_new_image(connection.ident, width, height);
	ft_putendl("MLX -- new_image");
	mlx_key_hook(connection.wndw, key_event, (void*)&connection);
	ft_putendl("MLX -- hooking key func");

	ft_putendl("MLX -- LOOP");
	mlx_loop(connection.ident);
	return (0);
}
