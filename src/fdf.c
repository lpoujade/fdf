/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 13:17:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/19 12:17:30 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	usage(void)
{
	ft_putendl("Usage : fdf [x_dim,y_dim] <map>.fdf");
	exit (0);
}

static int	key_event(int key, void *infos)
{
	t_mlx_datas	*con;
	con = (t_mlx_datas *)infos;
	if (key == 65307)
	{
		ft_putendl("KEY -- esc -- exiting");
		mlx_destroy_window(con->ident, con->wndw);
		exit (1);
	}
	if (key == 32)
	{
		ft_putendl("KEY -- space -- putting new image");
		draw_img(con->next_img, con->file, con->dims);
		mlx_put_image_to_window(con->ident, con->wndw, con->next_img, 0, 0);
		//mlx_destroy_image(con->ident, con->next_img);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx_datas		con;

	if (ac < 2)
		usage();
	if (ac == 3)
	{
		if (!ft_strcmp(av[1], "-p"))
		{
			show_parse(av[2]);
			exit (0);
		}
		con.dims[0] = ft_atoi(av[1]);
		con.dims[1] = ft_atoi(av[1] + ft_getndigits(con.dims[0]) + 1);
		con.file = av[2];
	}
	else
	{
		con.file = av[1];
		con.dims[0] = 1200;
		con.dims[1] = 1200;
	}
	con.ident = mlx_init();
	ft_putendl("MLX -- init");
	con.wndw = mlx_new_window(con.ident, con.dims[0], con.dims[1], "Hello World?");
	con.next_img = mlx_new_image(con.ident, con.dims[0], con.dims[1]);
	ft_putendl("MLX -- new_image");
	mlx_key_hook(con.wndw, key_event, (void*)&con);
	ft_putendl("MLX -- hooking key func");

	ft_putendl("MLX -- LOOP");
	mlx_loop(con.ident);
	return (0);
}
