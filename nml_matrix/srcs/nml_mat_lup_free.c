/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_lup_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:26:34 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 18:56:22 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Deallocate LUP structure
/// @param lup
void	nml_mat_lup_free(t_nml_mat_lup *lup)
{
	nml_mat_free(lup->_l);
	nml_mat_free(lup->_u);
	nml_mat_free(lup->_p);
	free(lup);
}
