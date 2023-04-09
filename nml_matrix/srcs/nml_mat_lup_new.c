/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_mat_lup_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:11:27 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/05 13:25:58 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_matrix.h"

t_nml_mat_lup	*nml_mat_lup_new(t_nml_mat *l, t_nml_mat *u, t_nml_mat *p, \
	unsigned int num_permutations)
{
	t_nml_mat_lup	*r;

	r = malloc(sizeof(*r));
	if (!r)
		return (nml_error(__FILE__, __LINE__, "MALLOC ERROR"), NULL);
	r->_l = l;
	r->_u = u;
	r->_p = p;
	r->num_permutations = num_permutations;
	return (r);
}
