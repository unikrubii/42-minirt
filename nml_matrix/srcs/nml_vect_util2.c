/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_vect_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:28:18 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/04 16:29:02 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief reset vector
/// @param matrix
void	reset_vect(t_nml_mat *matrix)
{
	matrix->data[0][0] = 0.0;
	matrix->data[1][0] = 0.0;
	matrix->data[2][0] = 0.0;
}
