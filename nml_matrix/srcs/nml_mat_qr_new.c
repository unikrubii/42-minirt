/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_qr_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:43:02 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/08 20:46:02 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

t_nml_mat_qr	*nml_mat_qr_new(void)
{
	t_nml_mat_qr	*qr;

	qr = malloc(sizeof(*qr));
	np_check(qr);
	return(qr);
}
