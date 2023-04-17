/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 20:40:40 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/17 20:44:47 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	endian(void)
{
	int		i;
	char	*p;

	i = 1;
	p = (char *)&i;
	if (p[0] == 1)
		return (LITTLE_ENDIAN);
	return (BIG_ENDIAN);
}
