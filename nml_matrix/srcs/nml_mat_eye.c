/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_eye.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:50:51 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/27 12:47:33 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Create Identity Matrix size x size
/// @param size
/// @return
t_nml_mat	*nml_mat_eye(unsigned int size)
{
	t_nml_mat		*r;
	unsigned int	i;

	i = 0;
	r = nml_mat_new(size, size);
	while (i < r->rows)
	{
		r->data[i][i] = 1.0f;
		i++;
	}
	return (r);
}
