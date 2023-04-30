/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_lu_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:37:13 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 18:55:58 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Returns LU matrix from a LUP structure
/// @param lup
/// @return
t_nml_mat	*nml_mat_lu_get(t_nml_mat_lup *lup)
{
	unsigned int	i;
	unsigned int	j;
	t_nml_mat		*r;

	i = 1;
	r = nml_mat_cp(lup->_u);
	while (i < lup->_l->rows)
	{
		j = 0;
		while (j < i)
		{
			r->data[i][j] = lup->_l->data[i][j];
			j++;
		}
		i++;
	}
	return (r);
}
