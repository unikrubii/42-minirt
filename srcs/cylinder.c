/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/08 01:42:22 by sthitiku         ###   ########.fr       */
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

float	pow(float x, float y)
{
	float	res;

	res = 1;
	while (y > 0)
	{
		res *= x;
		y--;
	}
	return (res);
}

void	cylinder_compute_values(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
{
	// Copy the ray and apply the bwd
	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);

	calc->vhat = nml_mat_cp(calc->bck_ray->v_lab);
	// calc->vhat = nml_mat_cp(scn->cam_ray->v_lab);
	nml_vect_normalize_r(calc->vhat);
	calc->a = pow(calc->vhat->data[0][0], 2) + pow(calc->vhat->data[1][0], 2);
	calc->b = 2.0 * (calc->bck_ray->v_point1->data[0][0] * calc->vhat->data[0][0] + \
		calc->bck_ray->v_point1->data[1][0] * calc->vhat->data[1][0]);
	calc->c = pow(calc->bck_ray->v_point1->data[0][0], 2) + \
		pow(calc->bck_ray->v_point1->data[1][0], 2) - 1.0;
	calc->inter_test = pow(calc->bck_ray->v_point1->data[0][0], 2) \
		- 4.0 * calc->a * calc->c;
	// calc->b = 2.0 * nml_vect_dot(calc->bck_ray->v_point1, 0, calc->vhat, 0);
	// calc->b = 2.0 * nml_vect_dot(scn->cam_ray->v_point1, 0, calc->vhat, 0);
	// calc->c = nml_vect_dot(calc->bck_ray->v_point1, 0, \
	// 	calc->bck_ray->v_point1, 0) - 1.0;
	// calc->c = nml_vect_dot(scn->cam_ray->v_point1, 0, \
	// 	scn->cam_ray->v_point1, 0) - 1.0;
	// calc->inter_test = (calc->b * calc->b) - 4.0 * calc->c;
}

int	cylinder_test_inter_scn(t_objbase *obj, t_scene *scn)
{
	t_inter_calc	cyl;

	cyl.v_poi = new_vector();
	cyl.v_obj_org = new_vector();
	set_vect(cyl.v_obj_org, 0.0, 0.0, 0.0);
	cylinder_compute_values(&cyl, scn, obj);
	if (cyl.inter_test > 0.0)
	{
		cyl.num_sqrt = sqrt(cyl.inter_test);
		cyl.t1 = (-cyl.b + cyl.num_sqrt) / 2.0;
		cyl.t2 = (-cyl.b - cyl.num_sqrt) / 2.0;
		if ((cyl.t1 < 0.0) || (cyl.t2 < 0.0))
			return (nml_mat_free(cyl.vhat), 0);
		else
			inter_calc(&cyl, scn, obj);
		return (nml_mat_free(cyl.vhat), 1);
	}
	else
		return (nml_mat_free(cyl.vhat), 0);
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
