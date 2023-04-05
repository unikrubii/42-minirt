/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_ls_solvefwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:15:33 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/05 22:18:41 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

t_nml_mat	*nml_ls_solvefwd(t_nml_mat *l, t_nml_mat *b)
{
	unsigned int	i;
	unsigned int	j;
	float			tmp;
	t_nml_mat		*x;

	x = nml_mat_new(l->cols, 1);
	i = 0;
	while (i < l->cols)
	{
		tmp = b->data[i][0];
		j = 0;
		while (j < i)
		{
			tmp -= l->data[i][j] * x->data[j][0];
			j++;
		}
		x->data[i][0] = tmp / l->data[i][i];
		i++;
	}
	return (x);
}
