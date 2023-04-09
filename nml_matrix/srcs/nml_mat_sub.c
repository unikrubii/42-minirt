/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:35:24 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/01 02:24:02 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Matrix substraction
/// @param m1
/// @param m2
/// @return New Matrix Subtraction Result
t_nml_mat	*nml_mat_sub(t_nml_mat *m1, t_nml_mat *m2)
{
	t_nml_mat	*r;

	r = nml_mat_cp(m1);
	if (!nml_mat_sub_r(r, m2))
		return (nml_mat_free(r), NULL);
	return (r);
}

/// @brief Matrix ref subtraction
/// @param m1
/// @param m2
/// @return 1 = success, 0 = failed
int	nml_mat_sub_r(t_nml_mat *m1, t_nml_mat *m2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!nml_mat_eqdim(m1, m2))
		return (nml_error(__FILE__, __LINE__, "CANNOT_SUBTRACT"), 0);
	while (i < m1->rows)
	{
		j = 0;
		while (j < m1->cols)
		{
			m1->data[i][j] -= m2->data[i][j];
			j++;
		}
		i++;
	}
	return (1);
}
