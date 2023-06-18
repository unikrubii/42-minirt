/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtform.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:15:26 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 22:10:40 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtform.h"

/// @brief gt init
/// @param form
void	gt_init(t_gtform *form)
{
	form->bwdtfm = NULL;
	form->fwdtfm = NULL;
	form->fwd = NULL;
	form->bwd = NULL;
	form->gt_form_init = &gt_form_init;
	form->gt_form_deinit = &gt_deinit;
}

/// @brief gt deinit
/// @param form
void	gt_deinit(t_gtform *form)
{
	if (form->fwdtfm)
	{
		nml_mat_free(form->fwdtfm);
		form->fwdtfm = NULL;
	}
	if (form->bwdtfm)
	{
		nml_mat_free(form->bwdtfm);
		form->bwdtfm = NULL;
	}
	if (form->fwd)
	{
		nml_mat_free(form->fwd);
		form->fwd = NULL;
	}
	if (form->bwd)
	{
		nml_mat_free(form->bwd);
		form->bwd = NULL;
	}
	if (form)
	{
		free(form);
		form = NULL;
	}
}

/// @brief Construct gt_form from a pair of matrices
/// @param form
/// @param fwd
/// @param bwd
void	gt_form_init(t_gtform *form, t_nml_mat *fwd, t_nml_mat *bwd)
{
	if ((mateqdim_num(fwd, 4) && mateqdim_num(bwd, 4)))
	{
		form->fwdtfm = nml_mat_cp(fwd);
		form->bwdtfm = nml_mat_cp(bwd);
	}
}

/// @brief Set Transformation utils
/// @param calc
void	gt_set_trans_util(t_gtform_calc *calc)
{
	nml_mat_lup_free(calc->lup);
	nml_mat_free(calc->transm);
	nml_mat_free(calc->rotmx);
	nml_mat_free(calc->rotmy);
	nml_mat_free(calc->rotmz);
	nml_mat_free(calc->sclm);
}

/// @brief Set Transformation
/// @note 1 - Populate these with the appropriate values.
/// @note First the translation matrix
/// @note 2 - Combine to give the final forward transform matrix.
/// @param form
/// @param trans
/// @param rot
/// @param scale
void	gt_set_trans(t_gtform *form, t_nml_mat *trans, \
	t_nml_mat *rot, t_nml_mat *scale)
{
	t_gtform_calc	calc;

	calc.transm = nml_mat_eye(4);
	calc.rotmx = nml_mat_eye(4);
	calc.rotmy = nml_mat_eye(4);
	calc.rotmz = nml_mat_eye(4);
	calc.sclm = nml_mat_eye(4);
	set_trans_mat(calc.transm, trans);
	set_rotz_mat(calc.rotmz, rot);
	set_roty_mat(calc.rotmy, rot);
	set_rotx_mat(calc.rotmx, rot);
	set_scale_mat(calc.sclm, scale);
	calc.dot_tmp1 = nml_mat_dot(calc.transm, calc.sclm);
	calc.dot_tmp2 = nml_mat_dot(calc.dot_tmp1, calc.rotmx);
	nml_mat_free(calc.dot_tmp1);
	calc.dot_tmp1 = nml_mat_dot(calc.dot_tmp2, calc.rotmy);
	nml_mat_free(calc.dot_tmp2);
	calc.dot_tmp2 = nml_mat_dot(calc.dot_tmp1, calc.rotmz);
	form->fwdtfm = nml_mat_cp(calc.dot_tmp2);
	nml_mat_free(calc.dot_tmp1);
	nml_mat_free(calc.dot_tmp2);
	calc.lup = nml_mat_lup_solve(form->fwdtfm);
	form->bwdtfm = nml_mat_inv(calc.lup);
}
