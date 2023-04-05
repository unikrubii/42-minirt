/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_col_row_rem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:45:55 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/31 20:00:28 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Allocate a specified column removed from matrix m
///	need to free m manualy
/// @param m
/// @param column
/// @return
t_nml_mat	*nml_mat_col_rem(t_nml_mat *m, unsigned int column)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	t_nml_mat		*r;

	i = 0;
	if (column >= m->cols)
		return (nml_error(__FILE__, __LINE__, "CANNOT_REMOVE_COLUMN"), NULL);
	r = nml_mat_new(m->rows, m->cols - 1);
	while (i < m->rows)
	{
		j = 0;
		k = 0;
		while (j < m->cols)
		{
			if (column != j)
				r->data[i][k++] = m->data[i][j];
			j++;
		}
		i++;
	}
	return (r);
}

/// @brief Allocate a specified row removed from matrix m
///	need to free m manualy
/// @param m
/// @param row
/// @return
t_nml_mat	*nml_mat_row_rem(t_nml_mat *m, unsigned int row)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	t_nml_mat		*r;

	i = 0;
	k = 0;
	if (row >= m->rows)
		return (nml_error(__FILE__, __LINE__, "CANNOT_REMOVE_ROW"), NULL);
	r = nml_mat_new(m->rows - 1, m->cols);
	while (i < m->rows)
	{
		if (row != i)
		{
			j = 0;
			while (j < m->cols)
			{
				r->data[k][j] = m->data[i][j];
				j++;
			}
			k++;
		}
		i++;
	}
	return (r);
}
