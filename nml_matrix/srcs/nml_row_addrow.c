/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_row_addrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:28:28 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/31 18:47:08 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

t_nml_mat	*nml_mat_row_addrow(t_nml_mat *m, unsigned int where, \
	unsigned int row, float mult)
{
	t_nml_mat	*r;

	r = nml_mat_cp(m);
	if (!nml_mat_row_addrow_r(m, where, row, mult))
		return (nml_mat_free(r), NULL);
	return (r);
}

int	nml_mat_row_addrow_r(t_nml_mat *m, unsigned int where, \
	unsigned int row, float mult)
{
	unsigned int	i;

	i = 0;
	if (where >= m->rows || row >= m->rows)
		return (nml_error(__FILE__, __LINE__, "CANNOT_ADD_TO_ROW"), 0);
	while (i < m->cols)
	{
		m->data[where][i] += mult * m->data[row][i];
		i++;
	}
	return (1);
}
