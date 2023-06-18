/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtform2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:25:55 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 16:26:15 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtform.h"

/// @brief set transform matrix
/// @param mat
/// @param trans
void	set_trans_mat(t_nml_mat *mat, t_nml_mat *trans)
{
	nml_mat_set(mat, 0, 3, trans->data[0][0]);
	nml_mat_set(mat, 1, 3, trans->data[1][0]);
	nml_mat_set(mat, 2, 3, trans->data[2][0]);
}

/// @brief set rotation z matrix
/// @param mat
/// @param rot
void	set_rotz_mat(t_nml_mat *mat, t_nml_mat *rot)
{
	nml_mat_set(mat, 0, 0, cosf(rot->data[2][0]));
	nml_mat_set(mat, 0, 1, -sinf(rot->data[2][0]));
	nml_mat_set(mat, 1, 0, sinf(rot->data[2][0]));
	nml_mat_set(mat, 1, 1, cosf(rot->data[2][0]));
}

/// @brief set rotation y matrix
/// @param mat
/// @param rot
void	set_roty_mat(t_nml_mat *mat, t_nml_mat *rot)
{
	nml_mat_set(mat, 0, 0, cosf(rot->data[1][0]));
	nml_mat_set(mat, 0, 2, sinf(rot->data[1][0]));
	nml_mat_set(mat, 2, 0, -sinf(rot->data[1][0]));
	nml_mat_set(mat, 2, 2, cosf(rot->data[1][0]));
}

/// @brief set rotation x matrix
/// @param mat
/// @param rot
void	set_rotx_mat(t_nml_mat *mat, t_nml_mat *rot)
{
	nml_mat_set(mat, 1, 1, cosf(rot->data[0][0]));
	nml_mat_set(mat, 1, 2, -sinf(rot->data[0][0]));
	nml_mat_set(mat, 2, 1, sinf(rot->data[0][0]));
	nml_mat_set(mat, 2, 2, cosf(rot->data[0][0]));
}

/// @brief set scale matrix
/// @param mat
/// @param scale
void	set_scale_mat(t_nml_mat *mat, t_nml_mat *scale)
{
	nml_mat_set(mat, 0, 0, scale->data[0][0]);
	nml_mat_set(mat, 1, 1, scale->data[1][0]);
	nml_mat_set(mat, 2, 2, scale->data[2][0]);
}
