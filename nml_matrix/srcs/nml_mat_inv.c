/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_inv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:31:24 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 18:55:42 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Invert Matrix Utility
/// @param lup
/// @param r
/// @param eye
/// @param n
static void	nml_mat_inv_util(t_nml_mat_lup *lup, t_nml_mat *r, \
	t_nml_mat *eye, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;
	t_nml_mat		*invx;
	t_nml_mat		*eyex;

	j = 0;
	while (j < n)
	{
		eyex = nml_mat_col_get(eye, j);
		invx = nml_ls_solve(lup, eyex);
		i = 0;
		while (i < invx->rows)
		{
			r->data[i][j] = invx->data[i][0];
			i++;
		}
		nml_mat_free(invx);
		nml_mat_free(eyex);
		j++;
	}
}

/// @brief Calculates the inverse of a matrix
/// @param lup
/// @return
t_nml_mat	*nml_mat_inv(t_nml_mat_lup *lup)
{
	unsigned int	n;
	t_nml_mat		*r;
	t_nml_mat		*eye;

	n = lup->_l->cols;
	r = nml_mat_sqr(n);
	eye = nml_mat_eye(lup->_u->rows);
	nml_mat_inv_util(lup, r, eye, n);
	nml_mat_free(eye);
	return (r);
}
