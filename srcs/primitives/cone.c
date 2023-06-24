/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 01:46:48 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objectbase.h"

void	cone_init(t_objbase *obj)
{
	(void) obj;
}

void	cone_deinit(t_objbase *obj)
{
	(void) obj;
}

void	cone_compute_values(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
{
	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);
	calc->vhat = nml_mat_cp(calc->bck_ray->v_lab);
	nml_vect_normalize_r(calc->vhat);
	calc->a = powf(calc->vhat->data[0][0], 2.0) + \
		powf(calc->vhat->data[1][0], 2.0) - powf(calc->vhat->data[2][0], 2.0);
	calc->b = 2.0 * ((calc->bck_ray->v_point1->data[0][0] * \
		calc->vhat->data[0][0]) + (calc->bck_ray->v_point1->data[1][0] * \
		calc->vhat->data[1][0]) - (calc->bck_ray->v_point1->data[2][0] * \
		calc->vhat->data[2][0]));
	calc->c = powf(calc->bck_ray->v_point1->data[0][0], 2.0) + \
		powf(calc->bck_ray->v_point1->data[1][0], 2.0) - \
		powf(calc->bck_ray->v_point1->data[2][0], 2.0);
	calc->inter_test = sqrtf(powf(calc->b, 2.0) - (4.0 * calc->a * calc->c));
}

void	cone_init_att(t_inter_calc *cone)
{
	cone->t1_valid = 0;
	cone->t2_valid = 0;
	cone->t3_valid = 0;
	cone->poi[0] = new_vector();
	cone->poi[1] = new_vector();
	cone->poi[2] = new_vector();
	cone->v_poi = new_vector();
}

void	cone_inter_test(t_inter_calc *cone)
{
	cone->tt[0] = (-cone->b + cone->inter_test) / (2 * cone->a);
	cone->tt[1] = (-cone->b - cone->inter_test) / (2 * cone->a);
	cone->poi[0] = nml_mat_add(cone->bck_ray->v_point1, nml_mat_smult(cone->vhat, cone->tt[0]));
	cone->poi[1] = nml_mat_add(cone->bck_ray->v_point1, nml_mat_smult(cone->vhat, cone->tt[1]));
	if ((cone->tt[0] > 0.0) && (cone->poi[0]->data[2][0] > 0.0) && (cone->poi[0]->data[2][0] < 1.0))
		cone->t1_valid = 1;
	else
	{
		cone->t1_valid = 0;
		cone->tt[0] = 100e6;
	}
	if ((cone->tt[1] > 0.0) && (cone->poi[1]->data[2][0] > 0.0) && (cone->poi[1]->data[2][0] < 1.0))
		cone->t2_valid = 1;
	else
	{
		cone->t2_valid = 0;
		cone->tt[1] = 100e6;
	}
}

void	cone_close_enough(t_inter_calc *cone)
{
	if (obj_close_enough(cone->vhat->data[2][0], 0.0))
	{
		cone->t3_valid = 0;
		cone->tt[2] = 100e6;
	}
	else
	{
		cone->tt[2] = (cone->bck_ray->v_point1->data[2][0] - 1.0) / -cone->vhat->data[2][0];
		cone->poi[2] = nml_mat_add(cone->bck_ray->v_point1, nml_mat_smult(cone->vhat, cone->tt[2]));
		if ((cone->tt[2] > 0.0) && (sqrtf(powf(cone->poi[2]->data[0][0], 2.0) + \
			powf(cone->poi[2]->data[1][0], 2.0)) < 1.0))
			cone->t3_valid = 1;
		else
		{
			cone->t3_valid = 0;
			cone->tt[2] = 100e6;
		}
	}
}

void	cone_get_min(t_inter_calc *cone)
{
	int	i;

	cone->min_i = 0;
	cone->min_t = 10e6;
	i = 0;
	while (i < 3)
	{
		if (cone->tt[i] < cone->min_t)
		{
			cone->min_t = cone->tt[i];
			cone->min_i = i;
		}
		i++;
	}
}

int	cone_side_inter(t_objbase *obj, t_scene *scn, t_inter_calc *cone)
{
	// if minIndex is 0 or 1, we have a side intersection
	t_nml_mat	*valid_poi;
	t_nml_mat	*org_normal;
	t_nml_mat	*local_origin;
	t_nml_mat	*global_origin;
	float		tx;
	float		ty;
	float		tz;

	valid_poi = nml_mat_cp(cone->poi[cone->min_i]);
	local_origin = new_vector();
	set_vect(local_origin, 0.0, 0.0, 0.0);
	global_origin = new_vector();
	org_normal = new_vector();
	// transform the intersection point to world coordinates
	scn->v_intpoint = gt_apply(obj->transmat, valid_poi, FWDFM);
	global_origin = gt_apply(obj->transmat, local_origin, FWDFM);
	if (cone->min_i < 2)
	{
		tx = valid_poi->data[0][0];
		ty = valid_poi->data[1][0];
		tz = -sqrtf(powf(tx, 2.0) + powf(ty, 2.0));
		set_vect(org_normal, tx, ty, tz);
		scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, org_normal, FWDFM), \
			global_origin);
		nml_mat_normalize_r(scn->v_lc_norm);
		// Return the base color
		scn->v_lc_color = nml_mat_cp(obj->v_base_color);
		return 1;
	}
	else
	{
		if (!obj_close_enough(cone->vhat->data[2][0], 0.0))
		{
			if (sqrtf(powf(valid_poi->data[0][0], 2.0) + powf(valid_poi->data[1][0], 2.0)) < 1.0)
			{
				// compute the local normal
				set_vect(org_normal, 0.0, 0.0, 1.0);
				scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, org_normal, FWDFM), \
					global_origin);
				nml_mat_normalize_r(scn->v_lc_norm);
				// return the base color
				scn->v_lc_color = nml_mat_cp(obj->v_base_color);
				return 1;
			}
			else
				return (0);
		}
		else
			return (0);
	}
	return (0);
}

int	cone_test_inter_scn(t_objbase *obj, t_scene *scn)
{
	t_inter_calc	cone;

	cone_compute_values(&cone, scn, obj);
	cone_init_att(&cone);
	if (cone.inter_test > 0.0)
		cone_inter_test(&cone);
	else
	{
		cone.t1_valid = 0;
		cone.t2_valid = 0;
		cone.tt[0] = 100e6;
		cone.tt[1] = 100e6;
	}
	cone_close_enough(&cone);
	if (!cone.t1_valid && !cone.t2_valid && !cone.t3_valid)
		return (0);
	cone_get_min(&cone);
	return (cone_side_inter(obj, scn, &cone));
}
