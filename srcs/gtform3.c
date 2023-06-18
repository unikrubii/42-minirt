/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtform3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:28:38 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 16:31:02 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtform.h"

/// @brief Apply transformation to ray
/// @param form
/// @param ray
/// @param dir
/// @return
t_ray	*ray_apply(t_gtform *form, t_ray *ray, int dir)
{
	t_ray		*opray;
	t_nml_mat	*point1;
	t_nml_mat	*point2;

	opray = malloc(sizeof(t_ray) * 1);
	if (dir == FWDFM)
	{
		point1 = gt_apply(form, ray->v_point1, FWDFM);
		point2 = gt_apply(form, ray->v_point2, FWDFM);
	}
	else
	{
		point1 = gt_apply(form, ray->v_point1, BWDFM);
		point2 = gt_apply(form, ray->v_point2, BWDFM);
	}
	ray_init(opray, point1, point2);
	nml_mat_free(point1);
	nml_mat_free(point2);
	return (opray);
}

/// @brief Apply geomatric transform with direction
/// @param form
/// @param v_inp
/// @param dir
/// @return
t_nml_mat	*gt_apply(t_gtform *form, t_nml_mat *v_inp, int dir)
{
	t_nml_mat	*vect4;
	t_nml_mat	*tmp;
	t_nml_mat	*resvect;

	vect4 = new_vector4();
	resvect = new_vector();
	set_vect4_frm_vect(vect4, v_inp);
	if (dir == FWDFM)
	{
		tmp = nml_mat_dot(form->fwdtfm, vect4);
	}
	else
	{
		tmp = nml_mat_dot(form->bwdtfm, vect4);
	}
	set_vect_frm_vect4(tmp, resvect);
	nml_mat_free(vect4);
	nml_mat_free(tmp);
	return (resvect);
}

/// @brief geometric multiplication
/// @note 1 - Form the product of the two forward transition
/// @note 2 - Compute the backward transform as the forward transform
/// @note 3 - Form the final result
/// @param lhs
/// @param rhs
/// @return
t_gtform	*gt_form_mult(t_gtform *lhs, t_gtform *rhs)
{
	t_nml_mat		*fwdres;
	t_nml_mat		*bwdres;
	t_nml_mat_lup	*lup;
	t_gtform		*finalres;

	finalres = NULL;
	fwdres = nml_mat_dot(lhs->fwdtfm, rhs->fwdtfm);
	lup = nml_mat_lup_solve(fwdres);
	bwdres = nml_mat_inv(lup);
	nml_mat_lup_free(lup);
	gt_init(finalres);
	finalres->gt_form_init(finalres, fwdres, bwdres);
	nml_mat_free(fwdres);
	nml_mat_free(bwdres);
	return (finalres);
}

/// @brief assign geometric transform
/// @param lhs
/// @param rhs
void	gt_form_assign(t_gtform *lhs, t_gtform *rhs)
{
	if (lhs != rhs)
	{
		nml_mat_free(lhs->fwdtfm);
		nml_mat_free(lhs->bwdtfm);
		lhs->fwdtfm = nml_mat_cp(rhs->fwdtfm);
		lhs->bwdtfm = nml_mat_cp(rhs->bwdtfm);
	}
}
