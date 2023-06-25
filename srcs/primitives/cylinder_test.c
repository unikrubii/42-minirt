/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 20:55:38 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 22:49:00 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objectbase.h"

void	cylinder_init(t_objbase *obj)
{
	(void) obj;
}

void	cylinder_deinit(t_objbase *obj)
{
	(void) obj;
}

void	cylinder_compute_values(t_inter_calc *calc, t_scene *scn, \
	t_objbase *obj)
{
	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);
	calc->vhat = nml_mat_cp(calc->bck_ray->v_lab);
	nml_vect_normalize_r(calc->vhat);
	calc->vtmp = nml_mat_cp(calc->bck_ray->v_lab);
	calc->a = powf(calc->vtmp->data[0][0], 2.0) + powf(calc->vtmp->data[1][0], 2.0);
	calc->b = 2.0 * ((calc->vtmp->data[0][0] * calc->vhat->data[0][0]) + (calc->vtmp->data[1][0] * calc->vhat->data[1][0]));
	calc->c = powf(calc->vtmp->data[0][0], 2.0) + powf(calc->vtmp->data[1][0], 2.0) - 1.0;
	calc->num_sqrt = sqrtf(powf(calc->b, 2.0) - (4 * calc->a * calc->c));
	nml_mat_free(calc->vtmp);
}

void	cyl_init_att(t_inter_calc *cyl)
{
	cyl->t1_valid = 0;
	cyl->t2_valid = 0;
	cyl->t3_valid = 0;
	cyl->t4_valid = 0;
	cyl->v_poi = new_vector();
	cyl->v_obj_org = new_vector();
	// cyl->poi[0] = new_vector();
	// cyl->poi[1] = new_vector();
	cyl->poi[2] = new_vector();
	cyl->poi[3] = new_vector();
	cyl->tt[0] = 0.0;
	cyl->tt[1] = 0.0;
	cyl->tt[2] = 0.0;
	cyl->tt[3] = 0.0;
	set_vect(cyl->v_obj_org, 0.0, 0.0, 0.0);
}

void	cyl_inter_test(t_inter_calc *cyl)
{
	// There was an intersection
	// Compute the values for t
	cyl->tt[0] = (-cyl->b + cyl->num_sqrt) / (2 * cyl->a);
	cyl->tt[1] = (-cyl->b - cyl->num_sqrt) / (2 * cyl->a);

	// Compute the points of intersection
	cyl->poi[0] = nml_mat_smult(cyl->vhat, cyl->tt[0]);
	nml_mat_add_r(cyl->poi[0], cyl->bck_ray->v_point1);
	cyl->poi[1] = nml_mat_smult(cyl->vhat, cyl->tt[1]);
	nml_mat_add_r(cyl->poi[1], cyl->bck_ray->v_point1);

	// check if any of these are valid.
	if ((cyl->tt[0] > 0.0) && (fabs(cyl->poi[0]->data[2][0]) < 1.0))
	{
		cyl->t1_valid = 1;
	}
	else
	{
		cyl->t1_valid = 0;
		cyl->tt[0] = 100e6;
	}

	if ((cyl->tt[1] > 0.0) && (fabs(cyl->poi[1]->data[2][0]) < 1.0))
	{
		cyl->t2_valid = 1;
	}
	else
	{
		cyl->t2_valid = 0;
		cyl->tt[1] = 100e6;
	}
}

void	cyl_comp_caps(t_inter_calc *cyl)
{
	// compute the points of intersection.
	cyl->poi[2] = nml_mat_smult(cyl->vhat, cyl->tt[2]);
	nml_mat_add_r(cyl->poi[2], cyl->bck_ray->v_point1);
	cyl->poi[3] = nml_mat_smult(cyl->vhat, cyl->tt[3]);
	nml_mat_add_r(cyl->poi[3], cyl->bck_ray->v_point1);

	// Check if these are valid
	if ((cyl->tt[2] > 0.0) && (sqrtf(powf(cyl->poi[2]->data[0][0], 2.0) + powf(cyl->poi[2]->data[1][0], 2.0)) < 1.0))
	{
		cyl->t3_valid = 1;
	}
	else
	{
		cyl->t3_valid = 0;
		cyl->tt[2] = 100e6;
	}
	if ((cyl->tt[3] > 0.0) && (sqrtf(powf(cyl->poi[3]->data[0][0], 2.0) + powf(cyl->poi[3]->data[1][0], 2.0)) < 1.0))
	{
		cyl->t4_valid = 1;
	}
	else
	{
		cyl->t4_valid = 0;
		cyl->tt[3] = 100e6;
	}
}

void	cyl_close_enough(t_inter_calc *cyl)
{
	if (obj_close_enough(cyl->vhat->data[2][0], 0.0))
	{
		cyl->t3_valid = 0;
		cyl->t4_valid = 0;
		cyl->tt[2] = 100e6;
		cyl->tt[3] = 100e6;
	}
	else
	{
		cyl->tt[2] = (cyl->bck_ray->v_point1->data[2][0] - 1.0) / -cyl->vhat->data[2][0];
		cyl->tt[3] = (cyl->bck_ray->v_point1->data[2][0] + 1.0) / -cyl->vhat->data[2][0];
		cyl_comp_caps(cyl);
	}
}

