/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_col_l2norm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:09:37 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 18:47:17 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Calculates the l2 norm for a colum in the matrix
/// @param m
/// @param col
/// @return
float	nml_mat_col_l2norm(t_nml_mat *m, unsigned int col)
{
	float			sum;
	unsigned int	i;

	if (col >= m->cols)
		return (nml_error(__FILE__, __LINE__, "CANT_COLUMN_L2NORM"), INT_MIN);
	i = 0;
	sum = 0;
	while (i < m->rows)
	{
		sum += (m->data[i][col] * m->data[i][col]);
		i++;
	}
	return (sqrt(sum));
}
