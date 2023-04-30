/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_util.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:15:57 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 09:03:22 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v_util.h"
#include "minirt.h"
#include "nml_matrix.h"

t_nml_mat	*new_vector(void)
{
	return (nml_mat_new(3,1));
}

void	set_vect(t_nml_mat *vect, float u, float v, float w)
{
	vect->data[0][0] = u;
	vect->data[1][0] = v;
	vect->data[2][0] = w;
}

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

void	vect_print(t_nml_mat *vect)
{
	printf("%2.2f\n%2.2f\n%2.2f\n", vect->data[0][0], vect->data[1][0], vect->data[2][0]);
}
