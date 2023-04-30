/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_lup_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:27:38 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 18:56:58 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Print LUP Structure
/// @param lup
void	nml_mat_lup_print(t_nml_mat_lup *lup)
{
	printf("L:\n");
	nml_mat_print(lup->_l);
	printf("U:\n");
	nml_mat_print(lup->_u);
	printf("P:\n");
	nml_mat_print(lup->_p);
}
