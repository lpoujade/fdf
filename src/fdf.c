/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 13:17:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/03/14 20:51:46 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

static int	key_event(int key, t_mlx_datas con)
{
	ft_putnbr(key);ft_putchar('\n');
	if (key == 53)
	{
		ft_putendl("CLOSING");
		mlx_destroy_window(con.ident, con.wndw);
	}
	return (0);
}

int		main(int ac, char **av)
{
	(void)av; (void)ac;
	t_mlx_datas		connection;

	connection.ident = mlx_init();
	connection.wndw = mlx_new_window(connection.ident, 200, 200, "Hello World?");
	mlx_key_hook(connection.wndw, key_event, (void*)&connection);
	mlx_loop(connection.ident);
	return (0);
}
