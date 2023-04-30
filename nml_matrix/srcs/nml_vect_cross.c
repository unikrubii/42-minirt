/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_vect_cross.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 18:45:49 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 18:46:11 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

// A × B = (bz – cy)i – (az – cx)j + (ay – bx)k
// = (bz – cy)i + (cx – az)j + (ay – bx)k
t_nml_mat	*vect_cross(t_nml_mat *a, t_nml_mat *b)
{
	float		i;
	float		j;
	float		k;
	t_nml_mat	*new_vect;

	i = 0;
	j = 0;
	k = 0;
	i = (a->data[1][0] * b->data[2][0]) - (a->data[2][0] * b->data[1][0]);
	j = (a->data[2][0] * b->data[0][0]) - (a->data[0][0] * b->data[2][0]);
	k = (a->data[0][0] * b->data[1][0]) - (a->data[1][0] * b->data[0][0]);
	new_vect = nml_mat_new(3, 1);
	new_vect->data[0][0] = i;
	new_vect->data[1][0] = j;
	new_vect->data[2][0] = k;
	return (new_vect);
}
