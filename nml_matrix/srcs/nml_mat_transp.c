/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_transp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:59:17 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/02 17:18:38 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Matrix transpose
/// @param m
/// @return New transposed matrix from m
t_nml_mat	*nml_mat_transp(t_nml_mat *m)
{
	t_nml_mat		*r;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	r = nml_mat_new(m->cols, m->rows);
	if (r)
	{
		while (i < r->rows)
		{
			j = 0;
			while (j < r->cols)
			{
				r->data[i][j] = m->data[j][i];
				j++;
			}
			i++;
		}
	}
	return (r);
}
