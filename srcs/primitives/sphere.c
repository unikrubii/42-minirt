/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 16:49:29 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objectbase.h"

void	sphere_init(t_objbase *obj)
{
	(void) obj;
}

void	sphere_deinit(t_objbase *obj)
{
	(void) obj;
}

void	sphere_compute_values(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
{
	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);
	calc->vhat = nml_mat_cp(calc->bck_ray->v_lab);
	nml_vect_normalize_r(calc->vhat);
	calc->b = 2.0 * nml_vect_dot(calc->bck_ray->v_point1, 0, calc->vhat, 0);
	calc->c = nml_vect_dot(calc->bck_ray->v_point1, 0, \
		calc->bck_ray->v_point1, 0) - 1.0;
	calc->inter_test = (calc->b * calc->b) - 4.0 * calc->c;
}

void	inter_calc(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
{
	if (calc->t1 < calc->t2)
	{
		calc->vtmp = nml_mat_smult(calc->vhat, calc->t1);
		nml_mat_add_r(calc->vtmp, calc->bck_ray->v_point1);
		set_vect(calc->v_poi, calc->vtmp->data[0][0], \
			calc->vtmp->data[1][0], calc->vtmp->data[2][0]);
		nml_mat_free(calc->vtmp);
	}
	else
	{
		calc->vtmp = nml_mat_smult(calc->vhat, calc->t2);
		nml_mat_add_r(calc->vtmp, calc->bck_ray->v_point1);
		set_vect(calc->v_poi, calc->vtmp->data[0][0], \
			calc->vtmp->data[1][0], calc->vtmp->data[2][0]);
		nml_mat_free(calc->vtmp);
	}
	scn->v_intpoint = gt_apply(obj->transmat, calc->v_poi, FWDFM);
	calc->v_obj_norg = gt_apply(obj->transmat, calc->v_obj_org, FWDFM);
	set_vect(scn->v_lc_norm, scn->v_intpoint->data[0][0], \
		scn->v_intpoint->data[1][0], scn->v_intpoint->data[2][0]);
	nml_mat_sub_r(scn->v_lc_norm, calc->v_obj_norg);
	nml_vect_normalize_r(scn->v_lc_norm);
	scn->v_lc_color = nml_mat_cp(obj->v_base_color);
}

int	sphere_test_inter_scn(t_objbase *obj, t_scene *scn)
{
	t_inter_calc	sph;

	sph.v_poi = new_vector();
	sph.v_obj_org = new_vector();
	set_vect(sph.v_obj_org, 0.0, 0.0, 0.0);
	sphere_compute_values(&sph, scn, obj);
	if (sph.inter_test > 0.0)
	{
		sph.num_sqrt = sqrtf(sph.inter_test);
		sph.t1 = (-sph.b + sph.num_sqrt) / 2.0;
		sph.t2 = (-sph.b - sph.num_sqrt) / 2.0;
		if ((sph.t1 < 0.0) || (sph.t2 < 0.0))
			return (nml_mat_free(sph.vhat), 0);
		else
			return (inter_calc(&sph, scn, obj), nml_mat_free(sph.vhat), 1);
	}
	else
		return (nml_mat_free(sph.vhat), 0);
}
