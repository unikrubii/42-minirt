/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_trace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:53:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/02 17:23:58 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Matrix Trace
/// @param m
/// @return sum of diagonal value or -2147483648 incase matrix is not square
float	nml_mat_trace(t_nml_mat *m)
{
	unsigned int	i;
	float			trace;

	i = 0;
	trace = 0.0f;
	if (!m->is_square)
		return (nml_error(__FILE__, __LINE__, "CANNOT_TRACE"), -2147483648);
	while (i < m->rows)
	{
		trace += m->data[i][i];
		i++;
	}
	return (trace);
}
