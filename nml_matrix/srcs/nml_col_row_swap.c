/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_col_row_swap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:13:19 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/31 18:46:19 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Create new matrix from m with row swapped between row1 and row2
/// @param m
/// @param row1
/// @param row2
/// @return
t_nml_mat	*nml_mat_row_swap(t_nml_mat *m, unsigned int row1, \
	unsigned int row2)
{
	t_nml_mat	*r;

	r = nml_mat_cp(m);
	if (!nml_mat_row_swap_r(r, row1, row2))
	{
		return (nml_mat_free(r), NULL);
	}
	return (r);
}

/// @brief Swap the reference matrix m between row1 and row2
/// @param m
/// @param row1
/// @param row2
/// @return
int	nml_mat_row_swap_r(t_nml_mat *m, unsigned int row1, unsigned int row2)
{
	float	*tmp;

	if (row1 >= m->rows || row2 >= m->rows)
		return (nml_error(__FILE__, __LINE__, "CANNOT_SWAP_ROWS"), 0);
	tmp = m->data[row2];
	m->data[row2] = m->data[row1];
	m->data[row1] = tmp;
	return (1);
}

/// @brief Create new matrix from m with row swapped between col1 and col2
/// @param m
/// @param col1
/// @param col2
/// @return
t_nml_mat	*nml_mat_col_swap(t_nml_mat *m, unsigned int col1, \
	unsigned int col2)
{
	t_nml_mat	*r;

	r = nml_mat_cp(m);
	if (!nml_mat_col_swap_r(r, col1, col2))
	{
		return (nml_mat_free(r), NULL);
	}
	return (r);
}

/// @brief Swap the reference matrix m between col1 and col2
/// @param m
/// @param col1
/// @param col2
/// @return
int	nml_mat_col_swap_r(t_nml_mat *m, unsigned int col1, unsigned int col2)
{
	float			tmp;
	unsigned int	j;

	j = 0;
	if (col1 >= m->cols || col2 >= m->cols)
		return (nml_error(__FILE__, __LINE__, "CANNOT_SWAP_COLS"), 0);
	while (j < m->rows)
	{
		tmp = m->data[j][col1];
		m->data[j][col1] = m->data[j][col2];
		m->data[j][col2] = tmp;
		j++;
	}
	return (1);
}
