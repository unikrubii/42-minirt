/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_dot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:29:15 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/02 17:20:38 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Matrix dot product bewteen m1 and m2
/// @param m1
/// @param m2
/// @return New matrix with from dot product result of m1 and m2
t_nml_mat	*nml_mat_dot(t_nml_mat *m1, t_nml_mat *m2)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	t_nml_mat		*r;

	i = 0;
	if (!(m1->cols == m2->rows))
		return (nml_error(__FILE__, __LINE__, "CANNOT_MULITPLY"), NULL);
	r = nml_mat_new(m1->rows, m2->cols);
	while (i < r->rows)
	{
		j = 0;
		while (j < r->cols)
		{
			k = 0;
			while (k < m1->cols)
			{
				r->data[i][j] += m1->data[i][k] * m2->data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (r);
}
