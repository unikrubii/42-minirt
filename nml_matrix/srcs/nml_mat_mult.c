/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_mult.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:27:25 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/28 22:01:21 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Multiply row in new matrix
/// @param m
/// @param row
/// @param num
/// @return
t_nml_mat	*nml_mat_row_mult(t_nml_mat *m, unsigned int row, float num)
{
	t_nml_mat	*r;

	r = nml_mat_cp(m);
	if (!nml_mat_row_mult_r(r, row, num))
		return (nml_mat_free(r), NULL);
	return (r);
}

/// @brief Multiply row in reference matrix
/// @param m
/// @param row
/// @param num
/// @return
int	nml_mat_row_mult_r(t_nml_mat *m, unsigned int row, float num)
{
	unsigned int	i;

	i = 0;
	if (row >= m->rows)
		return (nml_error(__FILE__, __LINE__, "CANNOT_ROW_MULTIPLY"), 0);
	while (i < m->cols)
	{
		m->data[row][i] *= num;
		i++;
	}
	return (1);
}

/// @brief Multiply column in new matrix
/// @param m
/// @param col
/// @param num
/// @return
t_nml_mat	*nml_mat_col_mult(t_nml_mat *m, unsigned int col, float num)
{
	t_nml_mat	*r;

	r = nml_mat_cp(m);
	if (!nml_mat_col_mult_r(r, col, num))
		return (nml_mat_free(r), NULL);
	return (r);
}

/// @brief Multiply column in reference matrix
/// @param m
/// @param col
/// @param num
/// @return
int	nml_mat_col_mult_r(t_nml_mat *m, unsigned int col, float num)
{
	unsigned int	i;

	i = 0;
	if (col >= m->cols)
		return (nml_error(__FILE__, __LINE__, "CANNOT_COL_MULTIPLY"), 0);
	while (i < m->rows)
	{
		m->data[i][col] *= num;
		i++;
	}
	return (1);
}
