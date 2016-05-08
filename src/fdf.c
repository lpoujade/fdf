/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 13:17:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/08 17:14:46 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	pusage(void)
{
	ft_putendl("Usage : fdf [dim] <map1.fdf [map2.fdf map3.fdf ...]");
	exit(0);
}

void		quit_error(char *str, int error, void (exit_func)(void))
{
	if (str)
		ft_putendl(str);
	if (error)
		ft_putendl(strerror(error));
	if (exit_func)
		(exit_func)();
	exit(error ? error : 127);
}

static int	key_event(int key, void *infos)
{
	static int	c = 0;
	static int	px = 0;
	static int	py = 0;
	t_mlx_datas	*con;

	con = (t_mlx_datas *)infos;
	if (key == 53)
	{
		ft_putendl("KEY -- esc -- exiting");
		free(con->next_img);
		mlx_destroy_window(con->ident, con->wndw);
		exit(errno);
	}
	else if (key == 49)
	{
		if (*(con->files + c))
		{
			ft_putstr("KEY -- space -- new image: ");
			ft_putendl(*(con->files + c));
			con->next_img = draw_img(con, *(con->files + c));
			mlx_clear_window(con->ident, con->wndw);
			mlx_put_image_to_window(con->ident, con->wndw, con->next_img, 0, 0);
			px = 0;
			py = 0;
			c++;
		}
		else
			ft_putendl("NO MORE FILES");
	}
	else if (c && (key <= 126 && key >= 123))
	{
		if (key == 124)
			px++;
		else if (key == 123)
			px--;
		else if (key == 125)
			py++;
		else
			py--;
		mlx_clear_window(con->ident, con->wndw);
		mlx_put_image_to_window(con->ident, con->wndw, con->next_img, px, py);
	}
	else
		ft_putendl(ft_strjoin("UNK KEY : ", ft_itoa(key)));
	return (0);
}

int			main(int ac, char **av)
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
