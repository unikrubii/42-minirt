/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_vect_normalize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 10:44:27 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/04 23:18:45 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Compute the length of the vector,known as the 'norm'
/// @param v
/// @return
float	nml_vect_norm(t_nml_mat *v)
{
	unsigned int		i;
	float	cumulative_sum;

	i = 0;
	cumulative_sum = 0.0;
	while (i < v->rows)
	{
		cumulative_sum += (v->data[i][0] * v->data[i][0]);
		i++;
	}
	return sqrt(cumulative_sum);
}

/// @brief Vector Normalization to the target
/// @param v
/// @return
int	nml_vect_normalize_r(t_nml_mat *v)
{
	float			norm;
	float			temp;
	unsigned int	i;

	i = 0;
	norm = nml_vect_norm(v);
	printf("hello\n");
	while (i < v->rows)
	{
		temp = v->data[i][0] * (1.0 / norm);
		v->data[i][0] = temp;
		i++;
	}
	return (1);
}

/// @brief Vector Normalization
/// @param v vector
/// @return new MAtrix
t_nml_mat	*nml_vect_normalize(t_nml_mat *v)
{
	t_nml_mat	*r;

	r = nml_mat_cp(v);
	if (!nml_vect_normalize_r(r))
		return (nml_mat_free(r), NULL);
	return (r);
}
