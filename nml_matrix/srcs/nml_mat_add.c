/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 21:08:21 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/31 23:34:27 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Matrix adding, return new matrix
/// @param m1
/// @param m2
/// @return
t_nml_mat	*nml_mat_add(t_nml_mat *m1, t_nml_mat *m2)
{
	t_nml_mat	*r;

	r = nml_mat_cp(m1);
	if (!nml_mat_add_r(r, m2))
		return (nml_mat_free(r), NULL);
	return (r);
}

/// @brief Adding reference matrix m1 with matrix m2
/// @param m1
/// @param m2
/// @return
int	nml_mat_add_r(t_nml_mat *m1, t_nml_mat *m2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!nml_mat_eqdim(m1, m2))
		return (nml_error(__FILE__, __LINE__, "CANNOT_ADD"), 0);
	while (i < m1->rows)
	{
		j = 0;
		while (j < m1->cols)
		{
			m1->data[i][j] += m2->data[i][j];
			j++;
		}
		i++;
	}
	return (0);
}
