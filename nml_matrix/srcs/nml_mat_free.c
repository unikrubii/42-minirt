/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:26:53 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/27 12:46:16 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Matrix deallocation
/// @param matrix
void	nml_mat_free(t_nml_mat *matrix)
{
	unsigned int	i;

	i = 0;
	while (i < matrix->rows)
	{
		free(matrix->data[i]);
		i++;
	}
	free(matrix->data);
	free(matrix);
}
