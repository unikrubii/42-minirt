/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_util.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 08:17:12 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/23 17:01:26 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_UTIL_H
# define V_UTIL_H

# include "nml_matrix.h"

void		set_vect(t_nml_mat *vect, float u, float v, float w);
t_nml_mat	*vect_cross(t_nml_mat *a, t_nml_mat *b);
void		vect_print(t_nml_mat *vect);

#endif