void	cyl_get_min(t_inter_calc *cyl)
{
	int	i;

	i = 0;
	cyl->min_i = 0;
	cyl->min_t = 10e6;
	while (i < 4)
	{
		if (cyl->tt[i] < cyl->min_t)
		{
			cyl->min_t = cyl->tt[i];
			cyl->min_i = i;
		}
		i++;
	}
}

int	cyl_not_side_inter(t_objbase *obj, t_scene *scn, t_inter_calc *cyl)
{
	if (!obj_close_enough(cyl->vhat->data[2][0], 0.0))
	{
		if (sqrtf(pow(cyl->valid_poi->data[0][0], 2) + \
			pow(cyl->valid_poi->data[1][0], 2)) < 1.0)
		{
			scn->v_intpoint = gt_apply(obj->transmat, cyl->valid_poi, FWDFM);
			set_vect(cyl->org_normal, 0.0, 0.0, 0.0 + \
				cyl->valid_poi->data[2][0]);
			cyl->global_origin = gt_apply(obj->transmat, \
				cyl->local_origin, FWDFM);
			scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, \
				cyl->org_normal, FWDFM), cyl->global_origin);
			nml_mat_normalize_r(scn->v_lc_norm);
			scn->v_lc_color = nml_mat_cp(obj->v_base_color);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	cyl_side_inter(t_objbase *obj, t_scene *scn, t_inter_calc *cyl)
{
	cyl->local_origin = new_vector();
	set_vect(cyl->local_origin, 0.0, 0.0, 0.0);
	cyl->org_normal = new_vector();
	cyl->v_obj_norg = new_vector();
	cyl->v_obj_gorg = new_vector();
	cyl->valid_poi = nml_mat_cp(cyl->poi[cyl->min_i]);
	// if the min index is either 0 or 1, then we have a valid intersection
	// with the cylinder itself
	if (cyl->min_i < 2)
	{
		// scn->v_intpoint = gt_apply(obj->transmat, \
		// 	cyl->valid_poi, FWDFM);
		// cyl->global_origin = gt_apply(obj->transmat, \
		// 	cyl->local_origin, FWDFM);
		// set_vect(cyl->org_normal, cyl->valid_poi->data[0][0], \
		// 	cyl->valid_poi->data[1][0], 0.0);
		// scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, \
		// 	cyl->org_normal, FWDFM), cyl->global_origin);
		// nml_mat_normalize_r(scn->v_lc_norm);
		// scn->v_lc_color = nml_mat_cp(obj->v_base_color);

		// Transform the intersection point back into world coordinates.
		scn->v_intpoint = gt_apply(obj->transmat, cyl->valid_poi, FWDFM);

		// compute the local normal
		cyl->global_origin = gt_apply(obj->transmat, cyl->local_origin, FWDFM);
		set_vect(cyl->org_normal, cyl->valid_poi->data[0][0], cyl->valid_poi->data[1][0], 0.0);

		cyl->vtmp = gt_apply(obj->transmat, cyl->org_normal, FWDFM);
		nml_mat_sub_r(cyl->vtmp, cyl->v_obj_gorg);
		nml_mat_normalize_r(cyl->vtmp);
		set_vect(scn->v_lc_norm, cyl->vtmp->data[0][0], \
			cyl->vtmp->data[1][0], cyl->vtmp->data[2][0]);
		nml_mat_free(cyl->vtmp);

		// cyl->vtmp = gt_apply(obj->transmat, cyl->v_obj_norm, FWDFM);
		// nml_mat_sub_r(cyl->vtmp, cyl->v_obj_gorg);
		// nml_mat_normalize_r(cyl->vtmp);
		// set_vect(scn->v_lc_norm, cyl->vtmp->data[0][0], \
		// 	cyl->vtmp->data[1][0], cyl->vtmp->data[2][0]);
		// nml_mat_free(cyl->vtmp);
		scn->v_lc_color = nml_mat_cp(obj->v_base_color);
		return (1);
	}
	else
		return (cyl_not_side_inter(obj, scn, cyl));
}

int	cylinder_test_inter_scn(t_objbase *obj, t_scene *scn)
{
	t_inter_calc	cyl;

	cylinder_compute_values(&cyl, scn, obj);
	cyl_init_att(&cyl);
	if (cyl.num_sqrt > 0.0)
		cyl_inter_test(&cyl);
	else
	{
		cyl.t1_valid = 0;
		cyl.t2_valid = 0;
		cyl.tt[0] = 100e6;
		cyl.tt[1] = 100e6;
	}
	// And test the end caps.
	cyl_close_enough(&cyl);

	// Check all validators
	if (!cyl.t1_valid && !cyl.t2_valid && !cyl.t3_valid && !cyl.t4_valid)
		return (0);

	// Check for the smallest valid value of t
	cyl_get_min(&cyl);
	return (cyl_side_inter(obj, scn, &cyl));
}
