/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_from.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:19:32 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 18:52:06 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Dynamically allocates a new matrix struct.
/// Initialise the matrix by reading values from a vector
/// @param num_rows
/// @param num_cols
/// @param n_vals
/// @param vals
/// @return
t_nml_mat	*nml_mat_from(unsigned int num_rows, unsigned int num_cols, \
	unsigned int n_vals, float *vals)
{
	t_nml_mat		*m;
	unsigned int	i;
	unsigned int	j;
	unsigned int	v_idx;

	i = 0;
	m = nml_mat_new(num_rows, num_cols);
	while (i < m->rows)
	{
		j = 0;
		while (j < m->cols)
		{
			v_idx = (i * m->cols) + j;
			m->data[i][j] = 0.0f;
			if (v_idx < n_vals)
				m->data[i][j] = vals[v_idx];
			j++;
		}
		i++;
	}
	return (m);
}
