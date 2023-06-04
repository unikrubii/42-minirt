/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 02:48:18 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/04 19:26:04 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objectbase.h"

void	plane_init(t_objbase *obj)
{
	(void) obj;
}

void	plane_deinit(t_objbase *obj)
{
	(void) obj;
}

int	plane_compute_values(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
{
	// Copy the ray and apply the bwd
	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);

	// Copy the lab vector from bckray and normalize it.
	calc->k = nml_mat_cp(calc->bck_ray->v_lab);
	nml_mat_normalize_r(calc->k);

	// Chec if there if an intersection, i.e. the castray is not parallel to plane
	if (!obj_close_enough(calc->k->data[2][0], 0.0))
	{
		// There is an intersection
		calc->t = calc->bck_ray->v_point1->data[2][0] / -calc->k->data[2][0];

		// if t is negative then the intersection is behind the camere, ignore it
		if (calc->t > 0.0)
		{
			calc->u = calc->bck_ray->v_point1->data[0][0] + (calc->k->data[0][0] * calc->t);
			calc->v = calc->bck_ray->v_point1->data[1][0] + (calc->k->data[1][0] * calc->t);

			// if the magnitude of both u and v is less than or eq to 1 then we must be in the plane
			if (fabs(calc->u) < 1.0 && fabs(calc->v) < 1.0)
			{
				calc->v_poi = nml_mat_cp(calc->bck_ray->v_point1);
				calc->vtmp = nml_mat_cp(calc->k);
				nml_mat_smult_r(calc->vtmp, calc->t);
				nml_mat_add_r(calc->v_poi, calc->vtmp);
				nml_mat_free(calc->vtmp);


				scn->v_intpoint = gt_apply(obj->transmat, calc->v_poi, FWDFM);

				// Compute Local Normal
				calc->v_obj_gorg = gt_apply(obj->transmat, calc->v_obj_org, FWDFM);
				calc->vtmp = gt_apply(obj->transmat, calc->v_obj_norm, FWDFM);
				nml_mat_sub_r(calc->vtmp, calc->v_obj_gorg);
				nml_mat_normalize_r(calc->vtmp);
				set_vect(scn->v_lc_norm, calc->vtmp->data[0][0], \
					calc->vtmp->data[1][0], calc->vtmp->data[2][0]);
				nml_mat_free(calc->vtmp);

				//Return Base Color
				// scn->v_lc_color = obj->v_base_color;
				scn->v_lc_color = nml_mat_cp(obj->v_base_color);

				return (1);
			}
			return (0);
		}
		return (0);
	}
	return (0);
}

int	plane_test_inter_scn(t_objbase *obj, t_scene *scn)
{
	t_inter_calc	pln;

	pln.v_poi = new_vector();
	pln.v_obj_org = new_vector();
	pln.v_obj_norm = new_vector();
	set_vect(pln.v_obj_org, 0.0, 0.0, 0.0);
	set_vect(pln.v_obj_norm, 0.0, 0.0, -1.0);
	return (plane_compute_values(&pln, scn, obj));
}

// void	compute_values(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
// {
// 	// Copy the ray and apply the bwd
// 	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, FWDFM);

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
// 	compute_values(&sph, scn, obj);
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
