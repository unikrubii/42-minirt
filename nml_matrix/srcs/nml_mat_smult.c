/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_smult.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:08:47 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/29 11:11:20 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Multiply all value in matrix m with num
/// and return new multiplied matrix
/// @param m
/// @param num
/// @return
t_nml_mat	*nml_mat_smult(t_nml_mat *m, float num)
{
	t_nml_mat	*r;

	r = nml_mat_cp(m);
	nml_mat_smult_r(r, num);
	return (r);
}

/// @brief Multiply all value in matrix m with num
/// @param m
/// @param num
/// @return
int	nml_mat_smult_r(t_nml_mat *m, float num)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < m->rows)
	{
		j = 0;
		while (j < m->cols)
		{
			m->data[i][j] *= num;
			j++;
		}
		i++;
	}
	return (1);
}
