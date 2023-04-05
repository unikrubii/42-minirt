/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:09:13 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/28 21:59:58 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Print matrix on the terminal
/// @param matrix
void	nml_mat_print(t_nml_mat *matrix)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	printf("\n");
	while (i < matrix->rows)
	{
		j = 0;
		while (j < matrix->cols)
		{
			printf("%lf\t\t", matrix->data[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}
