/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_absmaxr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:15:40 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/04 10:47:36 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Finds the maxid on the column (starting from k -> num_rows)
/// This method is used for pivoting in LUP decomposition
/// @param m
/// @param k
/// @return
int	nml_mat_absmaxr(t_nml_mat *m, unsigned int k)
{
	unsigned int	i;
	float			max;
	int				max_idx;

	i = k + 1;
	max_idx = k;
	max = m->data[k][k];
	while (i < m->rows)
	{
		if (fabs(m->data[i][k]) > max)
		{
			max = fabs(m->data[i][k]);
			max_idx = i;
		}
		i++;
	}
	return (max_idx);
}
