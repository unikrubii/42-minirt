/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_vect4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:11:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/20 13:17:05 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

t_nml_mat	*new_vector4(void)
{
	return (nml_mat_new(4, 1));
}

void	set_vect4(t_nml_mat *vect, float u, float v, float w)
{
	vect->data[0][0] = u;
	vect->data[1][0] = v;
	vect->data[2][0] = w;
	vect->data[3][0] = 1;
}

void	set_vect4_frm_vect(t_nml_mat *vect4, t_nml_mat *vect3)
{
	vect4->data[0][0] = vect3->data[0][0];
	vect4->data[1][0] = vect3->data[1][0];
	vect4->data[2][0] = vect3->data[2][0];
	vect4->data[3][0] = 1;
}

void	set_vect_frm_vect4(t_nml_mat *vect4, t_nml_mat *vect3)
{
	vect3->data[0][0] = vect4->data[0][0];
	vect3->data[1][0] = vect4->data[1][0];
	vect3->data[2][0] = vect4->data[2][0];
}
