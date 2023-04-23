/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_normalize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:35:01 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/23 17:49:12 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

int	nml_mat_normalize_r(t_nml_mat *m)
{
	t_nml_mat		*l2norms;
	unsigned int	j;

	j = 0;
	l2norms = NULL;
	l2norms = nml_mat_l2norm(m);
	while (j < m->cols)
	{
		if (l2norms->data[0][j] < NML_MIN_COEF)
		{
			nml_error(__FILE__, __LINE__, "VECTOR_J_DEGENERATE");
			return (nml_mat_free(l2norms), 0);
		}
		nml_mat_col_mult_r(m, j, 1/l2norms->data[0][j]);
		j++;
	}
	return (1);
}

t_nml_mat	*nml_mat_normalize(t_nml_mat *m)
{
	t_nml_mat	*r;

	r = nml_mat_cp(m);
	if (!nml_mat_normalize_r(r))
		return (nml_mat_free(r), NULL);
	return (r);
}
