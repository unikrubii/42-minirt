/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_ls_solve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:11:30 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/08 18:47:15 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief A[n][n] is a square matrix
/// m contains matrices L, U, P for A[n][n] so that P*A = L*U
/// @note linear system is: A*x=b  =>  P*A*x = P*b  =>  L*U*x = P*b  =>
/// @note (where b is a matrix[n][1], and x is a matrix[n][1])
/// @note if y = U*x , we solve two systems:
/// @note L * y = P b (forward substition)
/// @note U * x = y (backward substition)
/// @param lu
/// @param b
/// @return
t_nml_mat	*nml_ls_solve(t_nml_mat_lup *lu, t_nml_mat *b)
{
	t_nml_mat	*pb;
	t_nml_mat	*y;
	t_nml_mat	*x;

	if (lu->_u->rows != b->rows || b->cols != 1)
		return (nml_error(__FILE__, __LINE__, "CANT_SOL_LS_INVALID_B"), NULL);
	pb = nml_mat_dot(lu->_p, b);
	y = nml_ls_solvefwd(lu->_l, pb);
	x = nml_ls_solvebck(lu->_u, y);
	nml_mat_free(y);
	nml_mat_free(pb);
	return (x);
}
