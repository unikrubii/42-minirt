/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_qr_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:46:30 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/08 20:47:37 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

void	nml_mat_qr_free(t_nml_mat_qr *qr)
{
	nml_mat_free(qr->_q);
	nml_mat_free(qr->_r);
	free(qr);
}
