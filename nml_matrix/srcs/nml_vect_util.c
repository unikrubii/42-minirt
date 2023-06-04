/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_vect_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:36:13 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/03 17:20:14 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief allocate new vector in matrix form
/// @param
/// @return
t_nml_mat	*new_vector(void)
{
	return (nml_mat_new(3, 1));
}

/// @brief set value of vector
/// @param vect
/// @param u
/// @param v
/// @param w
void	set_vect(t_nml_mat *vect, float u, float v, float w)
{
	vect->data[0][0] = u;
	vect->data[1][0] = v;
	vect->data[2][0] = w;
}

void	vect_print(t_nml_mat *vect)
{
	printf("%2.2f\n%2.2f\n%2.2f\n", vect->data[0][0], \
		vect->data[1][0], vect->data[2][0]);
}

/// @brief get vector value
/// @param vect
/// @param pos
/// @return
float	vect_get(t_nml_mat *vect, int pos)
{
	if (vect)
		return (vect->data[pos][0]);
	return (0.0);
}
