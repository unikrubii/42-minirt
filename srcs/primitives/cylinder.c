/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/24 21:53:12 by sthitiku         ###   ########.fr       */
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

void	cylinder_compute_values(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
{
	// Copy the ray and apply the bwd
	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);
	calc->vhat = nml_mat_cp(calc->bck_ray->v_lab);
	nml_vect_normalize_r(calc->vhat);
	calc->a = powf(calc->vhat->data[0][0], 2) + powf(calc->vhat->data[1][0], 2);
	calc->b = 2.0 * (calc->bck_ray->v_point1->data[0][0] * calc->vhat->data[0][0] + \
		calc->bck_ray->v_point1->data[1][0] * calc->vhat->data[1][0]);
	calc->c = powf(calc->bck_ray->v_point1->data[0][0], 2) + \
		powf(calc->bck_ray->v_point1->data[1][0], 2) - 1.0;
	calc->inter_test = sqrtf(powf(calc->b, 2) - 4.0 * calc->a * calc->c);
}

int	cylinder_test_inter_scn(t_objbase *obj, t_scene *scn)
{
	t_inter_calc	cyl;
	t_nml_mat		*poi[4];
	float			t[4];
	int				t1_valid;
	int				t2_valid;
	int				t3_valid;
	int				t4_valid;

	cylinder_compute_values(&cyl, scn, obj);
	t1_valid = 0;
	t2_valid = 0;
	t3_valid = 0;
	t4_valid = 0;
	cyl.v_poi = new_vector();
	cyl.v_obj_org = new_vector();
	poi[0] = new_vector();
	poi[1] = new_vector();
	poi[2] = new_vector();
	poi[3] = new_vector();
	set_vect(cyl.v_obj_org, 0.0, 0.0, 0.0);
	if (cyl.inter_test > 0.0)
	{
		t[0] = (-cyl.b + cyl.inter_test) / (2 * cyl.a);
		t[1] = (-cyl.b - cyl.inter_test) / (2 * cyl.a);
		
		// compute the points of intersection
		poi[0] = nml_mat_add(cyl.bck_ray->v_point1, nml_mat_smult(cyl.vhat, t[0]));
		poi[1] = nml_mat_add(cyl.bck_ray->v_point1, nml_mat_smult(cyl.vhat, t[1]));

		// check if any of these are valid
		if ((t[0] > 0.0) && (fabs(poi[0]->data[2][0]) < 1.0))
			t1_valid = 1;
		else
		{
			t1_valid = 0;
			t[0] = 100e6;
		}
		if ((t[1] > 0.0) && (fabs(poi[1]->data[2][0]) < 1.0))
			t2_valid = 1;
		else
		{
			t2_valid = 0;
			t[1] = 100e6;
		}
	}
	else
	{
		t1_valid = 0;
		t2_valid = 0;
		t[0] = 100e6;
		t[1] = 100e6;
	}
	
	// test the end caps
	if (obj_close_enough(cyl.vhat->data[2][0], 0.0))
	{
		t3_valid = 0;
		t4_valid = 0;
		t[2] = 100e6;
		t[3] = 100e6;
	}
	else
	{
		// compute the values of t
		t[2] = (cyl.bck_ray->v_point1->data[2][0] - 1.0) / -cyl.vhat->data[2][0];
		t[3] = (cyl.bck_ray->v_point1->data[2][0] + 1.0) / -cyl.vhat->data[2][0];

		// compute the points of intersection
		poi[2] = nml_mat_add(cyl.bck_ray->v_point1, nml_mat_smult(cyl.vhat, t[2]));
		poi[3] = nml_mat_add(cyl.bck_ray->v_point1, nml_mat_smult(cyl.vhat, t[3]));

		// check if any of these are valid
		if ((t[2] > 0.0) && sqrtf(powf(poi[2]->data[0][0], 2)) + \
			powf(poi[2]->data[1][0], 2) < 1.0)
			t3_valid = 1;
		else
		{
			t3_valid = 0;
			t[2] = 100e6;
		}
		if ((t[3] > 0.0) && sqrtf(powf(poi[3]->data[0][0], 2)) + \
			powf(poi[3]->data[1][0], 2) < 1.0)
			t4_valid = 1;
		else
		{
			t4_valid = 0;
			t[3] = 100e6;
		}
	}

	// if no valid intersection
	if (!t1_valid && !t2_valid && !t3_valid && !t4_valid)
		return 0;

	// find the smallest t
	int		min_i;
	float	min_t;
	int		i = 0;

	min_i = 0;
	min_t = 10e6;
	while (i < 4)
	{
		if (t[i] < min_t)
		{
			min_t = t[i];
			min_i = i;
		}
		i++;
	}

	// if min_i is 0 or 1, we have a side intersection
	t_nml_mat	*valid_poi;
	t_nml_mat	*org_normal;
	t_nml_mat	*local_origin;
	t_nml_mat	*global_origin;

	local_origin = new_vector();
	set_vect(local_origin, 0.0, 0.0, 0.0);
	org_normal = new_vector();
	valid_poi = nml_mat_cp(poi[min_i]);
	if (min_i < 2)
	{
		// transform the intersection point to world coordinates
		scn->v_intpoint = gt_apply(obj->transmat, valid_poi, FWDFM);

		// compute the local normal
		global_origin = gt_apply(obj->transmat, local_origin, FWDFM);
		set_vect(org_normal, valid_poi->data[0][0], \
			valid_poi->data[1][0], 0.0);
		scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, org_normal, FWDFM), \
			global_origin);
		nml_mat_normalize_r(scn->v_lc_norm);

		// Return the base color
		scn->v_lc_color = nml_mat_cp(obj->v_base_color);
		return 1;
	}
	else
	{
		if (!obj_close_enough(cyl.vhat->data[2][0], 0.0))
		{
			if (sqrtf(pow(valid_poi->data[0][0], 2) + \
				pow(valid_poi->data[1][0], 2)) < 1.0)
			{
				scn->v_intpoint = gt_apply(obj->transmat, valid_poi, FWDFM);
				// comput local normal
				set_vect(org_normal, obj->up_x, obj->up_y, obj->up_z + valid_poi->data[2][0]);
				// set_vect(org_normal, 0.0, 0.0, 0.0 + valid_poi->data[2][0]);
				global_origin = gt_apply(obj->transmat, local_origin, FWDFM);
				scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, \
					org_normal, FWDFM), global_origin);
				nml_mat_normalize_r(scn->v_lc_norm);
				scn->v_lc_color = nml_mat_cp(obj->v_base_color);
				return 1;
			}
			else
				return 0;
		}
	}
	return 0;
}


