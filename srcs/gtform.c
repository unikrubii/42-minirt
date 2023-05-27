/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtform.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:15:26 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/27 15:57:06 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtform.h"

void	set_trans_mat(t_nml_mat *mat, t_nml_mat *trans)
{
	nml_mat_set(mat, 0, 3, trans->data[0][0]);
	nml_mat_set(mat, 1, 3, trans->data[1][0]);
	nml_mat_set(mat, 2, 3, trans->data[2][0]);
}

void	set_rotz_mat(t_nml_mat *mat, t_nml_mat *rot)
{
	nml_mat_set(mat, 0, 0, cosf(rot->data[2][0]));
	nml_mat_set(mat, 0, 1, -sinf(rot->data[2][0]));
	nml_mat_set(mat, 1, 0, sinf(rot->data[2][0]));
	nml_mat_set(mat, 1, 1, cosf(rot->data[2][0]));
}

void	set_roty_mat(t_nml_mat *mat, t_nml_mat *rot)
{
	nml_mat_set(mat, 0, 0, cosf(rot->data[1][0]));
	nml_mat_set(mat, 0, 2, sinf(rot->data[1][0]));
	nml_mat_set(mat, 2, 0, -sinf(rot->data[1][0]));
	nml_mat_set(mat, 2, 2, cosf(rot->data[1][0]));
}

void	set_rotx_mat(t_nml_mat *mat, t_nml_mat *rot)
{
	nml_mat_set(mat, 1, 1, cosf(rot->data[0][0]));
	nml_mat_set(mat, 1, 2, -sinf(rot->data[0][0]));
	nml_mat_set(mat, 2, 1, sinf(rot->data[0][0]));
	nml_mat_set(mat, 2, 2, cosf(rot->data[0][0]));
}

void	set_scale_mat(t_nml_mat *mat, t_nml_mat *scale)
{
	nml_mat_set(mat, 0, 0, scale->data[0][0]);
	nml_mat_set(mat, 1, 1, scale->data[1][0]);
	nml_mat_set(mat, 2, 2, scale->data[2][0]);
}

int	mateqdim_num(t_nml_mat *mat, unsigned int size)
{
	t_nml_mat	*tmp;
	int			isfour;

	isfour = 0;
	tmp = nml_mat_sqr(size);
	isfour = nml_mat_eqdim(mat, tmp);
	free(tmp);
	return (isfour);
}

// Contructor / Deconstructor
void	gt_init(t_gtform *form)
{
	form->bwdtfm = NULL;
	form->fwdtfm = NULL;
	form->fwd = NULL;
	form->bwd = NULL;
	form->gt_form_init = &gt_form_init;
	form->gt_form_deinit = &gt_deinit;
}

void	gt_deinit(t_gtform *form)
{
	if (form->fwdtfm)
		nml_mat_free(form->fwdtfm);
	if (form->bwdtfm)
		nml_mat_free(form->bwdtfm);
	if (form->fwd)
		nml_mat_free(form->fwd);
	if (form->bwd)
		nml_mat_free(form->bwd);
	free(form);
}

// Construct from a pair of matrices
void	gt_form_init(t_gtform *form, t_nml_mat *fwd, t_nml_mat *bwd)
{
	// Verity the inputs are 4x4
	if ((mateqdim_num(fwd, 4) && mateqdim_num(bwd, 4)))
	{
		form->fwdtfm = nml_mat_cp(fwd);
		form->bwdtfm = nml_mat_cp(bwd);
	}
}

void	gt_set_trans(t_gtform *form, t_nml_mat *trans, t_nml_mat *rot, t_nml_mat *scale)
{
	// Define a matrix for each component of the transform
	t_nml_mat	*transm;
	t_nml_mat	*rotmx;
	t_nml_mat	*rotmy;
	t_nml_mat	*rotmz;
	t_nml_mat	*sclm;
	t_nml_mat	*dot_tmp1;
	t_nml_mat	*dot_tmp2;

	t_nml_mat_lup *lup;

	transm = nml_mat_eye(4);
	rotmx = nml_mat_eye(4);
	rotmy = nml_mat_eye(4);
	rotmz = nml_mat_eye(4);
	sclm = nml_mat_eye(4);

	// Populate these with the appropriate values.
	// First the translation matrix
	set_trans_mat(transm, trans);
	set_rotz_mat(rotmz, rot);
	set_roty_mat(rotmy, rot);
	set_rotx_mat(rotmx, rot);
	set_scale_mat(sclm, scale);

	nml_mat_print(transm);
	nml_mat_print(sclm);
	nml_mat_print(rotmx);
	nml_mat_print(rotmy);
	nml_mat_print(rotmz);


	// Combine to give the final forward transform matrix.
	dot_tmp1 = nml_mat_dot(transm, sclm);
	dot_tmp2 = nml_mat_dot(dot_tmp1, rotmx);
	nml_mat_free(dot_tmp1);
	dot_tmp1 = nml_mat_dot(dot_tmp2, rotmy);
	nml_mat_free(dot_tmp2);
	dot_tmp2 = nml_mat_dot(dot_tmp1, rotmz);

	// dot_tmp1 = nml_mat_dot(sclm, rotmx);
	// dot_tmp2 = nml_mat_dot(dot_tmp1, rotmy);
	// nml_mat_free(dot_tmp1);
	// dot_tmp1 = nml_mat_dot(dot_tmp2, rotmz);
	// nml_mat_free(dot_tmp2);
	// dot_tmp2 = nml_mat_dot(dot_tmp1, transm);

	form->fwdtfm = nml_mat_cp(dot_tmp2);
	nml_mat_free(dot_tmp1);
	nml_mat_free(dot_tmp2);

	nml_mat_print(form->fwdtfm);

	lup = nml_mat_lup_solve(form->fwdtfm);
	form->bwdtfm = nml_mat_inv(lup);

	nml_mat_print(form->bwdtfm);

	nml_mat_lup_free(lup);
}

// Function to return the transform metrices
t_nml_mat	*gt_get_fwd(t_gtform *form)
{
	return (form->fwdtfm);
}

t_nml_mat	*gt_get_bwd(t_gtform *form)
{
	return (form->bwdtfm);
}

t_ray	*ray_apply(t_gtform *form, t_ray *ray, int dir)
{
	// Create an object output
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

t_gtform	*gt_form_mult(t_gtform *lhs, t_gtform *rhs)
{
	t_nml_mat		*fwdres;
	t_nml_mat		*bwdres;
	t_nml_mat_lup	*lup;
	t_gtform		*finalres;

	finalres = NULL;
	// Form the product of the two forward transition
	fwdres = nml_mat_dot(lhs->fwdtfm, rhs->fwdtfm);

	// Compute the backward transform as the forward transform
	lup = nml_mat_lup_solve(fwdres);
	bwdres = nml_mat_inv(lup);
	nml_mat_lup_free(lup);

	// Form the final result
	gt_init(finalres);
	finalres->gt_form_init(finalres, fwdres, bwdres);
	nml_mat_free(fwdres);
	nml_mat_free(bwdres);
	return (finalres);
}

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
