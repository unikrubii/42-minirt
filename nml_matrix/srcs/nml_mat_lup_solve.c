/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_lup_solve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:57:46 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/05 20:42:21 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

static void	nml_mat_pivot_lu(t_nml_mat_lup *r, unsigned int j, \
	unsigned int pivot, unsigned int *num_perm)
{
	if (pivot != j)
	{
		nml_mat_row_swap_r(r->_u, j, pivot);
		nml_mat_row_swap_r(r->_l, j, pivot);
		nml_mat_row_swap_r(r->_p, j, pivot);
		*num_perm += 1;
	}
}

static void	nml_mat_lup_solve_util(t_nml_mat *l, t_nml_mat *u, t_nml_mat_lup *r)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	pivot;
	unsigned int	num_perm;
	float			mult;

	j = 0;
	while (j < u->cols)
	{
		pivot = (unsigned int) nml_mat_absmaxr(u, j);
		if (fabs(u->data[pivot][j]) < NML_MIN_COEF)
			return (nml_error(__FILE__, __LINE__, "CANNOT_LU_MATRIX_SQUARE"));
		nml_mat_pivot_lu(r, j, pivot, &num_perm);
		i = j + 1;
		while (i < u->rows)
		{
			mult = u->data[i][j] / u->data[j][j];
			nml_mat_row_addrow_r(u, i, j, -mult);
			l->data[i][j] = mult;
			i++;
		}
		j++;
	}
	nml_mat_diag_set(l, 1.0);
	r->num_permutations = num_perm;
}

t_nml_mat_lup	*nml_mat_lup_solve(t_nml_mat *m)
{
	t_nml_mat		*l;
	t_nml_mat		*u;
	t_nml_mat		*p;
	t_nml_mat_lup	*r;

	if (!m->is_square)
		return (nml_error(__FILE__, __LINE__, "CANNOT_LU_MATRIX_SQUARE"), NULL);
	l = nml_mat_new(m->rows, m->cols);
	u = nml_mat_cp(m);
	p = nml_mat_eye(m->rows);
	if (!l || !u || !p)
		return (nml_error(__FILE__, __LINE__, "MALLOC_ERROR"), NULL);
	r = nml_mat_lup_new(l, u, p, 0);
	if (!r)
		return (nml_error(__FILE__, __LINE__, "MALLOC_ERROR"), NULL);
	nml_mat_lup_solve_util(l, u, r);
	return (r);
}
