/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_pivot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:24:29 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/02 20:11:56 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Finds the first non-zero element on the col column,
/// under the row row. This is used to determine the pivot in gauss Elimination
/// If not pivot is found, returns -1
/// @param m
/// @param col
/// @param row
/// @return
// int	nml_mat_pivotidx(t_nml_mat *m, unsigned int col, unsigned int row)
// {
// 	unsigned int	i;

// 	(void) row;
// 	i = 0;
// 	while (i < m->rows)
// 	{
// 		if (fabs(m->data[i][col]) > NML_MIN_COEF)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

/// @brief Find the max element from the column "col" under the row "row"
/// This is needed to pivot in Gauss-Jordan elimination
/// If pivot is not found, return -1
/// @param m
/// @param col
/// @param row
/// @return
int	nml_mat_pivotmaxidx(t_nml_mat *m, unsigned int col, unsigned int row)
{
	unsigned int	i;
	unsigned int	maxi;
	float			micol;
	float			max;

	i = 0;
	maxi = row;
	max = fabs(m->data[row][col]);
	while (i < m->rows)
	{
		micol = fabs(m->data[i][col]);
		if (micol > max)
		{
			max = micol;
			maxi = i;
		}
		i++;
	}
	if (max < NML_MIN_COEF)
		return (-1);
	return (maxi);
}
