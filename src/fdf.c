/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 13:17:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/24 19:19:25 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				quit_error(char *str, int error, void (exit_func)(void))
{
	if (str)
		ft_putendl(str);
	if (error)
		ft_putendl(strerror(error));
	if (exit_func)
		(exit_func)();
	exit(error ? error : 127);
}

static inline void	quit(t_mlx_datas *con)
{
	ft_putendl("KEY -- esc -- exiting");
	mlx_destroy_image(con->ident, con->next_img);
	mlx_destroy_window(con->ident, con->wndw);
	exit(errno);
}

static inline void	move(int c, int key, t_mlx_datas *con, int *dec)
{
	if (c && (key <= 126 && key >= 123))
	{
		if (key == 124)
			dec[0] += 4;
		else if (key == 123)
			dec[0] -= 4;
		else if (key == 125)
			dec[1] += 4;
		else
			dec[1] -= 4;
		redraw_img(con, dec);
		mlx_clear_window(con->ident, con->wndw);
		mlx_put_image_to_window(con->ident, con->wndw, con->next_img, 0, 0);
	}
	else if (key == 4)
		mlx_clear_window(con->ident, con->wndw);
	else
		ft_putendl(ft_strjoin("UNK KEY : ", ft_itoa(key)));
}

int					key_event(int key, void *infos)
{
	static int	c = 0;
	static int	dec[2] = {0, 0};
	t_mlx_datas	*con;

	con = (t_mlx_datas *)infos;
	if (key == 53)
		quit(con);
	else if (key == 49)
	{
		if (*(con->files + c))
		{
			dec[0] = 0;
			dec[1] = 0;
			ft_putstr("KEY -- space -- new image: ");
			ft_putendl(*(con->files + c));
			con->next_img = init_img(con, *(con->files + c));
			mlx_clear_window(con->ident, con->wndw);
			mlx_put_image_to_window(con->ident, con->wndw, con->next_img, 0, 0);
			c++;
		}
		else
			ft_putendl("NO MORE FILES");
	}
	move(c, key, con, dec);
	return (0);
}
