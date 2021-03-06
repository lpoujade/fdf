/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../libft/src/ft_getndigits.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 15:49:17 by lpoujade          #+#    #+#             */
/*   Updated: 2016/04/06 15:28:38 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getndigits(int a)
{
	int c;

	c = 0;
	if (!a)
		return (1);
	while (a)
	{
		a /= 10;
		c++;
	}
	return (c);
}
