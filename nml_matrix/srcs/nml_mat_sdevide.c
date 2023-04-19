/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_devide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 23:24:48 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/19 23:37:51 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Divide all value in matrix m with num
/// and return new multiplied matrix
/// @param m
/// @param num
/// @return
t_nml_mat	*nml_mat_sdevide(t_nml_mat *m, float num)
{
	t_nml_mat	*r;

	if (num == 0.0f)
		return (NULL);
	r = nml_mat_cp(m);
	nml_mat_sdevide_r(r, num);
	return (r);
}

/// @brief Divide all value in matrix m with num
/// @param m
/// @param num
/// @return
int	nml_mat_sdevide_r(t_nml_mat *m, float num)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (num == 0.0f)
		return (-1);
	while (i < m->rows)
	{
		j = 0;
		while (j < m->cols)
		{
			m->data[i][j] /= num;
			j++;
		}
		i++;
	}
	return (1);
}
