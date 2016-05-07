/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 13:17:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/06 17:53:50 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	usage(void)
{
	ft_putendl("Usage : fdf [x_dim,y_dim] <map>.fdf\n\tfdf -p <map>.fdf \
			\n\tfdf map1.fdf [map2.fdf map3.fdf ...]");
	exit(0);
}

static int	key_event(int key, void *infos)
{
	t_mlx_datas	*con;
	static int	c = 0, px = 0, py = 0;

	con = (t_mlx_datas *)infos;
	if (key == 65307) // 53
	{
		ft_putendl("KEY -- esc -- exiting");
		free (con->next_img);
		mlx_destroy_window(con->ident, con->wndw);
		exit(errno);
	}
	else if (key == 32) // 49 // right : 65363 -- left : 65361
	{
		if (*(con->files + c))
		{
			ft_putstr("KEY -- space -- new image: ");
			ft_putendl(*(con->files + c));
			con->next_img = draw_img(con, *(con->files + c));
			mlx_clear_window(con->ident, con->wndw);
			mlx_put_image_to_window(con->ident, con->wndw, con->next_img, 0, 0);
			px = 0; py = 0;
			c++;
		}
		else
			ft_putendl("NO MORE FILES");
	}
	else if (c && (key == 65363 || key == 65361 || key == 65364 || key == 65362))
	{
		if (key == 65363)
			px++;
		else if (key == 65361)
			px--;
		else if (key == 65364)
			py++;
		else
			py--;
		mlx_clear_window(con->ident, con->wndw);
		mlx_put_image_to_window(con->ident, con->wndw, con->next_img,
				px, py);
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
	if ((*av[1] == '-' || ft_strchr(av[1], ',')))
	{
		if (!ft_strcmp(av[1], "-p"))
		{
			show_parse(av[2]);
			exit(0);
		}
		con.dims[0] = ft_atoi(av[1]);
		con.dims[1] = ft_atoi(av[1] + ft_getndigits(con.dims[0]) + 1);
		con.files = av + 3;
	}
	else
	{
		con.files = av + 1;
		con.dims[0] = 1500;
		con.dims[1] = 1500;
	}
	if (!(con.ident = mlx_init()))
	{
		ft_putendl_fd("INIT ERROR", 2);
		exit (40);
	}
	ft_putendl("MLX -- init");
	con.wndw = mlx_new_window(con.ident, con.dims[0], con.dims[1], "fdf");
	mlx_key_hook(con.wndw, &key_event, (void*)&con);
	//mlx_hook(con.wndw, 3, 0, key_event, (void*)&con);
	ft_putendl("MLX -- hooking key func");
	ft_putendl("MLX -- LOOP\n\n");
	mlx_loop(con.ident);
	return (0);
}
