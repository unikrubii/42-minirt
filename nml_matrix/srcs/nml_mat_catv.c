/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_catv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:01:04 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/02 21:08:36 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Find the number of consecutive rows
/// @param mnum
/// @param marr
/// @param lcol
/// @return
static int	find_cons_rows(unsigned int mnum, t_nml_mat **marr, \
	unsigned int lcol)
{
	unsigned int	i;
	int				nrows;

	i = 0;
	nrows = 0;
	while (i < mnum)
	{
		if (!marr[i])
			return (nml_error(__FILE__, __LINE__, "INCONSITENT_ARRAY"), -1);
		if (marr[i]->cols != lcol)
			return (nml_error(__FILE__, __LINE__, "CANNOT_CONCATENATE_V"), -2);
		nrows += marr[i]->rows;
		i++;
	}
	return (nrows);
}

/// @brief Fill the consecutive rows
/// @param marr
/// @param r
static void	fill_cons_rows(t_nml_mat **marr, t_nml_mat *r)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	unsigned int	offset;

	j = 0;
	while (j < r->cols)
	{
		offset = 0;
		k = 0;
		i = 0;
		while (i < r->rows)
		{
			if (marr[k]->rows == i - offset)
			{
				offset += marr[k]->rows;
				k++;
			}
			r->data[i][j] = marr[k]->data[i - offset][j];
			i++;
		}
		j++;
	}
}

/// @brief Matrix row concatination
/// @param mnum
/// @param marr
/// @return New matrix from row concatination result
t_nml_mat	*nml_mat_catv(unsigned int mnum, t_nml_mat **marr)
{
	unsigned int	lcol;
	unsigned int	nrows;
	t_nml_mat		*r;

	if (mnum == 0)
		return (NULL);
	if (mnum == 1)
		return (nml_mat_cp(marr[0]));
	lcol = marr[0]->cols;
	nrows = find_cons_rows(mnum, marr, lcol);
	r = nml_mat_new(nrows, lcol);
	if (r)
		fill_cons_rows(marr, r);
	return (r);
}
