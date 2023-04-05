/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_ref.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:54:19 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/04 10:46:48 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

static void	nml_mat_ref_util(t_nml_mat *r, unsigned int i, unsigned int j)
{
	unsigned int	k;

	k = i + 1;
	while (k < r->rows)
	{
		if (fabs(r->data[k][j]) > NML_MIN_COEF)
			nml_mat_row_addrow_r(r, k, i, -(r->data[k][j]));
		k++;
	}
}

/// @brief Retrieves the matrix in Row Echelon form using Gauss Elimination
/// @param m
/// @return
t_nml_mat	*nml_mat_ref(t_nml_mat *m)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	pivot;
	t_nml_mat		*r;

	r = nml_mat_cp(m);
	j = 0;
	i = 0;
	while (j < r->cols && i < r->rows)
	{
		pivot = nml_mat_pivotmaxidx(r, j, i);
		if (pivot < 0)
		{
			j++;
			continue ;
		}
		if (pivot != i)
			nml_mat_row_swap_r(r, i, pivot);
		nml_mat_row_mult_r(r, i, 1 / r->data[i][j]);
		nml_mat_ref_util(r, i, j);
		i++;
		j++;
	}
	return (r);
}
