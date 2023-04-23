/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_l2norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:30:34 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/23 17:48:57 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

t_nml_mat	*nml_mat_l2norm(t_nml_mat *m)
{
	unsigned int	i;
	unsigned int	j;
	t_nml_mat		*r;
	float			sq_sum;

	j = 0;
	r = NULL;
	r = nml_mat_new(1, m->cols);
	while (j < m->cols)
	{
		i = 0;
		sq_sum = 0;
		while (i < m->rows)
		{
			sq_sum += m->data[i][j] * m->data[i][j];
			i++;
		}
		r->data[0][j] = sqrt(sq_sum);
		j++;
	}
	return (r);
}
