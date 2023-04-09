/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_ls_solvefwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:15:33 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/08 18:16:43 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Forward substitution algorithm
/// Solves the linear system L * x = b\
///
/// @note In case L is not a lower triangular matrix, the algorithm will try to
/// select only the lower triangular part of the matrix L and solve the system
/// with it.
///
/// @note In case any of the diagonal elements (L[i][i]) are 0 the system cannot
/// be solved
///
/// @note function is usually used with an L matrix from a LU decomposition
/// @param l lower triangular matrix of size NxN
/// @param b column matrix of size Nx1
/// @return the solution column matrix of size Nx1
t_nml_mat	*nml_ls_solvefwd(t_nml_mat *l, t_nml_mat *b)
{
	unsigned int	i;
	unsigned int	j;
	float			tmp;
	t_nml_mat		*x;

	x = nml_mat_new(l->cols, 1);
	i = 0;
	while (i < l->cols)
	{
		tmp = b->data[i][0];
		j = 0;
		while (j < i)
		{
			tmp -= l->data[i][j] * x->data[j][0];
			j++;
		}
		x->data[i][0] = tmp / l->data[i][i];
		i++;
	}
	return (x);
}
