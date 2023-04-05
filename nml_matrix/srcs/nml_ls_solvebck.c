/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_ls_solvebck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:09:06 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/05 22:16:03 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

t_nml_mat	*nml_ls_solvebck(t_nml_mat *u, t_nml_mat *b)
{
	unsigned int	i;
	unsigned int	j;
	float			tmp;
	t_nml_mat		*x;

	x = nml_mat_new(u->cols, 1);
	i = u->cols;
	while (i--)
	{
		tmp = b->data[i][0];
		j = i;
		while (j < u->cols)
		{
			tmp -= u->data[i][j] * x->data[j][0];
			j++;
		}
		x->data[i][0] = tmp / u->data[i][i];
	}
	return (x);
}
