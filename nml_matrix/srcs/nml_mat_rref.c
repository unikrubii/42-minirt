/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_rref.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:38:50 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/04 10:46:58 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

static void	nml_mat_rref_util(t_nml_mat *r, unsigned int i, unsigned int j)
{
	unsigned int	k;

	k = 0;
	while (k < r->rows)
	{
		if (!(k == i))
			nml_mat_row_addrow_r(r, k, i, -(r->data[k][j]));
		k++;
	}
}

t_nml_mat	*nml_mat_rref(t_nml_mat *m)
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
		nml_mat_rref_util(r, i, j);
		i++;
		j++;
	}
	return (r);
}
