/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_col_row_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:24:07 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/01 02:25:23 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Get value from matrix[i][j]
/// @param matrix
/// @param i
/// @param j
/// @return float m[i][j]
float	nml_mat_get(t_nml_mat *matrix, unsigned int i, unsigned int j)
{
	return (matrix->data[i][j]);
}

/// @brief Get one column from matrix m
/// @param m matrix
/// @param col number of column start from 0
/// @return selected column
t_nml_mat	*nml_mat_col_get(t_nml_mat *m, unsigned int col)
{
	t_nml_mat		*r;
	unsigned int	j;

	j = 0;
	if (col >= m->cols)
		return (nml_error(__FILE__, __LINE__, "CANNOT_GET_COLUMN"), NULL);
	r = nml_mat_new(m->rows, 1);
	if (r)
	{
		while (j < r->rows)
		{
			r->data[j][0] = m->data[j][col];
			j++;
		}
	}
	return (r);
}

/// @brief Get one row from matrix m
/// @param m matrix
/// @param row number of row start from 0
/// @return selected row
t_nml_mat	*nml_mat_row_get(t_nml_mat *m, unsigned int row)
{
	t_nml_mat		*r;

	if (row >= m->rows)
		return (nml_error(__FILE__, __LINE__, "CANNOT_GET_ROW"), NULL);
	r = nml_mat_new(1, m->cols);
	if (r)
		ft_memcpy(r->data[0], m->data[row], m->cols * sizeof(*r->data[0]));
	return (r);
}
