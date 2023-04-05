/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_det.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:34:17 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/05 21:36:28 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief After the LU(P) factorisation the det can be easily calculated
/// by multiplying the main diagonal of matrix U with the sign.
/// the sign is -1 if the number of permutations is odd
/// the sign is +1 if the number of permutations is even
/// @param lup
/// @return determinant of the matrix
float	nml_mat_det(t_nml_mat_lup *lup)
{
	unsigned int	k;
	int				sign;
	float			product;
	t_nml_mat		*u;

	k = 0;
	sign = -1;
	product = 1.0;
	u = lup->_u;
	if (lup->num_permutations % 2 == 0)
		sign = 1;
	while (k < u->rows)
	{
		product *= u->data[k][k];
		k++;
	}
	return (sign * product);
}
