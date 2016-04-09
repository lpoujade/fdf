/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 13:17:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/09 19:23:04 by lpoujade         ###   ########.fr       */
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
		draw_img(con->next_img);
		mlx_put_image_to_window(con->ident, con->wndw, con->next_img, 0, 0);
	}
	return (0);
}

static inline void	pix_img(char *addr)
{
	*addr = 0xff;
	*(addr + 1) = 0xff;
	*(addr + 2) = 0xff;
	*(addr + 3) = 0;
}

void	*draw_img(void *img)
{
	int		bpp, size_line, endianess;
	char	*addr;

	ft_putendl("MLX -- mlx_get_data_addr");
	addr = mlx_get_data_addr(img, &bpp, &size_line, &endianess);
	addr += 100*size_line;
	size_line /= 4;

	while (size_line--)
	{
		pix_img(addr);
		addr += bpp / 8;
	}
	return (img);
}

int		main(int ac, char **av)
{
	(void)av; int width = 400, height = 400;
	t_mlx_datas		connection;

	if (ac < 2)
		usage();
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
