/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 13:17:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/25 13:37:23 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	usage(void)
{
	ft_putendl("Usage : fdf [x_dim,y_dim] <map>.fdf\n\tfdf -p <map>.fdf");
	exit(0);
}

static int	key_event(int key, void *infos)
{
	t_mlx_datas	*con;
	static int	c = 0;

	con = (t_mlx_datas *)infos;
	if (key == 53)
	{
		ft_putendl("KEY -- esc -- exiting");
		mlx_destroy_window(con->ident, con->wndw);
		exit(errno);
	}
	else if (key == 49)
	{
		if (*(con->files + c))
		{
			ft_putstr("KEY -- space -- new image: ");
			ft_putendl(*(con->files + c));
			con->next_img = mlx_new_image(con->ident, con->dims[0], con->dims[1]);
			ft_putendl("MLX -- new_image");
			draw_img(con->next_img, *(con->files + c), con->dims);
			mlx_put_image_to_window(con->ident, con->wndw, con->next_img, 100, 100);
			mlx_destroy_image(con->ident, con->next_img);
			c++;
		}
		else
			ft_putendl("NO MORE FILES");
	}
	else
		ft_putendl(ft_strjoin("UNK KEY : ", ft_itoa(key)));
	return (0);
}

int			main(int ac, char **av)
{
	t_mlx_datas		con;

	if (ac < 2)
		usage();
	if (ac == 3 && (*av[1] == '-' || ft_strchr(av[1], ',')))
	{
		if (!ft_strcmp(av[1], "-p"))
		{
			show_parse(av[2]);
			exit(0);
		}
		con.dims[0] = ft_atoi(av[1]);
		con.dims[1] = ft_atoi(av[1] + ft_getndigits(con.dims[0]) + 1);
		con.files = av + 2;
	}
	else
	{
		con.files = av + 1;
		con.dims[0] = 800;
		con.dims[1] = 800;
	}
	con.ident = mlx_init();
	ft_putendl("MLX -- init");
	con.wndw = mlx_new_window(con.ident, con.dims[0] + 2, con.dims[1] + 2, "?");
	mlx_key_hook(con.wndw, &key_event, (void*)&con);
	ft_putendl("MLX -- hooking key func");
	ft_putendl("MLX -- LOOP\n\n");
	mlx_loop(con.ident);
	return (0);
}
