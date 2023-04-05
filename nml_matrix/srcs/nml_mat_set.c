/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:32:40 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/28 22:00:30 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief
/// @param matrix
/// @param i
/// @param j
/// @param value
void	nml_mat_set(t_nml_mat *matrix, unsigned int i, unsigned int j, \
	float value)
{
	matrix->data[i][j] = value;
}

/// @brief Set all matrix's values
/// @param matrix
/// @param value
void	nml_mat_all_set(t_nml_mat *matrix, float value)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < matrix->rows)
	{
		j = 0;
		while (j < matrix->cols)
		{
			matrix->data[i][j] = value;
			j++;
		}
		i++;
	}
}

/// @brief Set diagonal value of matrix
/// @param m
/// @param value
/// @return
int	nml_mat_diag_set(t_nml_mat *m, float value)
{
	unsigned int	i;

	i = 0;
	if (!m->is_square)
		return (nml_error(__FILE__, __LINE__, "CANNOT_SET_DIAG"), 0);
	while (i < m->rows)
	{
		m->data[i][i] = value;
		i++;
	}
	return (1);
}
