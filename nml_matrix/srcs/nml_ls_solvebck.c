/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_ls_solvebck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:09:06 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/08 18:16:19 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Back substition algorithm
/// Solves the linear system U *x = b
///
/// @note in case U is not an upper triangular matrix, the algorithm will try to
/// select only the upper triangular part of the matrix U and solve the system
/// with it
///
/// @note In case any of the diagonal elements (U[i][i]) are 0 the system cannot
/// be solved
///
/// @param u an upper triangular matrix of size NxN
/// @param b a column matrix of size Nx1
/// @return the solution column matrix of size Nx1
t_nml_mat	*nml_ls_solvebck(t_nml_mat *u, t_nml_mat *b)
{
	unsigned int	i;
	unsigned int	j;
	float			tmp;
	t_nml_mat		*x;

	x = nml_mat_new(u->cols, 1);
	i = u->cols;
	while (i--)
	{
		tmp = b->data[i][0];
		j = i;
		while (j < u->cols)
		{
			tmp -= u->data[i][j] * x->data[j][0];
			j++;
		}
		x->data[i][0] = tmp / u->data[i][i];
	}
	return (x);
}
