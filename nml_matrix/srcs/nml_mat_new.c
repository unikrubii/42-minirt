/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:40:16 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/27 14:27:52 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Allocation new matrix rows x cols
/// @param num_rows
/// @param num_cols
/// @return
t_nml_mat	*nml_mat_new(unsigned int num_rows, unsigned int num_cols)
{
	t_nml_mat		*m;
	unsigned int	i;

	i = 0;
	if (num_rows <= 0)
		return (nml_error(__FILE__, __LINE__, "INVALID ROWS"), NULL);
	if (num_cols <= 0)
		return (nml_error(__FILE__, __LINE__, "INVALID COLS"), NULL);
	m = ft_calloc(1, sizeof(*m));
	np_check(m);
	m->rows = num_rows;
	m->cols = num_cols;
	m->is_square = 0;
	if (num_rows == num_cols)
		m->is_square = 1;
	m->data = ft_calloc(m->rows, sizeof(*m->data));
	np_check(m->data);
	while (i < m->rows)
	{
		m->data[i] = ft_calloc(m->cols, sizeof(**m->data));
		np_check(m->data[i++]);
	}
	return (m);
}

/// @brief Initialise the matrix by copying another one
/// @param m
/// @return
t_nml_mat	*nml_mat_cp(t_nml_mat *m)
{
	unsigned int	i;
	unsigned int	j;
	t_nml_mat		*r;

	i = 0;
	j = 0;
	r = nml_mat_new(m->rows, m->cols);
	while (i < r->rows)
	{
		j = 0;
		while (j < r->cols)
		{
			r->data[i][j] = m->data[i][j];
			j++;
		}
		i++;
	}
	return (r);
}
