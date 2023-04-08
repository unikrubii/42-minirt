/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_vect_dot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:43:54 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/08 20:04:42 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

float	nml_vect_dot(t_nml_mat *m1, unsigned int m1col, t_nml_mat *m2, \
	unsigned int m2col)
{
	unsigned int	i;
	float			dot;

	if (m1->rows != m2->rows)
		return (nml_error(__FILE__, __LINE__, "CANT_V_DOT_DIM"), -2147483648);
	if (m1col >= m1->cols || m2col >= m2->cols)
		return (nml_error(__FILE__, __LINE__, "CANT_GET_COLUMN"), -2147483648);
	i = 0;
	dot = 0.0f;
	while (i < m1->rows)
	{
		dot += m1->data[i][m1col] * m2->data[i][m2col];
		i++;
	}
	return (dot);
}
