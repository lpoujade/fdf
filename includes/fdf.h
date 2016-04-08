/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes/fdf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 20:39:45 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/08 15:54:33 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H 

# include <fcntl.h>
# include <mlx.h>
# include "libft.h"

typedef struct		s_mlx_datas
{
	void			*ident;
	void			*wndw;
	void			*next_img;
}					t_mlx_datas;

int		*parse_file(char *file);

#endif
