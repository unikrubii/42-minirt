/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_equal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:56:44 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/27 12:49:35 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Matrices dimension equality checker
/// @param m1 Matrix 1
/// @param m2 Matrix 2
/// @return
int	nml_mat_eqdim(t_nml_mat *m1, t_nml_mat *m2)
{
	return ((m1->cols == m2->cols) && (m1->rows == m2->rows));
}

/// @brief Matrices identical checker
/// @param m1 Matrix 1
/// @param m2 Matrix 2
/// @param tolerance Acceptable tolerance
/// @return
int	nml_mat_eq(t_nml_mat *m1, t_nml_mat *m2, float tolerance)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!nml_mat_eqdim(m1, m2))
		return (0);
	while (i < m1->rows)
	{
		j = 0;
		while (j < m1->cols)
		{
			if (fabs(m1->data[i][j] - m2->data[i][j]) > tolerance)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
