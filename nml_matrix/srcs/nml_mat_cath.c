/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_cath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:59:21 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/31 21:06:34 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Find the number of consecutive matrices
/// @param mnum
/// @param marr
/// @param lrow
/// @return
static int	find_cons_cols(unsigned int mnum, t_nml_mat **marr, \
	unsigned int lrow)
{
	unsigned int	k;
	int				ccols;

	k = 1;
	ccols = 0;
	while (k < mnum)
	{
		if (!marr[k])
			return (nml_error(__FILE__, __LINE__, "INCONSITENT_ARRAY"), -1);
		if (marr[k]->rows != lrow)
			return (nml_error(__FILE__, __LINE__, "CANNOT_CONCATENATE_H"), -2);
		ccols += marr[k]->cols;
		k++;
	}
	return (ccols);
}

/// @brief Fill the consecutive columns
/// @param marr
/// @param r
static void	fill_cons_cols(t_nml_mat **marr, t_nml_mat *r)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	unsigned int	offset;

	i = 0;
	while (i < r->rows)
	{
		k = 0;
		j = 0;
		offset = 0;
		while (j < r->cols)
		{
			if (marr[k]->cols == j - offset)
			{
				offset += marr[k]->cols;
				k++;
			}
			r->data[i][j] = marr[k]->data[i][j - offset];
			j++;
		}
		i++;
	}
}

/// @brief Concatinate matrices in horizontal align
/// @param mnum
/// @param marr
/// @return
t_nml_mat	*nml_mat_cath(unsigned int mnum, t_nml_mat **marr)
{
	unsigned int	lrow;
	unsigned int	ncols;
	int				ccols;
	t_nml_mat		*r;

	r = NULL;
	if (mnum == 0)
		return (NULL);
	if (mnum == 1)
		return (nml_mat_cp(marr[0]));
	lrow = marr[0]->rows;
	ncols = marr[0]->cols;
	ccols = find_cons_cols(mnum, marr, lrow);
	if (ccols < 0)
		return (NULL);
	ncols += ccols;
	r = nml_mat_new(lrow, ncols);
	if (r)
		fill_cons_cols(marr, r);
	return (r);
}
