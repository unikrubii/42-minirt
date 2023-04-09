/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_sqr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:44:02 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/27 12:44:38 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

/// @brief Create square martix based on size x size
/// @param size
/// @return
t_nml_mat	*nml_mat_sqr(unsigned int size)
{
	return (nml_mat_new(size, size));
}
