/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 02:48:18 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 22:58:33 by nnakarac         ###   ########.fr       */
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

/// @brief compute plane utility
/// @param calc
/// @param scn
/// @param obj
/// @return
int	plane_compute_values_util(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
{
	if (fabs(calc->u) < 1.0 && fabs(calc->v) < 1.0)
	{
		calc->v_poi = nml_mat_cp(calc->bck_ray->v_point1);
		calc->vtmp = nml_mat_cp(calc->k);
		nml_mat_smult_r(calc->vtmp, calc->t);
		nml_mat_add_r(calc->v_poi, calc->vtmp);
		nml_mat_free(calc->vtmp);
		scn->v_intpoint = gt_apply(obj->transmat, calc->v_poi, FWDFM);
		calc->v_obj_gorg = gt_apply(obj->transmat, calc->v_obj_org, FWDFM);
		calc->vtmp = gt_apply(obj->transmat, calc->v_obj_norm, FWDFM);
		nml_mat_sub_r(calc->vtmp, calc->v_obj_gorg);
		nml_mat_normalize_r(calc->vtmp);
		set_vect(scn->v_lc_norm, calc->vtmp->data[0][0], \
			calc->vtmp->data[1][0], calc->vtmp->data[2][0]);
		nml_mat_free(calc->vtmp);
		scn->v_lc_color = nml_mat_cp(obj->v_base_color);
		return (1);
	}
	return (0);
}

/// @brief compute plane
/// @note 1 - Copy the ray and apply the bwd
/// @note 2 - Copy the lab vector from bckray and normalize it.
/// @note 3 - Check if there if an intersection,
/// @note i.e. the castray is not parallel to plane
/// @note 3.1 - ignore if t is negative then the intersection is behind the cam
/// @note 3.1.1 if magnitude of both u and v leq to 1 then we in the plane
/// @note then compute local normal and set base color
/// @param calc calculator struct
/// @param scn
/// @param obj
/// @return
int	plane_compute_values(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
{
	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);
	calc->k = nml_mat_cp(calc->bck_ray->v_lab);
	nml_mat_normalize_r(calc->k);
	if (!obj_close_enough(calc->k->data[2][0], 0.0))
	{
		calc->t = calc->bck_ray->v_point1->data[2][0] / -calc->k->data[2][0];
		if (calc->t > 0.0)
		{
			calc->u = calc->bck_ray->v_point1->data[0][0] + \
				(calc->k->data[0][0] * calc->t);
			calc->v = calc->bck_ray->v_point1->data[1][0] + \
				(calc->k->data[1][0] * calc->t);
			return (plane_compute_values_util(calc, scn, obj));
		}
		return (0);
	}
	return (0);
}

/// @brief plane intersection test using scene struct
/// @param obj
/// @param scn
/// @return
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