// void	sphere_init(t_objbase *obj)
// {
// 	(void) obj;
// }

// void	sphere_deinit(t_objbase *obj)
// {
// 	(void) obj;
// }

// void	sphere_compute_values(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
// {
// 	// Copy the ray and apply the bwd
// 	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);

// 	calc->vhat = nml_mat_cp(calc->bck_ray->v_lab);
// 	// calc->vhat = nml_mat_cp(scn->cam_ray->v_lab);
// 	nml_vect_normalize_r(calc->vhat);
// 	calc->b = 2.0 * nml_vect_dot(calc->bck_ray->v_point1, 0, calc->vhat, 0);
// 	// calc->b = 2.0 * nml_vect_dot(scn->cam_ray->v_point1, 0, calc->vhat, 0);
// 	calc->c = nml_vect_dot(calc->bck_ray->v_point1, 0, \
// 		calc->bck_ray->v_point1, 0) - 1.0;
// 	// calc->c = nml_vect_dot(scn->cam_ray->v_point1, 0, \
// 	// 	scn->cam_ray->v_point1, 0) - 1.0;
// 	calc->inter_test = (calc->b * calc->b) - 4.0 * calc->c;
// }

// void	inter_calc(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
// {
// 	(void) obj;
// 	if (calc->t1 < calc->t2)
// 	{
// 		calc->vtmp = nml_mat_smult(calc->vhat, calc->t1);
// 		nml_mat_add_r(calc->vtmp, calc->bck_ray->v_point1);
// 		// nml_mat_add_r(calc->vtmp, scn->cam_ray->v_point1);
// 		set_vect(calc->v_poi, calc->vtmp->data[0][0], \
// 			calc->vtmp->data[1][0], calc->vtmp->data[2][0]);
// 		// set_vect(scn->v_intpoint, calc->vtmp->data[0][0], \
// 		// 	calc->vtmp->data[1][0], calc->vtmp->data[2][0]);
// 		nml_mat_free(calc->vtmp);
// 	}
// 	else
// 	{
// 		calc->vtmp = nml_mat_smult(calc->vhat, calc->t2);
// 		nml_mat_add_r(calc->vtmp, calc->bck_ray->v_point1);
// 		// nml_mat_add_r(calc->vtmp, scn->cam_ray->v_point1);
// 		set_vect(calc->v_poi, calc->vtmp->data[0][0], \
// 			calc->vtmp->data[1][0], calc->vtmp->data[2][0]);
// 		// set_vect(scn->v_intpoint, calc->vtmp->data[0][0], \
// 		// 	calc->vtmp->data[1][0], calc->vtmp->data[2][0]);
// 		nml_mat_free(calc->vtmp);
// 	}
// 	scn->v_intpoint = gt_apply(obj->transmat, calc->v_poi, FWDFM);
// 	calc->v_obj_norg = gt_apply(obj->transmat, calc->v_obj_org, FWDFM);

// 	set_vect(scn->v_lc_norm, scn->v_intpoint->data[0][0], \
// 		scn->v_intpoint->data[1][0], scn->v_intpoint->data[2][0]);

// 	nml_mat_sub_r(scn->v_lc_norm, calc->v_obj_norg);

// 	nml_vect_normalize_r(scn->v_lc_norm);

// 	scn->v_lc_color = obj->v_base_color;
// }

// int	sphere_test_inter_scn(t_objbase *obj, t_scene *scn)
// {
// 	t_inter_calc	sph;

// 	(void) obj;
// 	sph.v_poi = new_vector();
// 	sph.v_obj_org = new_vector();
// 	set_vect(sph.v_obj_org, 0.0, 0.0, 0.0);
// 	sphere_compute_values(&sph, scn, obj);
// 	if (sph.inter_test > 0.0)
// 	{
// 		sph.num_sqrt = sqrt(sph.inter_test);
// 		sph.t1 = (-sph.b + sph.num_sqrt) / 2.0;
// 		sph.t2 = (-sph.b - sph.num_sqrt) / 2.0;
// 		if ((sph.t1 < 0.0) || (sph.t2 < 0.0))
// 			return (nml_mat_free(sph.vhat), 0);
// 		else
// 			inter_calc(&sph, scn, obj);
// 		return (nml_mat_free(sph.vhat), 1);
// 	}
// 	else
// 		return (nml_mat_free(sph.vhat), 0);
// }
